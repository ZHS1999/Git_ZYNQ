############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2018 Xilinx, Inc. All Rights Reserved.
############################################################
open_project ov5640_sobel_hls
set_top ov5640_sobel
add_files ov5640_sobel_hls/src/lena.jpg
add_files ov5640_sobel_hls/src/ov5640_sobel.cpp
add_files ov5640_sobel_hls/src/ov5640_sobel.h
add_files -tb ov5640_sobel_hls/src/lena.jpg
add_files -tb ov5640_sobel_hls/src/ov5640_sobel.cpp
add_files -tb ov5640_sobel_hls/src/ov5640_sobel.h
add_files -tb ov5640_sobel_hls/src/ov5640_sobel_tb.cpp
open_solution "solution1"
set_part {xc7z020clg400-2} -tool vivado
create_clock -period 20 -name default
#source "./ov5640_sobel_hls/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -rtl verilog -format ip_catalog
