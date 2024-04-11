// ==============================================================
// File generated on Thu Apr 11 15:09:01 +0800 2024
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2018.3 (64-bit)
// SW Build 2405991 on Thu Dec  6 23:38:27 MST 2018
// IP Build 2404404 on Fri Dec  7 01:43:56 MST 2018
// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xov5640_rgb2gray.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XOv5640_rgb2gray_CfgInitialize(XOv5640_rgb2gray *InstancePtr, XOv5640_rgb2gray_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Axilites_BaseAddress = ConfigPtr->Axilites_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XOv5640_rgb2gray_Set_rows(XOv5640_rgb2gray *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XOv5640_rgb2gray_WriteReg(InstancePtr->Axilites_BaseAddress, XOV5640_RGB2GRAY_AXILITES_ADDR_ROWS_DATA, Data);
}

u32 XOv5640_rgb2gray_Get_rows(XOv5640_rgb2gray *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XOv5640_rgb2gray_ReadReg(InstancePtr->Axilites_BaseAddress, XOV5640_RGB2GRAY_AXILITES_ADDR_ROWS_DATA);
    return Data;
}

void XOv5640_rgb2gray_Set_cols(XOv5640_rgb2gray *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XOv5640_rgb2gray_WriteReg(InstancePtr->Axilites_BaseAddress, XOV5640_RGB2GRAY_AXILITES_ADDR_COLS_DATA, Data);
}

u32 XOv5640_rgb2gray_Get_cols(XOv5640_rgb2gray *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XOv5640_rgb2gray_ReadReg(InstancePtr->Axilites_BaseAddress, XOV5640_RGB2GRAY_AXILITES_ADDR_COLS_DATA);
    return Data;
}

