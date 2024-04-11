#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "xil_types.h"
#include "xil_cache.h"
#include "xparameters.h"
#include "xgpio.h"
#include "xaxivdma.h"
#include "xaxivdma_i.h"
#include "display_ctrl/display_ctrl.h"
#include "vdma_api/vdma_api.h"
#include "emio_sccb_cfg/emio_sccb_cfg.h"
#include "ov5640/ov5640_init.h"
#include "xov5640_rgb2gray.h"

//宏定义
#define BYTES_PIXEL 3
#define FRAME_BUFFER_NUM 3
#define DYNCLK_BASEADDR XPAR_AXI_DYNCLK_0_BASEADDR
#define VDMA_ID XPAR_AXIVDMA_0_DEVICE_ID
#define DISP_VTC_ID XPAR_AXI_GPIO_0_DEVICE_ID
//使用AXI GPIO(LCD_ID)器件ID
#define AXI_GPIO_0_ID XPAR_AXI_GPIO_0_DEVICE_ID
//使用AXI GPIO(lcd_id) 通道1
#define AXI_GPIO_0_CHANEL 1

//全局变量
//frame buffer的起始地址
unsigned int const frame_buffer_addr = (XPAR_PS7_DDR_0_S_AXI_BASEADDR + 0X1000000);

XAxiVdma vdma;
DisplayCtrl dispCtrl;
XGpio axi_gpio_inst;
XOv5640_rgb2gray rgb2gray_inst;
VideoMode vd_mode;
unsigned int lcd_id;

int main(void)
{
	u32 status;
	u16 cmos_h_pixel;
	u16 cmos_v_pixel;
	u16 total_h_pixel;
	u16 total_v_pixel;

	XGpio_Initialize(&axi_gpio_inst,AXI_GPIO_0_ID);
	XGpio_SetDataDirection(&axi_gpio_inst,AXI_GPIO_0_CHANEL,0X07);
	lcd_id = LTDC_PanelID_Read(&axi_gpio_inst,AXI_GPIO_0_CHANEL);
	XGpio_SetDataDirection(&axi_gpio_inst,AXI_GPIO_0_CHANEL,0x00);
	xil_printf("LCD ID: %x\r\n",lcd_id);

	//根据获取的LCD的ID号来进行ov5640显示分辨率参数的选择
	switch(lcd_id){
		case 0x4342:
			cmos_h_pixel = 480;
			cmos_v_pixel = 272;
			total_h_pixel = 1800;
			total_v_pixel = 1000;
			break;
		case 0x4384:
			cmos_h_pixel = 800;
			cmos_v_pixel = 480;
			total_h_pixel = 1800;
			total_v_pixel = 1000;
			break;
		case 0x7084:
			cmos_h_pixel = 400;
			cmos_v_pixel = 240;
			total_h_pixel = 1800;
			total_v_pixel = 1000;
			break;
		case 0x7016:
			cmos_h_pixel = 1024;
			cmos_v_pixel = 600;
			total_h_pixel = 2200;
			total_v_pixel = 1000;
			break;
		case 0x1018:
			cmos_h_pixel = 1280;
			cmos_v_pixel = 800;
			total_h_pixel = 2570;
			total_v_pixel = 980;
			break;
		default:
			cmos_h_pixel = 480;
			cmos_v_pixel = 272;
			total_h_pixel = 1800;
			total_v_pixel = 1000;
			break;

	}

	emio_init();                       //初始化EMIO
	status = ov5640_init(cmos_h_pixel, //初始化ov5640
						cmos_v_pixel,
						total_h_pixel,
						total_v_pixel);
	if(status == 0)
		xil_printf("OV5640 detected successful!\r\n");
	else
		xil_printf("OV5640 detected successful!\r\n");

	//根据获取的LCD的ID号来进行video参数的选择
	switch(lcd_id){
	case 0x4342 : vd_mode = VMODE_480x272; break;
	case 0x4384 : vd_mode = VMODE_800x480; break;
	case 0x7084 : vd_mode = VMODE_800x480; break;
	case 0x7016 : vd_mode = VMODE_1024x600; break;
	case 0x1018 : vd_mode = VMODE_1280x800; break;
	default: vd_mode = VMODE_800x480; break;
	}

	//初始化灰度转换IP核OV5640_RGB2GRAY
	XOv5640_rgb2gray_Initialize(&rgb2gray_inst, XPAR_OV5640_RGB2GRAY_0_DEVICE_ID);
	//配置灰度转换IP核OV5640_RGB2GRAY的行数
	XOv5640_rgb2gray_Set_rows(&rgb2gray_inst,vd_mode.height);
	//配置灰度转换IP核OV5640——RGB2GRAY的列数
	XOv5640_rgb2gray_Set_cols(&rgb2gray_inst, vd_mode.width);

	//配置VDMA
	run_vdma_frame_buffer(&vdma,VDMA_ID,vd_mode.width,vd_mode.height,frame_buffer_addr,0,0,BOTH);
	//初始化Display controller
	DisplayInitialize(&dispCtrl,DISP_VTC_ID,DYNCLK_BASEADDR);
	//设置VideoMode
	DisplaySetMode(&dispCtrl,&vd_mode);
	DisplayStart(&dispCtrl);

	return 0;
}












