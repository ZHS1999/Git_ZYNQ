#include "hls_video.h"

#define MAX_HEIGHT 800
#define MAX_WIDTH  1280

typedef hls::stream<ap_axiu<24,1,1,1> > AXI_STREAM;//此处应格外注意< <> >大的套小的时中间是有空格的
typedef hls::Mat<MAX_HEIGHT,MAX_WIDTH,HLS_8UC3> RGB_IMAGE;
typedef hls::Mat<MAX_HEIGHT,MAX_WIDTH,HLS_8UC1> GRAY_IMAGE;

void ov5640_rgb2gray(AXI_STREAM &INPUT_STREAM,
		AXI_STREAM &OUTPUT_STREAM,
		int rows,
		int cols){
#pragma HLS INTERFACE axis port = INPUT_STREAM
#pragma HLS INTERFACE axis port = OUTPUT_STREAM
#pragma HLS INTERFACE s_axilite port = rows
#pragma HLS INTERFACE s_axilite port = cols
#pragma HLS INTERFACE ap_ctrl_none port = return
#pragma HLS dataflow

	//hls::mat 格式变量
	RGB_IMAGE img_0(rows,cols);
	GRAY_IMAGE img_1(rows,cols);
	RGB_IMAGE img_2(rows,cols);

	//将AXI4 Stream数据转换成hls::mat格式
	hls::AXIvideo2Mat(INPUT_STREAM, img_0);

	//将RGB888格式的彩色数据转换成灰度数据
	hls::CvtColor<HLS_RGB2GRAY,HLS_8UC3,HLS_8UC1>(img_0,img_1);

	//将灰度数据转换成三个通道的灰度图像
	hls::CvtColor<HLS_GRAY2RGB,HLS_8UC1,HLS_8UC3>(img_1,img_2);
	//hls::mat格式数据转换成AXI4 Stream格式
	hls::Mat2AXIvideo(img_2, OUTPUT_STREAM);
}
