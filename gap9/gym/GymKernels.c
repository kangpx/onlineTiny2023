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
	/* Shared L1: 20416 bytes, L2 buffer: 0 bytes */
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
		[D1 Dim: Init: 32, Tiled: 1][Tile0 Dim: 1][D0 Dim: Init: 64, Tiled: 1]
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
			@ 5504 (Total Size: 64 )[D1, [0 x 64, 64]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 64, 64]]
		Tile0: [0, 64, 64], Tile1: [0, 64, 64], Tile2; [0, 64, 64]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 5568 (Total Size: 12288 )[D1, [0 x 12288, 12288]][D0, [0 x 384, 384]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 12288, 12288]][D0, [0 x 384, 384]]
		Tile0: [0, 12288, 12288], Tile1: [0, 12288, 12288], Tile2; [0, 12288, 12288]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 17856 (Total Size: 2560 )[D1, [0 x 2560, 2560]][Tile0, 1:[40x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 2560, 2560]][Tile0, 1:[40x1], 2]
		Tile0: [0, 2560, 2560], Tile1: [0, 2560, 2560], Tile2; [0, 2560, 2560]
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
	KerArg0->Filter = (F16 * __restrict__) (Gym_L1_Memory+5568);
	KerArg0->Bias = (F16 * __restrict__) (Gym_L1_Memory+5504);
	KerArg0->Out = (F16 * __restrict__) (Gym_L1_Memory+17856);
	KerArg0->InFeat = (unsigned short int) (64);
	KerArg0->OutFeat = (unsigned short int) (32);
	KerArg0->Wo = (unsigned short int) (40);
	KerArg0->Ho = (unsigned short int) (1);
	KerArg0->ColBuff = (F16 * __restrict__) (Gym_L1_Memory+0);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+5568), 12288, 0, DmaR_Evt1);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+384), 5120, 0, 0);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+5504), 64, 0, 0);
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
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+17856), 2560, 1, DmaW_Evt1);
	AT_L2_WAIT(0, DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S43_Conv_21(
		F16 * __restrict__ In2,
		F16 * __restrict__ In1,
		F16 * __restrict__ Bias,
		F16 * __restrict__ Out)

{
	/* Shared L1: 16960 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT _DmaR_Evt1, *DmaR_Evt1 = &_DmaR_Evt1;
	AT_L2_EVENT _DmaW_Evt1, *DmaW_Evt1 = &_DmaW_Evt1;
	KerMatTranspose_fp_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerMatMul_fp16_T S_KerArg1, *KerArg1 = &S_KerArg1;

	/* Iteration space related variables */
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile0 Dim: 1]
	Ker Arg: TransIn2, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 9216 (Total Size: 5120 )[Tile0, 1:[64x40], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[64x40], 2]
		Tile0: [0, 5120, 80], Tile1: [0, 5120, 80], Tile2; [0, 5120, 80]
	Ker Arg: In2, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 4096 (Total Size: 5120 )[Tile0, 1:[64x40], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[64x40], 2]
		Tile0: [0, 5120, 5120], Tile1: [0, 5120, 5120], Tile2; [0, 5120, 5120]
	Ker Arg: In1, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 0 (Total Size: 4096 )[Tile0, 1:[32x64], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[32x64], 2]
		Tile0: [0, 4096, 4096], Tile1: [0, 4096, 4096], Tile2; [0, 4096, 4096]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 14336 (Total Size: 64 )[Tile0, 1:[32x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[32x1], 2]
		Tile0: [0, 64, 64], Tile1: [0, 64, 64], Tile2; [0, 64, 64]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 14400 (Total Size: 2560 )[Tile0, 1:[32x40], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[32x40], 2]
		Tile0: [0, 2560, 2560], Tile1: [0, 2560, 2560], Tile2; [0, 2560, 2560]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (void *__restrict__) (Gym_L1_Memory+4096);
	KerArg0->Out = (void *__restrict__) (Gym_L1_Memory+9216);
	KerArg0->Feat = (unsigned short int) (1);
	KerArg0->W = (unsigned short int) (40);
	KerArg0->H = (unsigned short int) (64);
	KerArg1->In1 = (F16 * __restrict__) (Gym_L1_Memory+0);
	KerArg1->W_In1 = (unsigned short int) (64);
	KerArg1->H_In1 = (unsigned short int) (32);
	KerArg1->In2 = (F16 * __restrict__) (Gym_L1_Memory+9216);
	KerArg1->W_In2 = (unsigned short int) (40);
	KerArg1->Bias = (F16 * __restrict__) (Gym_L1_Memory+14336);
	KerArg1->Out = (F16 * __restrict__) (Gym_L1_Memory+14400);
	KerArg1->UB = (F16) (6.000000e+00);
	KerArg1->LB = (F16) (0.000000e+00);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In2+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+4096), 5120, 0, DmaR_Evt1);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) In1+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+0), 4096, 0, 0);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+14336), 64, 0, 0);
	AT_L2_WAIT(0, DmaR_Evt1); /* Wait previous DMA read Bias */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on Tile0 */
		int T0Ind_Last = 1;
		/*====================== Call Kernel LOC_LOOP =========================*/
		AT_FORK(gap_ncore(), (void *) CNN_Transpose_fp, (void *) KerArg0);
		__CALL(CNN_Transpose_fp, KerArg0);
		AT_FORK(gap_ncore(), (void *) KerParMatMulSmallFeat_fp16, (void *) KerArg1);
		__CALL(KerParMatMulSmallFeat_fp16, KerArg1);
	} /* End iteration on Tile0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+14400), 2560, 1, DmaW_Evt1);
	AT_L2_WAIT(0, DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S45_Add_22_fusion(
		F16 * __restrict__ In1,
		F16 * __restrict__ In2,
		F16 * __restrict__ Out)

{
	/* Shared L1: 7680 bytes, L2 buffer: 0 bytes */
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
			@ 0 (Total Size: 2560 )[D0, [0 x 2560, 2560]][Tile0, 1:[32x40], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 2560, 2560]][Tile0, 1:[32x40], 2]
		Tile0: [0, 2560, 2560], Tile1: [0, 2560, 2560], Tile2; [0, 2560, 2560]
	Ker Arg: In2, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 2560 (Total Size: 2560 )[D0, [0 x 2560, 2560]][Tile0, 1:[32x40], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 2560, 2560]][Tile0, 1:[32x40], 2]
		Tile0: [0, 2560, 2560], Tile1: [0, 2560, 2560], Tile2; [0, 2560, 2560]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 5120 (Total Size: 2560 )[D0, [0 x 2560, 2560]][Tile0, 1:[32x40], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 2560, 2560]][Tile0, 1:[32x40], 2]
		Tile0: [0, 2560, 2560], Tile1: [0, 2560, 2560], Tile2; [0, 2560, 2560]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In1 = (F16 *__restrict__) (Gym_L1_Memory+0);
	KerArg0->In2 = (F16 *__restrict__) (Gym_L1_Memory+2560);
	KerArg0->Out = (F16 *__restrict__) (Gym_L1_Memory+5120);
	KerArg0->W = (unsigned short int) (32);
	KerArg0->H = (unsigned short int) (40);
	KerArg0->N = (unsigned short int) (1);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In1+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+0), 2560, 0, DmaR_Evt1);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) In2+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+2560), 2560, 0, 0);
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
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+5120), 2560, 1, DmaW_Evt1);
	AT_L2_WAIT(0, DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S48_Gemm_31(
		F16 * __restrict__ In,
		F16 * __restrict__ Filter,
		F16 * __restrict__ Bias,
		F16 * __restrict__ Out)

{
	/* Shared L1: 33328 bytes, L2 buffer: 0 bytes */
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
			@ 0 (Total Size: 2560 )[Tile0, 1:[1x1], 2560]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x1], 2560]
		Tile0: [0, 2560, 2560], Tile1: [0, 2560, 2560], Tile2; [0, 2560, 2560]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 2560 (Total Size: 30720 )[D0, [0 x 30720, 30720]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 30720, 30720]]
		Tile0: [0, 30720, 30720], Tile1: [0, 30720, 30720], Tile2; [0, 30720, 30720]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 33280 (Total Size: 24 )[D0, [0 x 24, 24]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 24, 24]]
		Tile0: [0, 24, 24], Tile1: [0, 24, 24], Tile2; [0, 24, 24]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 33304 (Total Size: 24 )[D0, [0 x 24, 24]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 24, 24]]
		Tile0: [0, 24, 24], Tile1: [0, 24, 24], Tile2; [0, 24, 24]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (F16 * __restrict__) (Gym_L1_Memory+0);
	KerArg0->Filter = (F16 * __restrict__) (Gym_L1_Memory+2560);
	KerArg0->Bias = (F16 * __restrict__) (Gym_L1_Memory+33280);
	KerArg0->Out = (F16 * __restrict__) (Gym_L1_Memory+33304);
	KerArg0->InDim = (unsigned short int) (1280);
	KerArg0->TotalInDim = (unsigned short int) (1280);
	KerArg0->OutDim = (unsigned short int) (12);
	KerArg0->UB = (F16) (6.000000e+00);
	KerArg0->LB = (F16) (0.000000e+00);
	KerArg0->TileIndex = (unsigned short int) (0);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+2560), 30720, 0, DmaR_Evt1);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+0), 2560, 0, 0);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+33280), 24, 0, 0);
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
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) Gym_L1_Memory+33304), 24, 1, DmaW_Evt1);
	AT_L2_WAIT(0, DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S49_Softmax_32(
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

	Gym_L2_Memory = (AT_L2_POINTER) AT_L2_ALLOC(0, 247704);
	if (Gym_L2_Memory == 0) return AT_L2_OPEN_ERROR;
	Gym_L2_Memory_Dyn = (AT_L2_POINTER) AT_L2_ALLOC(0, 20480);
	if (Gym_L2_Memory_Dyn == 0) return AT_L2_OPEN_ERROR;
	Gym_L1_Memory = (AT_L1_POINTER) AT_L1_ALLOC(0, 35328);
	if (Gym_L1_Memory == 0) return AT_L1_OPEN_ERROR;
	AT_DEFAULTFLASH_FS_FC_EVENT _UchanHF1, *UchanHF1 = &_UchanHF1;
	/* Static Moving Conv_0_weights, size 2688 from DefaultFlash at 243712 to (size 2688) L2 at 243712..246399 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Gym_L3_Flash + 243712), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Gym_L2_Memory + 243712), 2688, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_onnx__conv_123, size 128 from DefaultFlash at 246400 to (size 128) L2 at 246400..246527 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Gym_L3_Flash + 246400), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Gym_L2_Memory + 246400), 128, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Conv_2_weights, size 24576 from DefaultFlash at 30720 to (size 24576) L2 at 30720..55295 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Gym_L3_Flash + 30720), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Gym_L2_Memory + 30720), 24576, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_onnx__conv_126, size 128 from DefaultFlash at 246528 to (size 128) L2 at 246528..246655 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Gym_L3_Flash + 246528), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Gym_L2_Memory + 246528), 128, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Conv_4_weights, size 24576 from DefaultFlash at 55296 to (size 24576) L2 at 55296..79871 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Gym_L3_Flash + 55296), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Gym_L2_Memory + 55296), 24576, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_onnx__conv_129, size 128 from DefaultFlash at 246656 to (size 128) L2 at 246656..246783 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Gym_L3_Flash + 246656), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Gym_L2_Memory + 246656), 128, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Conv_6_weights, size 24576 from DefaultFlash at 79872 to (size 24576) L2 at 79872..104447 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Gym_L3_Flash + 79872), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Gym_L2_Memory + 79872), 24576, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_onnx__conv_132, size 128 from DefaultFlash at 246784 to (size 128) L2 at 246784..246911 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Gym_L3_Flash + 246784), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Gym_L2_Memory + 246784), 128, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Conv_9_weights, size 24576 from DefaultFlash at 104448 to (size 24576) L2 at 104448..129023 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Gym_L3_Flash + 104448), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Gym_L2_Memory + 104448), 24576, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_onnx__conv_135, size 128 from DefaultFlash at 246912 to (size 128) L2 at 246912..247039 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Gym_L3_Flash + 246912), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Gym_L2_Memory + 246912), 128, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Conv_11_weights, size 24576 from DefaultFlash at 129024 to (size 24576) L2 at 129024..153599 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Gym_L3_Flash + 129024), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Gym_L2_Memory + 129024), 24576, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_onnx__conv_138, size 128 from DefaultFlash at 247040 to (size 128) L2 at 247040..247167 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Gym_L3_Flash + 247040), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Gym_L2_Memory + 247040), 128, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Conv_13_weights, size 24576 from DefaultFlash at 153600 to (size 24576) L2 at 153600..178175 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Gym_L3_Flash + 153600), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Gym_L2_Memory + 153600), 24576, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_onnx__conv_141, size 128 from DefaultFlash at 247168 to (size 128) L2 at 247168..247295 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Gym_L3_Flash + 247168), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Gym_L2_Memory + 247168), 128, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Conv_16_weights, size 24576 from DefaultFlash at 178176 to (size 24576) L2 at 178176..202751 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Gym_L3_Flash + 178176), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Gym_L2_Memory + 178176), 24576, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_onnx__conv_144, size 128 from DefaultFlash at 247296 to (size 128) L2 at 247296..247423 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Gym_L3_Flash + 247296), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Gym_L2_Memory + 247296), 128, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Conv_18_weights, size 24576 from DefaultFlash at 202752 to (size 24576) L2 at 202752..227327 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Gym_L3_Flash + 202752), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Gym_L2_Memory + 202752), 24576, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_onnx__conv_147, size 128 from DefaultFlash at 247424 to (size 128) L2 at 247424..247551 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Gym_L3_Flash + 247424), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Gym_L2_Memory + 247424), 128, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Conv_20_weights, size 12288 from DefaultFlash at 227328 to (size 12288) L2 at 227328..239615 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Gym_L3_Flash + 227328), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Gym_L2_Memory + 227328), 12288, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_onnx__conv_150, size 64 from DefaultFlash at 247552 to (size 64) L2 at 247552..247615 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Gym_L3_Flash + 247552), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Gym_L2_Memory + 247552), 64, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Conv_21_weights, size 4096 from DefaultFlash at 239616 to (size 4096) L2 at 239616..243711 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Gym_L3_Flash + 239616), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Gym_L2_Memory + 239616), 4096, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_backbone_identity3_channel_adapt_bias, size 64 from DefaultFlash at 247616 to (size 64) L2 at 247616..247679 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Gym_L3_Flash + 247616), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Gym_L2_Memory + 247616), 64, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Gemm_31_weights, size 30720 from DefaultFlash at 0 to (size 30720) L2 at 0..30719 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Gym_L3_Flash + 0), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Gym_L2_Memory + 0), 30720, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Gemm_31_biases, size 24 from DefaultFlash at 247680 to (size 24) L2 at 247680..247703 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Gym_L3_Flash + 247680), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Gym_L2_Memory + 247680), 24, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	return AT_NO_ERROR;
}
void GymCNN_ConstructCluster()

{
}
int GymCNN_Destruct()

{
	AT_L2_FREE(0, Gym_L2_Memory, 247704);
	AT_L2_FREE(0, Gym_L2_Memory_Dyn, 20480);
	AT_L1_FREE(0, Gym_L1_Memory, 35328);
	AT_DEFAULTFLASH_FS_CLOSE(&DefaultFlash);
	return 0;
}
int GymCNN_Memory(AT_MEM_TYPE Which)

{
	switch (Which) {
		case AT_L1_MEM:     return 35328; /* L1 Memory */
		case AT_L2_MEM:     return 247704; /* L2 Memory, permanent */
		case AT_L2_DYN_MEM: return 20480; /* L2 Memory, dynamic */
		case AT_L3_MEM:     return 0; /* L3 Memory, permanent */
		case AT_L3_DYN_MEM: return 0; /* L3 Memory, dynamic */
		default:            return 0;
	}
}
unsigned int AT_GraphPerf[17];
unsigned int AT_GraphPerf_CNN_Total = 0;
unsigned int AT_GraphOperInfosNames[17] = {
	56320,
	494080,
	494080,
	491520,
	2560,
	494080,
	494080,
	491520,
	2560,
	81920,
	494080,
	494080,
	245760,
	1280,
	15360,
	12,
	0,
};
char *AT_GraphNodeNames[17] = {
	"S4_Conv_0_fusion",
	"S9_Conv_2_fusion",
	"S12_Conv_4_fusion",
	"S15_Conv_6",
	"S17_Add_7_fusion",
	"S21_Conv_9_fusion",
	"S24_Conv_11_fusion",
	"S27_Conv_13",
	"S29_Add_14_fusion",
	"S43_Conv_21",
	"S33_Conv_16_fusion",
	"S36_Conv_18_fusion",
	"S39_Conv_20",
	"S45_Add_22_fusion",
	"S48_Gemm_31",
	"S49_Softmax_32",
	"IO_Wait",
};
int GymCNN(
		F16 * __restrict__ Input_1,
		F16 * __restrict__ Output_1)

