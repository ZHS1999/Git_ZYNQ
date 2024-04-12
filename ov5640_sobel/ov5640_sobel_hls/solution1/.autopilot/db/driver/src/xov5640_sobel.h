// ==============================================================
// File generated on Fri Apr 12 14:33:45 +0800 2024
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2018.3 (64-bit)
// SW Build 2405991 on Thu Dec  6 23:38:27 MST 2018
// IP Build 2404404 on Fri Dec  7 01:43:56 MST 2018
// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XOV5640_SOBEL_H
#define XOV5640_SOBEL_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xov5640_sobel_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
#else
typedef struct {
    u16 DeviceId;
    u32 Axilites_BaseAddress;
} XOv5640_sobel_Config;
#endif

typedef struct {
    u32 Axilites_BaseAddress;
    u32 IsReady;
} XOv5640_sobel;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XOv5640_sobel_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XOv5640_sobel_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XOv5640_sobel_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XOv5640_sobel_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
int XOv5640_sobel_Initialize(XOv5640_sobel *InstancePtr, u16 DeviceId);
XOv5640_sobel_Config* XOv5640_sobel_LookupConfig(u16 DeviceId);
int XOv5640_sobel_CfgInitialize(XOv5640_sobel *InstancePtr, XOv5640_sobel_Config *ConfigPtr);
#else
int XOv5640_sobel_Initialize(XOv5640_sobel *InstancePtr, const char* InstanceName);
int XOv5640_sobel_Release(XOv5640_sobel *InstancePtr);
#endif


void XOv5640_sobel_Set_rows(XOv5640_sobel *InstancePtr, u32 Data);
u32 XOv5640_sobel_Get_rows(XOv5640_sobel *InstancePtr);
void XOv5640_sobel_Set_cols(XOv5640_sobel *InstancePtr, u32 Data);
u32 XOv5640_sobel_Get_cols(XOv5640_sobel *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
