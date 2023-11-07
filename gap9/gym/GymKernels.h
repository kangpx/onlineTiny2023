#ifndef __GYMKERNEL_H__
#define __GYMKERNEL_H__

#include "AutoTilerLibTypes.h"
#include "at_api.h"
#include "Gym.h"
#include "CNN_BasicKernels_fp16.h"
#include "Expression_Kernels.h"
#define _Gym_L1_Memory_SIZE 35328
#define _Gym_L2_Memory_SIZE 247704
#define _Gym_L2_Memory_Dyn_SIZE 20480
extern char *Gym_L1_Memory; /* Size given for generation: 128000 bytes, used: 35328 bytes */
extern char *Gym_L2_Memory; /* Size used for generation (static): 247704 bytes */
extern char *Gym_L2_Memory_Dyn; /* Size used for generation (dynamic): 20480 bytes */
extern void S4_Conv_0_fusion(
		F16 * __restrict__ In,
		F16 * __restrict__ Filter,
		F16 * __restrict__ Bias,
		F16 * __restrict__ Out);
extern void S9_Conv_2_fusion(
		F16 * __restrict__ In,
		F16 * __restrict__ Filter,
		F16 * __restrict__ Bias,
		F16 * __restrict__ Out);
extern void S12_Conv_4_fusion(
		F16 * __restrict__ In,
		F16 * __restrict__ Filter,
		F16 * __restrict__ Bias,
		F16 * __restrict__ Out);
extern void S15_Conv_6(
		F16 * __restrict__ In,
		F16 * __restrict__ Filter,
		F16 * __restrict__ Bias,
		F16 * __restrict__ Out);
extern void S17_Add_7_fusion(
		F16 * __restrict__ In1,
		F16 * __restrict__ In2,
		F16 * __restrict__ Out);
extern void S21_Conv_9_fusion(
		F16 * __restrict__ In,
		F16 * __restrict__ Filter,
		F16 * __restrict__ Bias,
		F16 * __restrict__ Out);
extern void S24_Conv_11_fusion(
		F16 * __restrict__ In,
		F16 * __restrict__ Filter,
		F16 * __restrict__ Bias,
		F16 * __restrict__ Out);
extern void S27_Conv_13(
		F16 * __restrict__ In,
		F16 * __restrict__ Filter,
		F16 * __restrict__ Bias,
		F16 * __restrict__ Out);
extern void S29_Add_14_fusion(
		F16 * __restrict__ In1,
		F16 * __restrict__ In2,
		F16 * __restrict__ Out);
extern void S33_Conv_16_fusion(
		F16 * __restrict__ In,
		F16 * __restrict__ Filter,
		F16 * __restrict__ Bias,
		F16 * __restrict__ Out);
extern void S36_Conv_18_fusion(
		F16 * __restrict__ In,
		F16 * __restrict__ Filter,
		F16 * __restrict__ Bias,
		F16 * __restrict__ Out);
extern void S39_Conv_20(
		F16 * __restrict__ In,
		F16 * __restrict__ Filter,
		F16 * __restrict__ Bias,
		F16 * __restrict__ Out);
extern void S43_Conv_21(
		F16 * __restrict__ In2,
		F16 * __restrict__ In1,
		F16 * __restrict__ Bias,
		F16 * __restrict__ Out);
extern void S45_Add_22_fusion(
		F16 * __restrict__ In1,
		F16 * __restrict__ In2,
		F16 * __restrict__ Out);
extern void S48_Gemm_31(
		F16 * __restrict__ In,
		F16 * __restrict__ Filter,
		F16 * __restrict__ Bias,
		F16 * __restrict__ Out);
extern void S49_Softmax_32(
		F16 * __restrict__ In,
		F16 * __restrict__ Out);
extern int GymCNN_Construct();
extern void GymCNN_ConstructCluster();
extern int GymCNN_Destruct();
extern int GymCNN_Memory(AT_MEM_TYPE Which);
extern int GymCNN(
		F16 * __restrict__ Input_1,
		F16 * __restrict__ Output_1);
extern unsigned int AT_GraphPerf[17];
extern unsigned int AT_GraphPerf_CNN_Total;
extern char * AT_GraphNodeNames[17];
extern unsigned int AT_GraphOperInfosNames[17];
#endif