{
	unsigned int Start_IO;
	AT_GraphPerf_CNN_Total = gap_cl_readhwtimer();
	AT_GraphPerf[0] = gap_cl_readhwtimer();
	AT_GraphPerf[16] = 0;
	S4_Conv_0_fusion(
		((F16 * __restrict__) Input_1), /* In */
		((F16 * __restrict__) (Gym_L2_Memory+243712)), /* Filter */
		((F16 * __restrict__) (Gym_L2_Memory+246400)), /* Bias */
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+10240)) /* Out */
	);
	AT_GraphPerf[0] = gap_cl_readhwtimer() - AT_GraphPerf[0];
	AT_GraphPerf[1] = gap_cl_readhwtimer();
	S9_Conv_2_fusion(
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+10240)), /* In */
		((F16 * __restrict__) (Gym_L2_Memory+30720)), /* Filter */
		((F16 * __restrict__) (Gym_L2_Memory+246528)), /* Bias */
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+0)) /* Out */
	);
	AT_GraphPerf[1] = gap_cl_readhwtimer() - AT_GraphPerf[1];
	AT_GraphPerf[2] = gap_cl_readhwtimer();
	S12_Conv_4_fusion(
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+0)), /* In */
		((F16 * __restrict__) (Gym_L2_Memory+55296)), /* Filter */
		((F16 * __restrict__) (Gym_L2_Memory+246656)), /* Bias */
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+5120)) /* Out */
	);
	AT_GraphPerf[2] = gap_cl_readhwtimer() - AT_GraphPerf[2];
	AT_GraphPerf[3] = gap_cl_readhwtimer();
	S15_Conv_6(
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+5120)), /* In */
		((F16 * __restrict__) (Gym_L2_Memory+79872)), /* Filter */
		((F16 * __restrict__) (Gym_L2_Memory+246784)), /* Bias */
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
		((F16 * __restrict__) (Gym_L2_Memory+104448)), /* Filter */
		((F16 * __restrict__) (Gym_L2_Memory+246912)), /* Bias */
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+0)) /* Out */
	);
	AT_GraphPerf[5] = gap_cl_readhwtimer() - AT_GraphPerf[5];
	AT_GraphPerf[6] = gap_cl_readhwtimer();
	S24_Conv_11_fusion(
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+0)), /* In */
		((F16 * __restrict__) (Gym_L2_Memory+129024)), /* Filter */
		((F16 * __restrict__) (Gym_L2_Memory+247040)), /* Bias */
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+15360)) /* Out */
	);
	AT_GraphPerf[6] = gap_cl_readhwtimer() - AT_GraphPerf[6];
	AT_GraphPerf[7] = gap_cl_readhwtimer();
	S27_Conv_13(
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+15360)), /* In */
		((F16 * __restrict__) (Gym_L2_Memory+153600)), /* Filter */
		((F16 * __restrict__) (Gym_L2_Memory+247168)), /* Bias */
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
	S43_Conv_21(
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+0)), /* In2 */
		((F16 * __restrict__) (Gym_L2_Memory+239616)), /* In1 */
		((F16 * __restrict__) (Gym_L2_Memory+247616)), /* Bias */
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+15360)) /* Out */
	);
	AT_GraphPerf[9] = gap_cl_readhwtimer() - AT_GraphPerf[9];
	AT_GraphPerf[10] = gap_cl_readhwtimer();
	S33_Conv_16_fusion(
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+0)), /* In */
		((F16 * __restrict__) (Gym_L2_Memory+178176)), /* Filter */
		((F16 * __restrict__) (Gym_L2_Memory+247296)), /* Bias */
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+5120)) /* Out */
	);
	AT_GraphPerf[10] = gap_cl_readhwtimer() - AT_GraphPerf[10];
	AT_GraphPerf[11] = gap_cl_readhwtimer();
	S36_Conv_18_fusion(
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+5120)), /* In */
		((F16 * __restrict__) (Gym_L2_Memory+202752)), /* Filter */
		((F16 * __restrict__) (Gym_L2_Memory+247424)), /* Bias */
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+10240)) /* Out */
	);
	AT_GraphPerf[11] = gap_cl_readhwtimer() - AT_GraphPerf[11];
	AT_GraphPerf[12] = gap_cl_readhwtimer();
	S39_Conv_20(
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+10240)), /* In */
		((F16 * __restrict__) (Gym_L2_Memory+227328)), /* Filter */
		((F16 * __restrict__) (Gym_L2_Memory+247552)), /* Bias */
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+0)) /* Out */
	);
	AT_GraphPerf[12] = gap_cl_readhwtimer() - AT_GraphPerf[12];
	AT_GraphPerf[13] = gap_cl_readhwtimer();
	S45_Add_22_fusion(
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+0)), /* In1 */
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+15360)), /* In2 */
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+2560)) /* Out */
	);
	AT_GraphPerf[13] = gap_cl_readhwtimer() - AT_GraphPerf[13];
	AT_GraphPerf[14] = gap_cl_readhwtimer();
	S48_Gemm_31(
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+2560)), /* In */
		((F16 * __restrict__) (Gym_L2_Memory+0)), /* Filter */
		((F16 * __restrict__) (Gym_L2_Memory+247680)), /* Bias */
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+0)) /* Out */
	);
	AT_GraphPerf[14] = gap_cl_readhwtimer() - AT_GraphPerf[14];
	AT_GraphPerf[15] = gap_cl_readhwtimer();
	S49_Softmax_32(
		((F16 * __restrict__) (Gym_L2_Memory_Dyn+0)), /* In */
		((F16 * __restrict__) Output_1) /* Out */
	);
	AT_GraphPerf[15] = gap_cl_readhwtimer() - AT_GraphPerf[15];
	AT_GraphPerf_CNN_Total = gap_cl_readhwtimer() - AT_GraphPerf_CNN_Total;
	return 0;
}
