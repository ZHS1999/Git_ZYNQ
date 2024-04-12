#ifndef _OV5640_SOBEL_H
#define _OV5640_SOBEL_H

#include "hls_video.h"

#define MAX_HEIGHT 800
#define MAX_WIDTH  1280

#define INPUT_IMAGE "lena.jpg"
#define OUTPUT_IMAGE "lena_sobel.jpg"

typedef hls::stream<ap_axiu<24,1,1,1> > AXI_STREAM;
typedef hls::Mat<MAX_HEIGHT,MAX_WIDTH,HLS_8UC3> RGB_IMAGE;
typedef hls::Mat<MAX_HEIGHT,MAX_WIDTH,HLS_8UC1> GRAY_IMAGE;

void ov5640_sobel(AXI_STREAM &INPUT_STREAM,
		AXI_STREAM &OUTPUT_STREAM,
		int rows,
		int cols
		);
#endif
