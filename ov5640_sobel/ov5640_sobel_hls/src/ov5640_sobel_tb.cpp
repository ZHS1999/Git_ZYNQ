#include "ov5640_sobel.h"
#include "hls_opencv.h"

int main(void)
{
	//获取图像数据
	IplImage* src = cvLoadImage(INPUT_IMAGE);
	IplImage* dst = cvCreateImage(cvGetSize(src),src->depth,src->nChannels);

	//使用HLS库进行处理
	AXI_STREAM src_axi, dst_axi;
	IplImage2AXIvideo(src, src_axi);
	ov5640_sobel(src_axi,dst_axi,src->height,src->width);
    AXIvideo2IplImage(dst_axi,dst);

    //保存图像
    cvSaveImage(OUTPUT_IMAGE,dst);
    //显示图像
    cvShowImage(INPUT_IMAGE,src);
    cvShowImage(OUTPUT_IMAGE,dst);

    //等待用户按下键盘上的任一按键
    cv::waitKey(0);
}
