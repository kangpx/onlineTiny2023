#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#include "GymKernels.h"
L1_CL_MEM AT_L1_POINTER Gym_L1_Memory;
L2_MEM AT_L2_POINTER Gym_L2_Memory;
L2_MEM AT_L2_POINTER Gym_L2_Memory_Dyn;
static AT_DEFAULTFLASH_FS_T DefaultFlash;
void S4_Conv_0_fusion(
		F16 * __restrict__ In,
		F16 * __restrict__ Filter,
		F16 * __restrict__ Bias,
		F16 * __restrict__ Out)

{
	/* Shared L1: 8544 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT _DmaR_Evt1, *DmaR_Evt1 = &_DmaR_Evt1;
	AT_L2_EVENT _DmaW_Evt1, *DmaW_Evt1 = &_DmaW_Evt1;
	Ker_MM_Conv_fp16_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int D1Ind, D1Ind_Last;
	int T0Ind, T0Ind_Last;
	int D0Ind, D0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 64, Tiled: 1][Tile0 Dim: 1][D0 Dim: Init: 7, Tiled: 1]
	Ker Arg: KerBuff, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 0 (Total Size: 48 )[Tile0, 1:[24x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[24x1], 2]
		Tile0: [0, 48, 48], Tile1: [0, 48, 48], Tile2; [0, 48, 48]
	Ker Arg: In, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 48 (Total Size: 560 )[D0, [0 x 560, 560]][Tile0, 1:[40x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[40x1], 2][D0, [0 x 560, 560]]
		Tile0: [0, 560, 560], Tile1: [0, 560, 560], Tile2; [0, 560, 560]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 608 (Total Size: 128 )[D1, [0 x 128, 128]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 128, 128]]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 736 (Total Size: 2688 )[D1, [0 x 2688, 2688]][D0, [0 x 42, 42]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 2688, 2688]][D0, [0 x 42, 42]]
		Tile0: [0, 2688, 2688], Tile1: [0, 2688, 2688], Tile2; [0, 2688, 2688]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 3424 (Total Size: 5120 )[D1, [0 x 5120, 5120]][Tile0, 1:[40x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 5120, 5120]][Tile0, 1:[40x1], 2]
		Tile0: [0, 5120, 5120], Tile1: [0, 5120, 5120], Tile2; [0, 5120, 5120]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (F16 * __restrict__) (Gym_L1_Memory+48);
	KerArg0->W = (unsigned short int) (40);
	KerArg0->H = (unsigned short int) (1);
	KerArg0->Fx = (unsigned char) (3);
	KerArg0->Sx = (unsigned char) (1);
	KerArg0->Sy = (unsigned char) (1);
	KerArg0->FirstTile = (unsigned char) ((1));
	KerArg0->Pad = (v4s) ((v4s){1,1,0,0});
	KerArg0->Filter = (F16 * __restrict__) (Gym_L1_Memory+736);
	KerArg0->Bias = (F16 * __restrict__) (Gym_L1_Memory+608);
	KerArg0->Out = (F16 * __restrict__) (Gym_L1_Memory+3424);
	KerArg0->InFeat = (unsigned short int) (7);
	KerArg0->OutFeat = (unsigned short int) (64);
	KerArg0->Wo = (unsigned short int) (40);
	KerArg0->Ho = (unsigned short int) (1);
	KerArg0->ColBuff = (F16 * __restrict__) (Gym_L1_Memory+0);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+736), 2688, 0, DmaR_Evt1);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+48), 560, 0, 0);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+608), 128, 0, 0);
	AT_L2_WAIT(0, DmaR_Evt1); /* Wait previous DMA read Bias */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1;
			{ /* Single iteration on D0 */
				int D0Ind_Last = 1;
				/*====================== Call Kernel LOC_D0 =========================*/
				AT_FORK(gap_ncore(), (void *) KerPar_MM_Conv1D_ReLU_fp16, (void *) KerArg0);
				__CALL(KerPar_MM_Conv1D_ReLU_fp16, KerArg0);
			} /* End iteration on D0 */
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+3424), 5120, 1, DmaW_Evt1);
	AT_L2_WAIT(0, DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S9_Conv_2_fusion(
		F16 * __restrict__ In,
		F16 * __restrict__ Filter,
		F16 * __restrict__ Bias,
		F16 * __restrict__ Out)

{
	/* Shared L1: 35328 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT _DmaR_Evt1, *DmaR_Evt1 = &_DmaR_Evt1;
	AT_L2_EVENT _DmaW_Evt1, *DmaW_Evt1 = &_DmaW_Evt1;
	Ker_MM_Conv_fp16_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int D1Ind, D1Ind_Last;
	int T0Ind, T0Ind_Last;
	int D0Ind, D0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 64, Tiled: 1][Tile0 Dim: 1][D0 Dim: Init: 64, Tiled: 1]
	Ker Arg: KerBuff, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 0 (Total Size: 384 )[Tile0, 1:[192x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[192x1], 2]
		Tile0: [0, 384, 384], Tile1: [0, 384, 384], Tile2; [0, 384, 384]
	Ker Arg: In, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 384 (Total Size: 5120 )[D0, [0 x 5120, 5120]][Tile0, 1:[40x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[40x1], 2][D0, [0 x 5120, 5120]]
		Tile0: [0, 5120, 5120], Tile1: [0, 5120, 5120], Tile2; [0, 5120, 5120]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 5504 (Total Size: 128 )[D1, [0 x 128, 128]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 128, 128]]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 5632 (Total Size: 24576 )[D1, [0 x 24576, 24576]][D0, [0 x 384, 384]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 24576, 24576]][D0, [0 x 384, 384]]
		Tile0: [0, 24576, 24576], Tile1: [0, 24576, 24576], Tile2; [0, 24576, 24576]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 30208 (Total Size: 5120 )[D1, [0 x 5120, 5120]][Tile0, 1:[40x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 5120, 5120]][Tile0, 1:[40x1], 2]
		Tile0: [0, 5120, 5120], Tile1: [0, 5120, 5120], Tile2; [0, 5120, 5120]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (F16 * __restrict__) (Gym_L1_Memory+384);
	KerArg0->W = (unsigned short int) (40);
	KerArg0->H = (unsigned short int) (1);
	KerArg0->Fx = (unsigned char) (3);
	KerArg0->Sx = (unsigned char) (1);
	KerArg0->Sy = (unsigned char) (1);
	KerArg0->FirstTile = (unsigned char) ((1));
	KerArg0->Pad = (v4s) ((v4s){1,1,0,0});
	KerArg0->Filter = (F16 * __restrict__) (Gym_L1_Memory+5632);
	KerArg0->Bias = (F16 * __restrict__) (Gym_L1_Memory+5504);
	KerArg0->Out = (F16 * __restrict__) (Gym_L1_Memory+30208);
	KerArg0->InFeat = (unsigned short int) (64);
	KerArg0->OutFeat = (unsigned short int) (64);
	KerArg0->Wo = (unsigned short int) (40);
	KerArg0->Ho = (unsigned short int) (1);
	KerArg0->ColBuff = (F16 * __restrict__) (Gym_L1_Memory+0);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+5632), 24576, 0, DmaR_Evt1);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+384), 5120, 0, 0);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+5504), 128, 0, 0);
	AT_L2_WAIT(0, DmaR_Evt1); /* Wait previous DMA read Bias */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1;
			{ /* Single iteration on D0 */
				int D0Ind_Last = 1;
				/*====================== Call Kernel LOC_D0 =========================*/
				AT_FORK(gap_ncore(), (void *) KerPar_MM_Conv1D_ReLU_fp16, (void *) KerArg0);
				__CALL(KerPar_MM_Conv1D_ReLU_fp16, KerArg0);
			} /* End iteration on D0 */
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+30208), 5120, 1, DmaW_Evt1);
	AT_L2_WAIT(0, DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S12_Conv_4_fusion(
		F16 * __restrict__ In,
		F16 * __restrict__ Filter,
		F16 * __restrict__ Bias,
		F16 * __restrict__ Out)

{
	/* Shared L1: 35328 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT _DmaR_Evt1, *DmaR_Evt1 = &_DmaR_Evt1;
	AT_L2_EVENT _DmaW_Evt1, *DmaW_Evt1 = &_DmaW_Evt1;
	Ker_MM_Conv_fp16_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int D1Ind, D1Ind_Last;
	int T0Ind, T0Ind_Last;
	int D0Ind, D0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 64, Tiled: 1][Tile0 Dim: 1][D0 Dim: Init: 64, Tiled: 1]
	Ker Arg: KerBuff, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 0 (Total Size: 384 )[Tile0, 1:[192x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[192x1], 2]
		Tile0: [0, 384, 384], Tile1: [0, 384, 384], Tile2; [0, 384, 384]
	Ker Arg: In, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 384 (Total Size: 5120 )[D0, [0 x 5120, 5120]][Tile0, 1:[40x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[40x1], 2][D0, [0 x 5120, 5120]]
		Tile0: [0, 5120, 5120], Tile1: [0, 5120, 5120], Tile2; [0, 5120, 5120]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 5504 (Total Size: 128 )[D1, [0 x 128, 128]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 128, 128]]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 5632 (Total Size: 24576 )[D1, [0 x 24576, 24576]][D0, [0 x 384, 384]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 24576, 24576]][D0, [0 x 384, 384]]
		Tile0: [0, 24576, 24576], Tile1: [0, 24576, 24576], Tile2; [0, 24576, 24576]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 30208 (Total Size: 5120 )[D1, [0 x 5120, 5120]][Tile0, 1:[40x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 5120, 5120]][Tile0, 1:[40x1], 2]
		Tile0: [0, 5120, 5120], Tile1: [0, 5120, 5120], Tile2; [0, 5120, 5120]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (F16 * __restrict__) (Gym_L1_Memory+384);
	KerArg0->W = (unsigned short int) (40);
	KerArg0->H = (unsigned short int) (1);
	KerArg0->Fx = (unsigned char) (3);
	KerArg0->Sx = (unsigned char) (1);
	KerArg0->Sy = (unsigned char) (1);
	KerArg0->FirstTile = (unsigned char) ((1));
	KerArg0->Pad = (v4s) ((v4s){1,1,0,0});
	KerArg0->Filter = (F16 * __restrict__) (Gym_L1_Memory+5632);
	KerArg0->Bias = (F16 * __restrict__) (Gym_L1_Memory+5504);
	KerArg0->Out = (F16 * __restrict__) (Gym_L1_Memory+30208);
	KerArg0->InFeat = (unsigned short int) (64);
	KerArg0->OutFeat = (unsigned short int) (64);
	KerArg0->Wo = (unsigned short int) (40);
	KerArg0->Ho = (unsigned short int) (1);
	KerArg0->ColBuff = (F16 * __restrict__) (Gym_L1_Memory+0);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+5632), 24576, 0, DmaR_Evt1);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+384), 5120, 0, 0);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+5504), 128, 0, 0);
	AT_L2_WAIT(0, DmaR_Evt1); /* Wait previous DMA read Bias */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1;
			{ /* Single iteration on D0 */
				int D0Ind_Last = 1;
				/*====================== Call Kernel LOC_D0 =========================*/
				AT_FORK(gap_ncore(), (void *) KerPar_MM_Conv1D_ReLU_fp16, (void *) KerArg0);
				__CALL(KerPar_MM_Conv1D_ReLU_fp16, KerArg0);
			} /* End iteration on D0 */
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+30208), 5120, 1, DmaW_Evt1);
	AT_L2_WAIT(0, DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S15_Conv_6(
		F16 * __restrict__ In,
		F16 * __restrict__ Filter,
		F16 * __restrict__ Bias,
		F16 * __restrict__ Out)

{
	/* Shared L1: 35328 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT _DmaR_Evt1, *DmaR_Evt1 = &_DmaR_Evt1;
	AT_L2_EVENT _DmaW_Evt1, *DmaW_Evt1 = &_DmaW_Evt1;
	Ker_MM_Conv_fp16_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int D1Ind, D1Ind_Last;
	int T0Ind, T0Ind_Last;
	int D0Ind, D0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 64, Tiled: 1][Tile0 Dim: 1][D0 Dim: Init: 64, Tiled: 1]
	Ker Arg: KerBuff, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 0 (Total Size: 384 )[Tile0, 1:[192x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[192x1], 2]
		Tile0: [0, 384, 384], Tile1: [0, 384, 384], Tile2; [0, 384, 384]
	Ker Arg: In, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 384 (Total Size: 5120 )[D0, [0 x 5120, 5120]][Tile0, 1:[40x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[40x1], 2][D0, [0 x 5120, 5120]]
		Tile0: [0, 5120, 5120], Tile1: [0, 5120, 5120], Tile2; [0, 5120, 5120]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 5504 (Total Size: 128 )[D1, [0 x 128, 128]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 128, 128]]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 5632 (Total Size: 24576 )[D1, [0 x 24576, 24576]][D0, [0 x 384, 384]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 24576, 24576]][D0, [0 x 384, 384]]
		Tile0: [0, 24576, 24576], Tile1: [0, 24576, 24576], Tile2; [0, 24576, 24576]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 30208 (Total Size: 5120 )[D1, [0 x 5120, 5120]][Tile0, 1:[40x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 5120, 5120]][Tile0, 1:[40x1], 2]
		Tile0: [0, 5120, 5120], Tile1: [0, 5120, 5120], Tile2; [0, 5120, 5120]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (F16 * __restrict__) (Gym_L1_Memory+384);
	KerArg0->W = (unsigned short int) (40);
	KerArg0->H = (unsigned short int) (1);
	KerArg0->Fx = (unsigned char) (3);
	KerArg0->Sx = (unsigned char) (1);
	KerArg0->Sy = (unsigned char) (1);
	KerArg0->FirstTile = (unsigned char) ((1));
	KerArg0->Pad = (v4s) ((v4s){1,1,0,0});
	KerArg0->Filter = (F16 * __restrict__) (Gym_L1_Memory+5632);
	KerArg0->Bias = (F16 * __restrict__) (Gym_L1_Memory+5504);
	KerArg0->Out = (F16 * __restrict__) (Gym_L1_Memory+30208);
	KerArg0->InFeat = (unsigned short int) (64);
	KerArg0->OutFeat = (unsigned short int) (64);
	KerArg0->Wo = (unsigned short int) (40);
	KerArg0->Ho = (unsigned short int) (1);
	KerArg0->ColBuff = (F16 * __restrict__) (Gym_L1_Memory+0);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+5632), 24576, 0, DmaR_Evt1);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+384), 5120, 0, 0);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+5504), 128, 0, 0);
	AT_L2_WAIT(0, DmaR_Evt1); /* Wait previous DMA read Bias */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1;
			{ /* Single iteration on D0 */
				int D0Ind_Last = 1;
				/*====================== Call Kernel LOC_D0 =========================*/
				AT_FORK(gap_ncore(), (void *) KerPar_MM_Conv1D_fp16, (void *) KerArg0);
				__CALL(KerPar_MM_Conv1D_fp16, KerArg0);
			} /* End iteration on D0 */
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+30208), 5120, 1, DmaW_Evt1);
	AT_L2_WAIT(0, DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S17_Add_7_fusion(
		F16 * __restrict__ In1,
		F16 * __restrict__ In2,
		F16 * __restrict__ Out)

{
	/* Shared L1: 15360 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT _DmaR_Evt1, *DmaR_Evt1 = &_DmaR_Evt1;
	AT_L2_EVENT _DmaW_Evt1, *DmaW_Evt1 = &_DmaW_Evt1;
	KerMat3_fp16_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int D0Ind, D0Ind_Last;
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D0 Dim: Init: 1, Tiled: 1][Tile0 Dim: 1]
	Ker Arg: In1, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 0 (Total Size: 5120 )[D0, [0 x 5120, 5120]][Tile0, 1:[64x40], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 5120, 5120]][Tile0, 1:[64x40], 2]
		Tile0: [0, 5120, 5120], Tile1: [0, 5120, 5120], Tile2; [0, 5120, 5120]
	Ker Arg: In2, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 5120 (Total Size: 5120 )[D0, [0 x 5120, 5120]][Tile0, 1:[64x40], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 5120, 5120]][Tile0, 1:[64x40], 2]
		Tile0: [0, 5120, 5120], Tile1: [0, 5120, 5120], Tile2; [0, 5120, 5120]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 10240 (Total Size: 5120 )[D0, [0 x 5120, 5120]][Tile0, 1:[64x40], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 5120, 5120]][Tile0, 1:[64x40], 2]
		Tile0: [0, 5120, 5120], Tile1: [0, 5120, 5120], Tile2; [0, 5120, 5120]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In1 = (F16 *__restrict__) (Gym_L1_Memory+0);
	KerArg0->In2 = (F16 *__restrict__) (Gym_L1_Memory+5120);
	KerArg0->Out = (F16 *__restrict__) (Gym_L1_Memory+10240);
	KerArg0->W = (unsigned short int) (64);
	KerArg0->H = (unsigned short int) (40);
	KerArg0->N = (unsigned short int) (1);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In1+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+0), 5120, 0, DmaR_Evt1);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) In2+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+5120), 5120, 0, 0);
	AT_L2_WAIT(0, DmaR_Evt1); /* Wait previous DMA read In2 */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D0 */
		int D0Ind_Last = 1;
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1;
			/*====================== Call Kernel LOC_LOOP =========================*/
			AT_FORK(gap_ncore(), (void *) KerParMatAddReLU_fp16, (void *) KerArg0);
			__CALL(KerParMatAddReLU_fp16, KerArg0);
		} /* End iteration on Tile0 */
	} /* End iteration on D0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+10240), 5120, 1, DmaW_Evt1);
	AT_L2_WAIT(0, DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S21_Conv_9_fusion(
		F16 * __restrict__ In,
		F16 * __restrict__ Filter,
		F16 * __restrict__ Bias,
		F16 * __restrict__ Out)

{
	/* Shared L1: 35328 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT _DmaR_Evt1, *DmaR_Evt1 = &_DmaR_Evt1;
	AT_L2_EVENT _DmaW_Evt1, *DmaW_Evt1 = &_DmaW_Evt1;
	Ker_MM_Conv_fp16_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int D1Ind, D1Ind_Last;
	int T0Ind, T0Ind_Last;
	int D0Ind, D0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 64, Tiled: 1][Tile0 Dim: 1][D0 Dim: Init: 64, Tiled: 1]
	Ker Arg: KerBuff, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 0 (Total Size: 384 )[Tile0, 1:[192x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[192x1], 2]
		Tile0: [0, 384, 384], Tile1: [0, 384, 384], Tile2; [0, 384, 384]
	Ker Arg: In, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 384 (Total Size: 5120 )[D0, [0 x 5120, 5120]][Tile0, 1:[40x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[40x1], 2][D0, [0 x 5120, 5120]]
		Tile0: [0, 5120, 5120], Tile1: [0, 5120, 5120], Tile2; [0, 5120, 5120]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 5504 (Total Size: 128 )[D1, [0 x 128, 128]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 128, 128]]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 5632 (Total Size: 24576 )[D1, [0 x 24576, 24576]][D0, [0 x 384, 384]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 24576, 24576]][D0, [0 x 384, 384]]
		Tile0: [0, 24576, 24576], Tile1: [0, 24576, 24576], Tile2; [0, 24576, 24576]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 30208 (Total Size: 5120 )[D1, [0 x 5120, 5120]][Tile0, 1:[40x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 5120, 5120]][Tile0, 1:[40x1], 2]
		Tile0: [0, 5120, 5120], Tile1: [0, 5120, 5120], Tile2; [0, 5120, 5120]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (F16 * __restrict__) (Gym_L1_Memory+384);
	KerArg0->W = (unsigned short int) (40);
	KerArg0->H = (unsigned short int) (1);
	KerArg0->Fx = (unsigned char) (3);
	KerArg0->Sx = (unsigned char) (1);
	KerArg0->Sy = (unsigned char) (1);
	KerArg0->FirstTile = (unsigned char) ((1));
	KerArg0->Pad = (v4s) ((v4s){1,1,0,0});
	KerArg0->Filter = (F16 * __restrict__) (Gym_L1_Memory+5632);
	KerArg0->Bias = (F16 * __restrict__) (Gym_L1_Memory+5504);
	KerArg0->Out = (F16 * __restrict__) (Gym_L1_Memory+30208);
	KerArg0->InFeat = (unsigned short int) (64);
	KerArg0->OutFeat = (unsigned short int) (64);
	KerArg0->Wo = (unsigned short int) (40);
	KerArg0->Ho = (unsigned short int) (1);
	KerArg0->ColBuff = (F16 * __restrict__) (Gym_L1_Memory+0);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+5632), 24576, 0, DmaR_Evt1);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+384), 5120, 0, 0);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+5504), 128, 0, 0);
	AT_L2_WAIT(0, DmaR_Evt1); /* Wait previous DMA read Bias */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1;
			{ /* Single iteration on D0 */
				int D0Ind_Last = 1;
				/*====================== Call Kernel LOC_D0 =========================*/
				AT_FORK(gap_ncore(), (void *) KerPar_MM_Conv1D_ReLU_fp16, (void *) KerArg0);
				__CALL(KerPar_MM_Conv1D_ReLU_fp16, KerArg0);
			} /* End iteration on D0 */
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+30208), 5120, 1, DmaW_Evt1);
	AT_L2_WAIT(0, DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S24_Conv_11_fusion(
		F16 * __restrict__ In,
		F16 * __restrict__ Filter,
		F16 * __restrict__ Bias,
		F16 * __restrict__ Out)

{
	/* Shared L1: 35328 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT _DmaR_Evt1, *DmaR_Evt1 = &_DmaR_Evt1;
	AT_L2_EVENT _DmaW_Evt1, *DmaW_Evt1 = &_DmaW_Evt1;
	Ker_MM_Conv_fp16_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int D1Ind, D1Ind_Last;
	int T0Ind, T0Ind_Last;
	int D0Ind, D0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 64, Tiled: 1][Tile0 Dim: 1][D0 Dim: Init: 64, Tiled: 1]
	Ker Arg: KerBuff, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 0 (Total Size: 384 )[Tile0, 1:[192x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[192x1], 2]
		Tile0: [0, 384, 384], Tile1: [0, 384, 384], Tile2; [0, 384, 384]
	Ker Arg: In, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 384 (Total Size: 5120 )[D0, [0 x 5120, 5120]][Tile0, 1:[40x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[40x1], 2][D0, [0 x 5120, 5120]]
		Tile0: [0, 5120, 5120], Tile1: [0, 5120, 5120], Tile2; [0, 5120, 5120]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 5504 (Total Size: 128 )[D1, [0 x 128, 128]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 128, 128]]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 5632 (Total Size: 24576 )[D1, [0 x 24576, 24576]][D0, [0 x 384, 384]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 24576, 24576]][D0, [0 x 384, 384]]
		Tile0: [0, 24576, 24576], Tile1: [0, 24576, 24576], Tile2; [0, 24576, 24576]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 30208 (Total Size: 5120 )[D1, [0 x 5120, 5120]][Tile0, 1:[40x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 5120, 5120]][Tile0, 1:[40x1], 2]
		Tile0: [0, 5120, 5120], Tile1: [0, 5120, 5120], Tile2; [0, 5120, 5120]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (F16 * __restrict__) (Gym_L1_Memory+384);
	KerArg0->W = (unsigned short int) (40);
	KerArg0->H = (unsigned short int) (1);
	KerArg0->Fx = (unsigned char) (3);
	KerArg0->Sx = (unsigned char) (1);
	KerArg0->Sy = (unsigned char) (1);
	KerArg0->FirstTile = (unsigned char) ((1));
	KerArg0->Pad = (v4s) ((v4s){1,1,0,0});
	KerArg0->Filter = (F16 * __restrict__) (Gym_L1_Memory+5632);
	KerArg0->Bias = (F16 * __restrict__) (Gym_L1_Memory+5504);
	KerArg0->Out = (F16 * __restrict__) (Gym_L1_Memory+30208);
	KerArg0->InFeat = (unsigned short int) (64);
	KerArg0->OutFeat = (unsigned short int) (64);
	KerArg0->Wo = (unsigned short int) (40);
	KerArg0->Ho = (unsigned short int) (1);
	KerArg0->ColBuff = (F16 * __restrict__) (Gym_L1_Memory+0);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+5632), 24576, 0, DmaR_Evt1);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+384), 5120, 0, 0);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+5504), 128, 0, 0);
	AT_L2_WAIT(0, DmaR_Evt1); /* Wait previous DMA read Bias */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1;
			{ /* Single iteration on D0 */
				int D0Ind_Last = 1;
				/*====================== Call Kernel LOC_D0 =========================*/
				AT_FORK(gap_ncore(), (void *) KerPar_MM_Conv1D_ReLU_fp16, (void *) KerArg0);
				__CALL(KerPar_MM_Conv1D_ReLU_fp16, KerArg0);
			} /* End iteration on D0 */
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+30208), 5120, 1, DmaW_Evt1);
	AT_L2_WAIT(0, DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S27_Conv_13(
		F16 * __restrict__ In,
		F16 * __restrict__ Filter,
		F16 * __restrict__ Bias,
		F16 * __restrict__ Out)

{
	/* Shared L1: 35328 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT _DmaR_Evt1, *DmaR_Evt1 = &_DmaR_Evt1;
	AT_L2_EVENT _DmaW_Evt1, *DmaW_Evt1 = &_DmaW_Evt1;
	Ker_MM_Conv_fp16_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int D1Ind, D1Ind_Last;
	int T0Ind, T0Ind_Last;
	int D0Ind, D0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 64, Tiled: 1][Tile0 Dim: 1][D0 Dim: Init: 64, Tiled: 1]
	Ker Arg: KerBuff, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 0 (Total Size: 384 )[Tile0, 1:[192x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[192x1], 2]
		Tile0: [0, 384, 384], Tile1: [0, 384, 384], Tile2; [0, 384, 384]
	Ker Arg: In, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 384 (Total Size: 5120 )[D0, [0 x 5120, 5120]][Tile0, 1:[40x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[40x1], 2][D0, [0 x 5120, 5120]]
		Tile0: [0, 5120, 5120], Tile1: [0, 5120, 5120], Tile2; [0, 5120, 5120]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 5504 (Total Size: 128 )[D1, [0 x 128, 128]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 128, 128]]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 5632 (Total Size: 24576 )[D1, [0 x 24576, 24576]][D0, [0 x 384, 384]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 24576, 24576]][D0, [0 x 384, 384]]
		Tile0: [0, 24576, 24576], Tile1: [0, 24576, 24576], Tile2; [0, 24576, 24576]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 30208 (Total Size: 5120 )[D1, [0 x 5120, 5120]][Tile0, 1:[40x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 5120, 5120]][Tile0, 1:[40x1], 2]
		Tile0: [0, 5120, 5120], Tile1: [0, 5120, 5120], Tile2; [0, 5120, 5120]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (F16 * __restrict__) (Gym_L1_Memory+384);
	KerArg0->W = (unsigned short int) (40);
	KerArg0->H = (unsigned short int) (1);
	KerArg0->Fx = (unsigned char) (3);
	KerArg0->Sx = (unsigned char) (1);
	KerArg0->Sy = (unsigned char) (1);
	KerArg0->FirstTile = (unsigned char) ((1));
	KerArg0->Pad = (v4s) ((v4s){1,1,0,0});
	KerArg0->Filter = (F16 * __restrict__) (Gym_L1_Memory+5632);
	KerArg0->Bias = (F16 * __restrict__) (Gym_L1_Memory+5504);
	KerArg0->Out = (F16 * __restrict__) (Gym_L1_Memory+30208);
	KerArg0->InFeat = (unsigned short int) (64);
	KerArg0->OutFeat = (unsigned short int) (64);
	KerArg0->Wo = (unsigned short int) (40);
	KerArg0->Ho = (unsigned short int) (1);
	KerArg0->ColBuff = (F16 * __restrict__) (Gym_L1_Memory+0);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+5632), 24576, 0, DmaR_Evt1);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+384), 5120, 0, 0);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+5504), 128, 0, 0);
	AT_L2_WAIT(0, DmaR_Evt1); /* Wait previous DMA read Bias */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1;
			{ /* Single iteration on D0 */
				int D0Ind_Last = 1;
				/*====================== Call Kernel LOC_D0 =========================*/
				AT_FORK(gap_ncore(), (void *) KerPar_MM_Conv1D_fp16, (void *) KerArg0);
				__CALL(KerPar_MM_Conv1D_fp16, KerArg0);
			} /* End iteration on D0 */
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+30208), 5120, 1, DmaW_Evt1);
	AT_L2_WAIT(0, DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S29_Add_14_fusion(
		F16 * __restrict__ In1,
		F16 * __restrict__ In2,
		F16 * __restrict__ Out)

{
	/* Shared L1: 15360 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT _DmaR_Evt1, *DmaR_Evt1 = &_DmaR_Evt1;
	AT_L2_EVENT _DmaW_Evt1, *DmaW_Evt1 = &_DmaW_Evt1;
	KerMat3_fp16_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int D0Ind, D0Ind_Last;
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D0 Dim: Init: 1, Tiled: 1][Tile0 Dim: 1]
	Ker Arg: In1, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 0 (Total Size: 5120 )[D0, [0 x 5120, 5120]][Tile0, 1:[64x40], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 5120, 5120]][Tile0, 1:[64x40], 2]
		Tile0: [0, 5120, 5120], Tile1: [0, 5120, 5120], Tile2; [0, 5120, 5120]
	Ker Arg: In2, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 5120 (Total Size: 5120 )[D0, [0 x 5120, 5120]][Tile0, 1:[64x40], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 5120, 5120]][Tile0, 1:[64x40], 2]
		Tile0: [0, 5120, 5120], Tile1: [0, 5120, 5120], Tile2; [0, 5120, 5120]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 10240 (Total Size: 5120 )[D0, [0 x 5120, 5120]][Tile0, 1:[64x40], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 5120, 5120]][Tile0, 1:[64x40], 2]
		Tile0: [0, 5120, 5120], Tile1: [0, 5120, 5120], Tile2; [0, 5120, 5120]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In1 = (F16 *__restrict__) (Gym_L1_Memory+0);
	KerArg0->In2 = (F16 *__restrict__) (Gym_L1_Memory+5120);
	KerArg0->Out = (F16 *__restrict__) (Gym_L1_Memory+10240);
	KerArg0->W = (unsigned short int) (64);
	KerArg0->H = (unsigned short int) (40);
	KerArg0->N = (unsigned short int) (1);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In1+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+0), 5120, 0, DmaR_Evt1);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) In2+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+5120), 5120, 0, 0);
	AT_L2_WAIT(0, DmaR_Evt1); /* Wait previous DMA read In2 */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D0 */
		int D0Ind_Last = 1;
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1;
			/*====================== Call Kernel LOC_LOOP =========================*/
			AT_FORK(gap_ncore(), (void *) KerParMatAddReLU_fp16, (void *) KerArg0);
			__CALL(KerParMatAddReLU_fp16, KerArg0);
		} /* End iteration on Tile0 */
	} /* End iteration on D0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+10240), 5120, 1, DmaW_Evt1);
	AT_L2_WAIT(0, DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S33_Conv_16_fusion(
		F16 * __restrict__ In,
		F16 * __restrict__ Filter,
		F16 * __restrict__ Bias,
		F16 * __restrict__ Out)

{
	/* Shared L1: 35328 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT _DmaR_Evt1, *DmaR_Evt1 = &_DmaR_Evt1;
	AT_L2_EVENT _DmaW_Evt1, *DmaW_Evt1 = &_DmaW_Evt1;
	Ker_MM_Conv_fp16_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int D1Ind, D1Ind_Last;
	int T0Ind, T0Ind_Last;
	int D0Ind, D0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 64, Tiled: 1][Tile0 Dim: 1][D0 Dim: Init: 64, Tiled: 1]
	Ker Arg: KerBuff, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 0 (Total Size: 384 )[Tile0, 1:[192x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[192x1], 2]
		Tile0: [0, 384, 384], Tile1: [0, 384, 384], Tile2; [0, 384, 384]
	Ker Arg: In, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 384 (Total Size: 5120 )[D0, [0 x 5120, 5120]][Tile0, 1:[40x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[40x1], 2][D0, [0 x 5120, 5120]]
		Tile0: [0, 5120, 5120], Tile1: [0, 5120, 5120], Tile2; [0, 5120, 5120]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 5504 (Total Size: 128 )[D1, [0 x 128, 128]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 128, 128]]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 5632 (Total Size: 24576 )[D1, [0 x 24576, 24576]][D0, [0 x 384, 384]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 24576, 24576]][D0, [0 x 384, 384]]
		Tile0: [0, 24576, 24576], Tile1: [0, 24576, 24576], Tile2; [0, 24576, 24576]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 30208 (Total Size: 5120 )[D1, [0 x 5120, 5120]][Tile0, 1:[40x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 5120, 5120]][Tile0, 1:[40x1], 2]
		Tile0: [0, 5120, 5120], Tile1: [0, 5120, 5120], Tile2; [0, 5120, 5120]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (F16 * __restrict__) (Gym_L1_Memory+384);
	KerArg0->W = (unsigned short int) (40);
	KerArg0->H = (unsigned short int) (1);
	KerArg0->Fx = (unsigned char) (3);
	KerArg0->Sx = (unsigned char) (1);
	KerArg0->Sy = (unsigned char) (1);
	KerArg0->FirstTile = (unsigned char) ((1));
	KerArg0->Pad = (v4s) ((v4s){1,1,0,0});
	KerArg0->Filter = (F16 * __restrict__) (Gym_L1_Memory+5632);
	KerArg0->Bias = (F16 * __restrict__) (Gym_L1_Memory+5504);
	KerArg0->Out = (F16 * __restrict__) (Gym_L1_Memory+30208);
	KerArg0->InFeat = (unsigned short int) (64);
	KerArg0->OutFeat = (unsigned short int) (64);
	KerArg0->Wo = (unsigned short int) (40);
	KerArg0->Ho = (unsigned short int) (1);
	KerArg0->ColBuff = (F16 * __restrict__) (Gym_L1_Memory+0);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+5632), 24576, 0, DmaR_Evt1);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+384), 5120, 0, 0);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+5504), 128, 0, 0);
	AT_L2_WAIT(0, DmaR_Evt1); /* Wait previous DMA read Bias */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1;
			{ /* Single iteration on D0 */
				int D0Ind_Last = 1;
				/*====================== Call Kernel LOC_D0 =========================*/
				AT_FORK(gap_ncore(), (void *) KerPar_MM_Conv1D_ReLU_fp16, (void *) KerArg0);
				__CALL(KerPar_MM_Conv1D_ReLU_fp16, KerArg0);
			} /* End iteration on D0 */
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+30208), 5120, 1, DmaW_Evt1);
	AT_L2_WAIT(0, DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S36_Conv_18_fusion(
		F16 * __restrict__ In,
		F16 * __restrict__ Filter,
		F16 * __restrict__ Bias,
		F16 * __restrict__ Out)

{
	/* Shared L1: 35328 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT _DmaR_Evt1, *DmaR_Evt1 = &_DmaR_Evt1;
	AT_L2_EVENT _DmaW_Evt1, *DmaW_Evt1 = &_DmaW_Evt1;
	Ker_MM_Conv_fp16_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int D1Ind, D1Ind_Last;
	int T0Ind, T0Ind_Last;
	int D0Ind, D0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 64, Tiled: 1][Tile0 Dim: 1][D0 Dim: Init: 64, Tiled: 1]
	Ker Arg: KerBuff, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 0 (Total Size: 384 )[Tile0, 1:[192x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[192x1], 2]
		Tile0: [0, 384, 384], Tile1: [0, 384, 384], Tile2; [0, 384, 384]
	Ker Arg: In, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 384 (Total Size: 5120 )[D0, [0 x 5120, 5120]][Tile0, 1:[40x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[40x1], 2][D0, [0 x 5120, 5120]]
		Tile0: [0, 5120, 5120], Tile1: [0, 5120, 5120], Tile2; [0, 5120, 5120]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 5504 (Total Size: 128 )[D1, [0 x 128, 128]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 128, 128]]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 5632 (Total Size: 24576 )[D1, [0 x 24576, 24576]][D0, [0 x 384, 384]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 24576, 24576]][D0, [0 x 384, 384]]
		Tile0: [0, 24576, 24576], Tile1: [0, 24576, 24576], Tile2; [0, 24576, 24576]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 30208 (Total Size: 5120 )[D1, [0 x 5120, 5120]][Tile0, 1:[40x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 5120, 5120]][Tile0, 1:[40x1], 2]
		Tile0: [0, 5120, 5120], Tile1: [0, 5120, 5120], Tile2; [0, 5120, 5120]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (F16 * __restrict__) (Gym_L1_Memory+384);
	KerArg0->W = (unsigned short int) (40);
	KerArg0->H = (unsigned short int) (1);
	KerArg0->Fx = (unsigned char) (3);
	KerArg0->Sx = (unsigned char) (1);
	KerArg0->Sy = (unsigned char) (1);
	KerArg0->FirstTile = (unsigned char) ((1));
	KerArg0->Pad = (v4s) ((v4s){1,1,0,0});
	KerArg0->Filter = (F16 * __restrict__) (Gym_L1_Memory+5632);
	KerArg0->Bias = (F16 * __restrict__) (Gym_L1_Memory+5504);
	KerArg0->Out = (F16 * __restrict__) (Gym_L1_Memory+30208);
	KerArg0->InFeat = (unsigned short int) (64);
	KerArg0->OutFeat = (unsigned short int) (64);
	KerArg0->Wo = (unsigned short int) (40);
	KerArg0->Ho = (unsigned short int) (1);
	KerArg0->ColBuff = (F16 * __restrict__) (Gym_L1_Memory+0);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+5632), 24576, 0, DmaR_Evt1);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+384), 5120, 0, 0);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+5504), 128, 0, 0);
	AT_L2_WAIT(0, DmaR_Evt1); /* Wait previous DMA read Bias */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1;
			{ /* Single iteration on D0 */
				int D0Ind_Last = 1;
				/*====================== Call Kernel LOC_D0 =========================*/
				AT_FORK(gap_ncore(), (void *) KerPar_MM_Conv1D_ReLU_fp16, (void *) KerArg0);
				__CALL(KerPar_MM_Conv1D_ReLU_fp16, KerArg0);
			} /* End iteration on D0 */
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+30208), 5120, 1, DmaW_Evt1);
	AT_L2_WAIT(0, DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S39_Conv_20(
		F16 * __restrict__ In,
		F16 * __restrict__ Filter,
		F16 * __restrict__ Bias,
		F16 * __restrict__ Out)

{
	/* Shared L1: 35328 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT _DmaR_Evt1, *DmaR_Evt1 = &_DmaR_Evt1;
	AT_L2_EVENT _DmaW_Evt1, *DmaW_Evt1 = &_DmaW_Evt1;
	Ker_MM_Conv_fp16_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int D1Ind, D1Ind_Last;
	int T0Ind, T0Ind_Last;
	int D0Ind, D0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 64, Tiled: 1][Tile0 Dim: 1][D0 Dim: Init: 64, Tiled: 1]
	Ker Arg: KerBuff, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 0 (Total Size: 384 )[Tile0, 1:[192x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[192x1], 2]
		Tile0: [0, 384, 384], Tile1: [0, 384, 384], Tile2; [0, 384, 384]
	Ker Arg: In, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 384 (Total Size: 5120 )[D0, [0 x 5120, 5120]][Tile0, 1:[40x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[40x1], 2][D0, [0 x 5120, 5120]]
		Tile0: [0, 5120, 5120], Tile1: [0, 5120, 5120], Tile2; [0, 5120, 5120]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 5504 (Total Size: 128 )[D1, [0 x 128, 128]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 128, 128]]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 5632 (Total Size: 24576 )[D1, [0 x 24576, 24576]][D0, [0 x 384, 384]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 24576, 24576]][D0, [0 x 384, 384]]
		Tile0: [0, 24576, 24576], Tile1: [0, 24576, 24576], Tile2; [0, 24576, 24576]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 30208 (Total Size: 5120 )[D1, [0 x 5120, 5120]][Tile0, 1:[40x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 5120, 5120]][Tile0, 1:[40x1], 2]
		Tile0: [0, 5120, 5120], Tile1: [0, 5120, 5120], Tile2; [0, 5120, 5120]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (F16 * __restrict__) (Gym_L1_Memory+384);
	KerArg0->W = (unsigned short int) (40);
	KerArg0->H = (unsigned short int) (1);
	KerArg0->Fx = (unsigned char) (3);
	KerArg0->Sx = (unsigned char) (1);
	KerArg0->Sy = (unsigned char) (1);
	KerArg0->FirstTile = (unsigned char) ((1));
	KerArg0->Pad = (v4s) ((v4s){1,1,0,0});
	KerArg0->Filter = (F16 * __restrict__) (Gym_L1_Memory+5632);
	KerArg0->Bias = (F16 * __restrict__) (Gym_L1_Memory+5504);
	KerArg0->Out = (F16 * __restrict__) (Gym_L1_Memory+30208);
	KerArg0->InFeat = (unsigned short int) (64);
	KerArg0->OutFeat = (unsigned short int) (64);
	KerArg0->Wo = (unsigned short int) (40);
	KerArg0->Ho = (unsigned short int) (1);
	KerArg0->ColBuff = (F16 * __restrict__) (Gym_L1_Memory+0);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+5632), 24576, 0, DmaR_Evt1);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+384), 5120, 0, 0);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+5504), 128, 0, 0);
	AT_L2_WAIT(0, DmaR_Evt1); /* Wait previous DMA read Bias */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1;
			{ /* Single iteration on D0 */
				int D0Ind_Last = 1;
				/*====================== Call Kernel LOC_D0 =========================*/
				AT_FORK(gap_ncore(), (void *) KerPar_MM_Conv1D_fp16, (void *) KerArg0);
				__CALL(KerPar_MM_Conv1D_fp16, KerArg0);
			} /* End iteration on D0 */
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+30208), 5120, 1, DmaW_Evt1);
	AT_L2_WAIT(0, DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S41_Add_21_fusion(
		F16 * __restrict__ In1,
		F16 * __restrict__ In2,
		F16 * __restrict__ Out)

{
	/* Shared L1: 15360 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT _DmaR_Evt1, *DmaR_Evt1 = &_DmaR_Evt1;
	AT_L2_EVENT _DmaW_Evt1, *DmaW_Evt1 = &_DmaW_Evt1;
	KerMat3_fp16_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int D0Ind, D0Ind_Last;
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D0 Dim: Init: 1, Tiled: 1][Tile0 Dim: 1]
	Ker Arg: In1, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 0 (Total Size: 5120 )[D0, [0 x 5120, 5120]][Tile0, 1:[64x40], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 5120, 5120]][Tile0, 1:[64x40], 2]
		Tile0: [0, 5120, 5120], Tile1: [0, 5120, 5120], Tile2; [0, 5120, 5120]
	Ker Arg: In2, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 5120 (Total Size: 5120 )[D0, [0 x 5120, 5120]][Tile0, 1:[64x40], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 5120, 5120]][Tile0, 1:[64x40], 2]
		Tile0: [0, 5120, 5120], Tile1: [0, 5120, 5120], Tile2; [0, 5120, 5120]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 10240 (Total Size: 5120 )[D0, [0 x 5120, 5120]][Tile0, 1:[64x40], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 5120, 5120]][Tile0, 1:[64x40], 2]
		Tile0: [0, 5120, 5120], Tile1: [0, 5120, 5120], Tile2; [0, 5120, 5120]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In1 = (F16 *__restrict__) (Gym_L1_Memory+0);
	KerArg0->In2 = (F16 *__restrict__) (Gym_L1_Memory+5120);
	KerArg0->Out = (F16 *__restrict__) (Gym_L1_Memory+10240);
	KerArg0->W = (unsigned short int) (64);
	KerArg0->H = (unsigned short int) (40);
	KerArg0->N = (unsigned short int) (1);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In1+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+0), 5120, 0, DmaR_Evt1);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) In2+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+5120), 5120, 0, 0);
	AT_L2_WAIT(0, DmaR_Evt1); /* Wait previous DMA read In2 */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D0 */
		int D0Ind_Last = 1;
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1;
			/*====================== Call Kernel LOC_LOOP =========================*/
			AT_FORK(gap_ncore(), (void *) KerParMatAddReLU_fp16, (void *) KerArg0);
			__CALL(KerParMatAddReLU_fp16, KerArg0);
		} /* End iteration on Tile0 */
	} /* End iteration on D0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+10240), 5120, 1, DmaW_Evt1);
	AT_L2_WAIT(0, DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S44_Gemm_30(
		F16 * __restrict__ In,
		F16 * __restrict__ Filter,
		F16 * __restrict__ Bias,
		F16 * __restrict__ Out)

{
	/* Shared L1: 66608 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT _DmaR_Evt1, *DmaR_Evt1 = &_DmaR_Evt1;
	AT_L2_EVENT _DmaW_Evt1, *DmaW_Evt1 = &_DmaW_Evt1;
	KerLinear_fp16_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int D0Ind, D0Ind_Last;
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D0 Dim: Init: 12, Tiled: 1][Tile0 Dim: 1]
	Ker Arg: In, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 0 (Total Size: 5120 )[Tile0, 1:[1x1], 5120]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x1], 5120]
		Tile0: [0, 5120, 5120], Tile1: [0, 5120, 5120], Tile2; [0, 5120, 5120]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 5120 (Total Size: 61440 )[D0, [0 x 61440, 61440]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 61440, 61440]]
		Tile0: [0, 61440, 61440], Tile1: [0, 61440, 61440], Tile2; [0, 61440, 61440]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 66560 (Total Size: 24 )[D0, [0 x 24, 24]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 24, 24]]
		Tile0: [0, 24, 24], Tile1: [0, 24, 24], Tile2; [0, 24, 24]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 66584 (Total Size: 24 )[D0, [0 x 24, 24]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 24, 24]]
		Tile0: [0, 24, 24], Tile1: [0, 24, 24], Tile2; [0, 24, 24]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (F16 * __restrict__) (Gym_L1_Memory+0);
	KerArg0->Filter = (F16 * __restrict__) (Gym_L1_Memory+5120);
	KerArg0->Bias = (F16 * __restrict__) (Gym_L1_Memory+66560);
	KerArg0->Out = (F16 * __restrict__) (Gym_L1_Memory+66584);
	KerArg0->InDim = (unsigned short int) (2560);
	KerArg0->TotalInDim = (unsigned short int) (2560);
	KerArg0->OutDim = (unsigned short int) (12);
	KerArg0->UB = (F16) (6.000000e+00);
	KerArg0->LB = (F16) (0.000000e+00);
	KerArg0->TileIndex = (unsigned short int) (0);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+5120), 61440, 0, DmaR_Evt1);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+0), 5120, 0, 0);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+66560), 24, 0, 0);
	AT_L2_WAIT(0, DmaR_Evt1); /* Wait previous DMA read Bias */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D0 */
		int D0Ind_Last = 1;
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1;
			/*====================== Call Kernel LOC_LOOP =========================*/
			AT_FORK(gap_ncore(), (void *) KerParLinearLayer_fp16, (void *) KerArg0);
			__CALL(KerParLinearLayer_fp16, KerArg0);
		} /* End iteration on Tile0 */
	} /* End iteration on D0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+66584), 24, 1, DmaW_Evt1);
	AT_L2_WAIT(0, DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S45_Softmax_31(
		F16 * __restrict__ In,
		F16 * __restrict__ Out)

{
	/* Shared L1: 48 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT _DmaR_Evt1, *DmaR_Evt1 = &_DmaR_Evt1;
	AT_L2_EVENT _DmaW_Evt1, *DmaW_Evt1 = &_DmaW_Evt1;
	KerSoftMax_fp16_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile0 Dim: 1]
	Ker Arg: In, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 0 (Total Size: 24 )[Tile0, 1:[12x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[12x1], 2]
		Tile0: [0, 24, 24], Tile1: [0, 24, 24], Tile2; [0, 24, 24]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 24 (Total Size: 24 )[Tile0, 1:[12x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[12x1], 2]
		Tile0: [0, 24, 24], Tile1: [0, 24, 24], Tile2; [0, 24, 24]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (F16 *__restrict__) (Gym_L1_Memory+0);
	KerArg0->Feat = (unsigned short int) (1);
	KerArg0->N = (unsigned short int) (12);
	KerArg0->Out = (F16 *__restrict__) (Gym_L1_Memory+24);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+0), 24, 0, DmaR_Evt1);
	AT_L2_WAIT(0, DmaR_Evt1); /* Wait previous DMA read In */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on Tile0 */
		int T0Ind_Last = 1;
		/*====================== Call Kernel LOC_LOOP =========================*/
		AT_FORK(gap_ncore(), (void *) KerParSoftMax_fp16, (void *) KerArg0);
		__CALL(KerParSoftMax_fp16, KerArg0);
	} /* End iteration on Tile0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+24), 24, 1, DmaW_Evt1);
	AT_L2_WAIT(0, DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
#pragma GCC diagnostic pop
int GymCNN_Construct()

{
	AT_DEFAULTFLASH_FS_CONF_T DefaultFlashConf;

	int Error;
	AT_DEFAULTFLASH_FS_CONF_INIT(&DefaultFlashConf, AT_MEM_L3_DEFAULTFLASH, 0);
	AT_DEFAULTFLASH_FS_OPEN(&DefaultFlash, &DefaultFlashConf, "Gym_L3_Flash_Const.dat", &Error);
	if (Error) return AT_FLASH_OPEN_ERROR;

	Gym_L2_Memory = (AT_L2_POINTER) AT_L2_ALLOC(0, 286616);
	if (Gym_L2_Memory == 0) return AT_L2_OPEN_ERROR;
	Gym_L2_Memory_Dyn = (AT_L2_POINTER) AT_L2_ALLOC(0, 20480);
	if (Gym_L2_Memory_Dyn == 0) return AT_L2_OPEN_ERROR;
	Gym_L1_Memory = (AT_L1_POINTER) AT_L1_ALLOC(0, 66608);
	if (Gym_L1_Memory == 0) return AT_L1_OPEN_ERROR;
	AT_DEFAULTFLASH_FS_FC_EVENT _UchanHF1, *UchanHF1 = &_UchanHF1;
	/* Static Moving Conv_0_weights, size 2688 from DefaultFlash at 282624 to (size 2688) L2 at 282624..285311 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Gym_L3_Flash + 282624), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Gym_L2_Memory + 282624), 2688, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_onnx__conv_120, size 128 from DefaultFlash at 285312 to (size 128) L2 at 285312..285439 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Gym_L3_Flash + 285312), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Gym_L2_Memory + 285312), 128, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Conv_2_weights, size 24576 from DefaultFlash at 61440 to (size 24576) L2 at 61440..86015 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Gym_L3_Flash + 61440), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Gym_L2_Memory + 61440), 24576, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_onnx__conv_123, size 128 from DefaultFlash at 285440 to (size 128) L2 at 285440..285567 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Gym_L3_Flash + 285440), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Gym_L2_Memory + 285440), 128, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Conv_4_weights, size 24576 from DefaultFlash at 86016 to (size 24576) L2 at 86016..110591 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Gym_L3_Flash + 86016), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Gym_L2_Memory + 86016), 24576, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_onnx__conv_126, size 128 from DefaultFlash at 285568 to (size 128) L2 at 285568..285695 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Gym_L3_Flash + 285568), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Gym_L2_Memory + 285568), 128, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Conv_6_weights, size 24576 from DefaultFlash at 110592 to (size 24576) L2 at 110592..135167 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Gym_L3_Flash + 110592), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Gym_L2_Memory + 110592), 24576, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_onnx__conv_129, size 128 from DefaultFlash at 285696 to (size 128) L2 at 285696..285823 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Gym_L3_Flash + 285696), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Gym_L2_Memory + 285696), 128, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Conv_9_weights, size 24576 from DefaultFlash at 135168 to (size 24576) L2 at 135168..159743 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Gym_L3_Flash + 135168), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Gym_L2_Memory + 135168), 24576, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_onnx__conv_132, size 128 from DefaultFlash at 285824 to (size 128) L2 at 285824..285951 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Gym_L3_Flash + 285824), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Gym_L2_Memory + 285824), 128, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Conv_11_weights, size 24576 from DefaultFlash at 159744 to (size 24576) L2 at 159744..184319 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Gym_L3_Flash + 159744), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Gym_L2_Memory + 159744), 24576, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_onnx__conv_135, size 128 from DefaultFlash at 285952 to (size 128) L2 at 285952..286079 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Gym_L3_Flash + 285952), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Gym_L2_Memory + 285952), 128, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Conv_13_weights, size 24576 from DefaultFlash at 184320 to (size 24576) L2 at 184320..208895 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Gym_L3_Flash + 184320), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Gym_L2_Memory + 184320), 24576, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_onnx__conv_138, size 128 from DefaultFlash at 286080 to (size 128) L2 at 286080..286207 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Gym_L3_Flash + 286080), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Gym_L2_Memory + 286080), 128, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Conv_16_weights, size 24576 from DefaultFlash at 208896 to (size 24576) L2 at 208896..233471 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Gym_L3_Flash + 208896), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Gym_L2_Memory + 208896), 24576, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_onnx__conv_141, size 128 from DefaultFlash at 286208 to (size 128) L2 at 286208..286335 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Gym_L3_Flash + 286208), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Gym_L2_Memory + 286208), 128, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Conv_18_weights, size 24576 from DefaultFlash at 233472 to (size 24576) L2 at 233472..258047 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Gym_L3_Flash + 233472), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Gym_L2_Memory + 233472), 24576, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_onnx__conv_144, size 128 from DefaultFlash at 286336 to (size 128) L2 at 286336..286463 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Gym_L3_Flash + 286336), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Gym_L2_Memory + 286336), 128, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Conv_20_weights, size 24576 from DefaultFlash at 258048 to (size 24576) L2 at 258048..282623 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Gym_L3_Flash + 258048), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Gym_L2_Memory + 258048), 24576, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_onnx__conv_147, size 128 from DefaultFlash at 286464 to (size 128) L2 at 286464..286591 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Gym_L3_Flash + 286464), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Gym_L2_Memory + 286464), 128, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Gemm_30_weights, size 61440 from DefaultFlash at 0 to (size 61440) L2 at 0..61439 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Gym_L3_Flash + 0), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Gym_L2_Memory + 0), 61440, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Gemm_30_biases, size 24 from DefaultFlash at 286592 to (size 24) L2 at 286592..286615 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Gym_L3_Flash + 286592), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Gym_L2_Memory + 286592), 24, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	return AT_NO_ERROR;
}
void GymCNN_ConstructCluster()

{
}
int GymCNN_Destruct()

{
	AT_L2_FREE(0, Gym_L2_Memory, 286616);
	AT_L2_FREE(0, Gym_L2_Memory_Dyn, 20480);
	AT_L1_FREE(0, Gym_L1_Memory, 66608);
	AT_DEFAULTFLASH_FS_CLOSE(&DefaultFlash);
	return 0;
}
int GymCNN_Memory(AT_MEM_TYPE Which)

{
	switch (Which) {
		case AT_L1_MEM:     return 66608; /* L1 Memory */
		case AT_L2_MEM:     return 286616; /* L2 Memory, permanent */
		case AT_L2_DYN_MEM: return 20480; /* L2 Memory, dynamic */
		case AT_L3_MEM:     return 0; /* L3 Memory, permanent */
		case AT_L3_DYN_MEM: return 0; /* L3 Memory, dynamic */
		default:            return 0;
	}
}
unsigned int AT_GraphPerf[16];
unsigned int AT_GraphPerf_CNN_Total = 0;
unsigned int AT_GraphOperInfosNames[16] = {
	56320,
	494080,
	494080,
	491520,
	2560,
	494080,
	494080,
	491520,
	2560,
	494080,
	494080,
	491520,
	2560,
	30720,
	12,
	0,
};
char *AT_GraphNodeNames[16] = {
	"S4_Conv_0_fusion",
	"S9_Conv_2_fusion",
	"S12_Conv_4_fusion",
	"S15_Conv_6",
	"S17_Add_7_fusion",
	"S21_Conv_9_fusion",
	"S24_Conv_11_fusion",
	"S27_Conv_13",
	"S29_Add_14_fusion",
	"S33_Conv_16_fusion",
	"S36_Conv_18_fusion",
	"S39_Conv_20",
	"S41_Add_21_fusion",
	"S44_Gemm_30",
	"S45_Softmax_31",
	"IO_Wait",
};
int GymCNN(
		F16 * __restrict__ Input_1,
		F16 * __restrict__ Output_1)

{
	unsigned int Start_IO;
	AT_GraphPerf_CNN_Total = gap_cl_readhwtimer();
	AT_GraphPerf[0] = gap_cl_readhwtimer();
	AT_GraphPerf[15] = 0;
	S4_Conv_0_fusion(
		((F16 * __restrict__) Input_1), /* In */
		((F16 * __restrict__) (Gym_L2_Memory+282624)), /* Filter */
		((F16 * __restrict__) (Gym_L2_Memory+285312)), /* Bias */
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+10240)) /* Out */
	);
	AT_GraphPerf[0] = gap_cl_readhwtimer() - AT_GraphPerf[0];
	AT_GraphPerf[1] = gap_cl_readhwtimer();
	S9_Conv_2_fusion(
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+10240)), /* In */
		((F16 * __restrict__) (Gym_L2_Memory+61440)), /* Filter */
		((F16 * __restrict__) (Gym_L2_Memory+285440)), /* Bias */
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+0)) /* Out */
	);
	AT_GraphPerf[1] = gap_cl_readhwtimer() - AT_GraphPerf[1];
	AT_GraphPerf[2] = gap_cl_readhwtimer();
	S12_Conv_4_fusion(
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+0)), /* In */
		((F16 * __restrict__) (Gym_L2_Memory+86016)), /* Filter */
		((F16 * __restrict__) (Gym_L2_Memory+285568)), /* Bias */
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+5120)) /* Out */
	);
	AT_GraphPerf[2] = gap_cl_readhwtimer() - AT_GraphPerf[2];
	AT_GraphPerf[3] = gap_cl_readhwtimer();
	S15_Conv_6(
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+5120)), /* In */
		((F16 * __restrict__) (Gym_L2_Memory+110592)), /* Filter */
		((F16 * __restrict__) (Gym_L2_Memory+285696)), /* Bias */
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+0)) /* Out */
	);
	AT_GraphPerf[3] = gap_cl_readhwtimer() - AT_GraphPerf[3];
	AT_GraphPerf[4] = gap_cl_readhwtimer();
	S17_Add_7_fusion(
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+0)), /* In1 */
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+10240)), /* In2 */
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+5120)) /* Out */
	);
	AT_GraphPerf[4] = gap_cl_readhwtimer() - AT_GraphPerf[4];
	AT_GraphPerf[5] = gap_cl_readhwtimer();
	S21_Conv_9_fusion(
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+5120)), /* In */
		((F16 * __restrict__) (Gym_L2_Memory+135168)), /* Filter */
		((F16 * __restrict__) (Gym_L2_Memory+285824)), /* Bias */
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+0)) /* Out */
	);
	AT_GraphPerf[5] = gap_cl_readhwtimer() - AT_GraphPerf[5];
	AT_GraphPerf[6] = gap_cl_readhwtimer();
	S24_Conv_11_fusion(
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+0)), /* In */
		((F16 * __restrict__) (Gym_L2_Memory+159744)), /* Filter */
		((F16 * __restrict__) (Gym_L2_Memory+285952)), /* Bias */
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+15360)) /* Out */
	);
	AT_GraphPerf[6] = gap_cl_readhwtimer() - AT_GraphPerf[6];
	AT_GraphPerf[7] = gap_cl_readhwtimer();
	S27_Conv_13(
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+15360)), /* In */
		((F16 * __restrict__) (Gym_L2_Memory+184320)), /* Filter */
		((F16 * __restrict__) (Gym_L2_Memory+286080)), /* Bias */
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+10240)) /* Out */
	);
	AT_GraphPerf[7] = gap_cl_readhwtimer() - AT_GraphPerf[7];
	AT_GraphPerf[8] = gap_cl_readhwtimer();
	S29_Add_14_fusion(
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+10240)), /* In1 */
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+5120)), /* In2 */
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+0)) /* Out */
	);
	AT_GraphPerf[8] = gap_cl_readhwtimer() - AT_GraphPerf[8];
	AT_GraphPerf[9] = gap_cl_readhwtimer();
	S33_Conv_16_fusion(
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+0)), /* In */
		((F16 * __restrict__) (Gym_L2_Memory+208896)), /* Filter */
		((F16 * __restrict__) (Gym_L2_Memory+286208)), /* Bias */
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+5120)) /* Out */
	);
	AT_GraphPerf[9] = gap_cl_readhwtimer() - AT_GraphPerf[9];
	AT_GraphPerf[10] = gap_cl_readhwtimer();
	S36_Conv_18_fusion(
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+5120)), /* In */
		((F16 * __restrict__) (Gym_L2_Memory+233472)), /* Filter */
		((F16 * __restrict__) (Gym_L2_Memory+286336)), /* Bias */
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+15360)) /* Out */
	);
	AT_GraphPerf[10] = gap_cl_readhwtimer() - AT_GraphPerf[10];
	AT_GraphPerf[11] = gap_cl_readhwtimer();
	S39_Conv_20(
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+15360)), /* In */
		((F16 * __restrict__) (Gym_L2_Memory+258048)), /* Filter */
		((F16 * __restrict__) (Gym_L2_Memory+286464)), /* Bias */
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+10240)) /* Out */
	);
	AT_GraphPerf[11] = gap_cl_readhwtimer() - AT_GraphPerf[11];
	AT_GraphPerf[12] = gap_cl_readhwtimer();
	S41_Add_21_fusion(
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+10240)), /* In1 */
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+0)), /* In2 */
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+5120)) /* Out */
	);
	AT_GraphPerf[12] = gap_cl_readhwtimer() - AT_GraphPerf[12];
	AT_GraphPerf[13] = gap_cl_readhwtimer();
	S44_Gemm_30(
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+5120)), /* In */
		((F16 * __restrict__) (Gym_L2_Memory+0)), /* Filter */
		((F16 * __restrict__) (Gym_L2_Memory+286592)), /* Bias */
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+0)) /* Out */
	);
	AT_GraphPerf[13] = gap_cl_readhwtimer() - AT_GraphPerf[13];
	AT_GraphPerf[14] = gap_cl_readhwtimer();
	S45_Softmax_31(
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+0)), /* In */
		((F16 * __restrict__) Output_1) /* Out */
	);
	AT_GraphPerf[14] = gap_cl_readhwtimer() - AT_GraphPerf[14];
	AT_GraphPerf_CNN_Total = gap_cl_readhwtimer() - AT_GraphPerf_CNN_Total;
	return 0;
}
