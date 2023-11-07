#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#include "QvarKernels.h"
L1_CL_MEM AT_L1_POINTER Qvar_L1_Memory;
L2_MEM AT_L2_POINTER Qvar_L2_Memory;
L2_MEM AT_L2_POINTER Qvar_L2_Memory_Dyn;
static AT_DEFAULTFLASH_FS_T DefaultFlash;
void S4_Conv_0_fusion(
		F16 * __restrict__ In,
		F16 * __restrict__ Filter,
		F16 * __restrict__ Bias,
		F16 * __restrict__ Out)

{
	/* Shared L1: 9480 bytes, L2 buffer: 0 bytes */
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
		[D1 Dim: Init: 64, Tiled: 1][Tile0 Dim: 1][D0 Dim: Init: 9, Tiled: 1]
	Ker Arg: KerBuff, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 0 (Total Size: 56 )[Tile0, 1:[28x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[28x1], 2]
		Tile0: [0, 56, 56], Tile1: [0, 56, 56], Tile2; [0, 56, 56]
	Ker Arg: In, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 56 (Total Size: 720 )[D0, [0 x 720, 720]][Tile0, 1:[40x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[40x1], 2][D0, [0 x 720, 720]]
		Tile0: [0, 720, 720], Tile1: [0, 720, 720], Tile2; [0, 720, 720]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 776 (Total Size: 128 )[D1, [0 x 128, 128]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 128, 128]]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 904 (Total Size: 3456 )[D1, [0 x 3456, 3456]][D0, [0 x 54, 54]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 3456, 3456]][D0, [0 x 54, 54]]
		Tile0: [0, 3456, 3456], Tile1: [0, 3456, 3456], Tile2; [0, 3456, 3456]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 4360 (Total Size: 5120 )[D1, [0 x 5120, 5120]][Tile0, 1:[40x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 5120, 5120]][Tile0, 1:[40x1], 2]
		Tile0: [0, 5120, 5120], Tile1: [0, 5120, 5120], Tile2; [0, 5120, 5120]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (F16 * __restrict__) (Qvar_L1_Memory+56);
	KerArg0->W = (unsigned short int) (40);
	KerArg0->H = (unsigned short int) (1);
	KerArg0->Fx = (unsigned char) (3);
	KerArg0->Sx = (unsigned char) (1);
	KerArg0->Sy = (unsigned char) (1);
	KerArg0->FirstTile = (unsigned char) ((1));
	KerArg0->Pad = (v4s) ((v4s){1,1,0,0});
	KerArg0->Filter = (F16 * __restrict__) (Qvar_L1_Memory+904);
	KerArg0->Bias = (F16 * __restrict__) (Qvar_L1_Memory+776);
	KerArg0->Out = (F16 * __restrict__) (Qvar_L1_Memory+4360);
	KerArg0->InFeat = (unsigned short int) (9);
	KerArg0->OutFeat = (unsigned short int) (64);
	KerArg0->Wo = (unsigned short int) (40);
	KerArg0->Ho = (unsigned short int) (1);
	KerArg0->ColBuff = (F16 * __restrict__) (Qvar_L1_Memory+0);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+904), 3456, 0, DmaR_Evt1);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+56), 720, 0, 0);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+776), 128, 0, 0);
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
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+4360), 5120, 1, DmaW_Evt1);
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
	KerArg0->In = (F16 * __restrict__) (Qvar_L1_Memory+384);
	KerArg0->W = (unsigned short int) (40);
	KerArg0->H = (unsigned short int) (1);
	KerArg0->Fx = (unsigned char) (3);
	KerArg0->Sx = (unsigned char) (1);
	KerArg0->Sy = (unsigned char) (1);
	KerArg0->FirstTile = (unsigned char) ((1));
	KerArg0->Pad = (v4s) ((v4s){1,1,0,0});
	KerArg0->Filter = (F16 * __restrict__) (Qvar_L1_Memory+5632);
	KerArg0->Bias = (F16 * __restrict__) (Qvar_L1_Memory+5504);
	KerArg0->Out = (F16 * __restrict__) (Qvar_L1_Memory+30208);
	KerArg0->InFeat = (unsigned short int) (64);
	KerArg0->OutFeat = (unsigned short int) (64);
	KerArg0->Wo = (unsigned short int) (40);
	KerArg0->Ho = (unsigned short int) (1);
	KerArg0->ColBuff = (F16 * __restrict__) (Qvar_L1_Memory+0);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+5632), 24576, 0, DmaR_Evt1);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+384), 5120, 0, 0);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+5504), 128, 0, 0);
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
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+30208), 5120, 1, DmaW_Evt1);
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
	KerArg0->In = (F16 * __restrict__) (Qvar_L1_Memory+384);
	KerArg0->W = (unsigned short int) (40);
	KerArg0->H = (unsigned short int) (1);
	KerArg0->Fx = (unsigned char) (3);
	KerArg0->Sx = (unsigned char) (1);
	KerArg0->Sy = (unsigned char) (1);
	KerArg0->FirstTile = (unsigned char) ((1));
	KerArg0->Pad = (v4s) ((v4s){1,1,0,0});
	KerArg0->Filter = (F16 * __restrict__) (Qvar_L1_Memory+5632);
	KerArg0->Bias = (F16 * __restrict__) (Qvar_L1_Memory+5504);
	KerArg0->Out = (F16 * __restrict__) (Qvar_L1_Memory+30208);
	KerArg0->InFeat = (unsigned short int) (64);
	KerArg0->OutFeat = (unsigned short int) (64);
	KerArg0->Wo = (unsigned short int) (40);
	KerArg0->Ho = (unsigned short int) (1);
	KerArg0->ColBuff = (F16 * __restrict__) (Qvar_L1_Memory+0);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+5632), 24576, 0, DmaR_Evt1);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+384), 5120, 0, 0);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+5504), 128, 0, 0);
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
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+30208), 5120, 1, DmaW_Evt1);
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
	KerArg0->In = (F16 * __restrict__) (Qvar_L1_Memory+384);
	KerArg0->W = (unsigned short int) (40);
	KerArg0->H = (unsigned short int) (1);
	KerArg0->Fx = (unsigned char) (3);
	KerArg0->Sx = (unsigned char) (1);
	KerArg0->Sy = (unsigned char) (1);
	KerArg0->FirstTile = (unsigned char) ((1));
	KerArg0->Pad = (v4s) ((v4s){1,1,0,0});
	KerArg0->Filter = (F16 * __restrict__) (Qvar_L1_Memory+5632);
	KerArg0->Bias = (F16 * __restrict__) (Qvar_L1_Memory+5504);
	KerArg0->Out = (F16 * __restrict__) (Qvar_L1_Memory+30208);
	KerArg0->InFeat = (unsigned short int) (64);
	KerArg0->OutFeat = (unsigned short int) (64);
	KerArg0->Wo = (unsigned short int) (40);
	KerArg0->Ho = (unsigned short int) (1);
	KerArg0->ColBuff = (F16 * __restrict__) (Qvar_L1_Memory+0);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+5632), 24576, 0, DmaR_Evt1);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+384), 5120, 0, 0);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+5504), 128, 0, 0);
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
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+30208), 5120, 1, DmaW_Evt1);
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
	KerArg0->In1 = (F16 *__restrict__) (Qvar_L1_Memory+0);
	KerArg0->In2 = (F16 *__restrict__) (Qvar_L1_Memory+5120);
	KerArg0->Out = (F16 *__restrict__) (Qvar_L1_Memory+10240);
	KerArg0->W = (unsigned short int) (64);
	KerArg0->H = (unsigned short int) (40);
	KerArg0->N = (unsigned short int) (1);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In1+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+0), 5120, 0, DmaR_Evt1);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) In2+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+5120), 5120, 0, 0);
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
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+10240), 5120, 1, DmaW_Evt1);
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
	KerArg0->In = (F16 * __restrict__) (Qvar_L1_Memory+384);
	KerArg0->W = (unsigned short int) (40);
	KerArg0->H = (unsigned short int) (1);
	KerArg0->Fx = (unsigned char) (3);
	KerArg0->Sx = (unsigned char) (1);
	KerArg0->Sy = (unsigned char) (1);
	KerArg0->FirstTile = (unsigned char) ((1));
	KerArg0->Pad = (v4s) ((v4s){1,1,0,0});
	KerArg0->Filter = (F16 * __restrict__) (Qvar_L1_Memory+5632);
	KerArg0->Bias = (F16 * __restrict__) (Qvar_L1_Memory+5504);
	KerArg0->Out = (F16 * __restrict__) (Qvar_L1_Memory+30208);
	KerArg0->InFeat = (unsigned short int) (64);
	KerArg0->OutFeat = (unsigned short int) (64);
	KerArg0->Wo = (unsigned short int) (40);
	KerArg0->Ho = (unsigned short int) (1);
	KerArg0->ColBuff = (F16 * __restrict__) (Qvar_L1_Memory+0);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+5632), 24576, 0, DmaR_Evt1);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+384), 5120, 0, 0);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+5504), 128, 0, 0);
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
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+30208), 5120, 1, DmaW_Evt1);
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
	KerArg0->In = (F16 * __restrict__) (Qvar_L1_Memory+384);
	KerArg0->W = (unsigned short int) (40);
	KerArg0->H = (unsigned short int) (1);
	KerArg0->Fx = (unsigned char) (3);
	KerArg0->Sx = (unsigned char) (1);
	KerArg0->Sy = (unsigned char) (1);
	KerArg0->FirstTile = (unsigned char) ((1));
	KerArg0->Pad = (v4s) ((v4s){1,1,0,0});
	KerArg0->Filter = (F16 * __restrict__) (Qvar_L1_Memory+5632);
	KerArg0->Bias = (F16 * __restrict__) (Qvar_L1_Memory+5504);
	KerArg0->Out = (F16 * __restrict__) (Qvar_L1_Memory+30208);
	KerArg0->InFeat = (unsigned short int) (64);
	KerArg0->OutFeat = (unsigned short int) (64);
	KerArg0->Wo = (unsigned short int) (40);
	KerArg0->Ho = (unsigned short int) (1);
	KerArg0->ColBuff = (F16 * __restrict__) (Qvar_L1_Memory+0);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+5632), 24576, 0, DmaR_Evt1);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+384), 5120, 0, 0);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+5504), 128, 0, 0);
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
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+30208), 5120, 1, DmaW_Evt1);
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
	KerArg0->In = (F16 * __restrict__) (Qvar_L1_Memory+384);
	KerArg0->W = (unsigned short int) (40);
	KerArg0->H = (unsigned short int) (1);
	KerArg0->Fx = (unsigned char) (3);
	KerArg0->Sx = (unsigned char) (1);
	KerArg0->Sy = (unsigned char) (1);
	KerArg0->FirstTile = (unsigned char) ((1));
	KerArg0->Pad = (v4s) ((v4s){1,1,0,0});
	KerArg0->Filter = (F16 * __restrict__) (Qvar_L1_Memory+5632);
	KerArg0->Bias = (F16 * __restrict__) (Qvar_L1_Memory+5504);
	KerArg0->Out = (F16 * __restrict__) (Qvar_L1_Memory+30208);
	KerArg0->InFeat = (unsigned short int) (64);
	KerArg0->OutFeat = (unsigned short int) (64);
	KerArg0->Wo = (unsigned short int) (40);
	KerArg0->Ho = (unsigned short int) (1);
	KerArg0->ColBuff = (F16 * __restrict__) (Qvar_L1_Memory+0);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+5632), 24576, 0, DmaR_Evt1);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+384), 5120, 0, 0);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+5504), 128, 0, 0);
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
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+30208), 5120, 1, DmaW_Evt1);
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
	KerArg0->In1 = (F16 *__restrict__) (Qvar_L1_Memory+0);
	KerArg0->In2 = (F16 *__restrict__) (Qvar_L1_Memory+5120);
	KerArg0->Out = (F16 *__restrict__) (Qvar_L1_Memory+10240);
	KerArg0->W = (unsigned short int) (64);
	KerArg0->H = (unsigned short int) (40);
	KerArg0->N = (unsigned short int) (1);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In1+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+0), 5120, 0, DmaR_Evt1);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) In2+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+5120), 5120, 0, 0);
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
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+10240), 5120, 1, DmaW_Evt1);
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
	KerArg0->In = (F16 * __restrict__) (Qvar_L1_Memory+384);
	KerArg0->W = (unsigned short int) (40);
	KerArg0->H = (unsigned short int) (1);
	KerArg0->Fx = (unsigned char) (3);
	KerArg0->Sx = (unsigned char) (1);
	KerArg0->Sy = (unsigned char) (1);
	KerArg0->FirstTile = (unsigned char) ((1));
	KerArg0->Pad = (v4s) ((v4s){1,1,0,0});
	KerArg0->Filter = (F16 * __restrict__) (Qvar_L1_Memory+5632);
	KerArg0->Bias = (F16 * __restrict__) (Qvar_L1_Memory+5504);
	KerArg0->Out = (F16 * __restrict__) (Qvar_L1_Memory+30208);
	KerArg0->InFeat = (unsigned short int) (64);
	KerArg0->OutFeat = (unsigned short int) (64);
	KerArg0->Wo = (unsigned short int) (40);
	KerArg0->Ho = (unsigned short int) (1);
	KerArg0->ColBuff = (F16 * __restrict__) (Qvar_L1_Memory+0);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+5632), 24576, 0, DmaR_Evt1);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+384), 5120, 0, 0);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+5504), 128, 0, 0);
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
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+30208), 5120, 1, DmaW_Evt1);
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
	KerArg0->In = (F16 * __restrict__) (Qvar_L1_Memory+384);
	KerArg0->W = (unsigned short int) (40);
	KerArg0->H = (unsigned short int) (1);
	KerArg0->Fx = (unsigned char) (3);
	KerArg0->Sx = (unsigned char) (1);
	KerArg0->Sy = (unsigned char) (1);
	KerArg0->FirstTile = (unsigned char) ((1));
	KerArg0->Pad = (v4s) ((v4s){1,1,0,0});
	KerArg0->Filter = (F16 * __restrict__) (Qvar_L1_Memory+5632);
	KerArg0->Bias = (F16 * __restrict__) (Qvar_L1_Memory+5504);
	KerArg0->Out = (F16 * __restrict__) (Qvar_L1_Memory+30208);
	KerArg0->InFeat = (unsigned short int) (64);
	KerArg0->OutFeat = (unsigned short int) (64);
	KerArg0->Wo = (unsigned short int) (40);
	KerArg0->Ho = (unsigned short int) (1);
	KerArg0->ColBuff = (F16 * __restrict__) (Qvar_L1_Memory+0);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+5632), 24576, 0, DmaR_Evt1);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+384), 5120, 0, 0);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+5504), 128, 0, 0);
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
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+30208), 5120, 1, DmaW_Evt1);
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
	KerArg0->In = (F16 * __restrict__) (Qvar_L1_Memory+384);
	KerArg0->W = (unsigned short int) (40);
	KerArg0->H = (unsigned short int) (1);
	KerArg0->Fx = (unsigned char) (3);
	KerArg0->Sx = (unsigned char) (1);
	KerArg0->Sy = (unsigned char) (1);
	KerArg0->FirstTile = (unsigned char) ((1));
	KerArg0->Pad = (v4s) ((v4s){1,1,0,0});
	KerArg0->Filter = (F16 * __restrict__) (Qvar_L1_Memory+5568);
	KerArg0->Bias = (F16 * __restrict__) (Qvar_L1_Memory+5504);
	KerArg0->Out = (F16 * __restrict__) (Qvar_L1_Memory+17856);
	KerArg0->InFeat = (unsigned short int) (64);
	KerArg0->OutFeat = (unsigned short int) (32);
	KerArg0->Wo = (unsigned short int) (40);
	KerArg0->Ho = (unsigned short int) (1);
	KerArg0->ColBuff = (F16 * __restrict__) (Qvar_L1_Memory+0);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+5568), 12288, 0, DmaR_Evt1);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+384), 5120, 0, 0);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+5504), 64, 0, 0);
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
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+17856), 2560, 1, DmaW_Evt1);
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
	KerArg0->In = (void *__restrict__) (Qvar_L1_Memory+4096);
	KerArg0->Out = (void *__restrict__) (Qvar_L1_Memory+9216);
	KerArg0->Feat = (unsigned short int) (1);
	KerArg0->W = (unsigned short int) (40);
	KerArg0->H = (unsigned short int) (64);
	KerArg1->In1 = (F16 * __restrict__) (Qvar_L1_Memory+0);
	KerArg1->W_In1 = (unsigned short int) (64);
	KerArg1->H_In1 = (unsigned short int) (32);
	KerArg1->In2 = (F16 * __restrict__) (Qvar_L1_Memory+9216);
	KerArg1->W_In2 = (unsigned short int) (40);
	KerArg1->Bias = (F16 * __restrict__) (Qvar_L1_Memory+14336);
	KerArg1->Out = (F16 * __restrict__) (Qvar_L1_Memory+14400);
	KerArg1->UB = (F16) (6.000000e+00);
	KerArg1->LB = (F16) (0.000000e+00);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In2+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+4096), 5120, 0, DmaR_Evt1);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) In1+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+0), 4096, 0, 0);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+14336), 64, 0, 0);
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
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+14400), 2560, 1, DmaW_Evt1);
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
	KerArg0->In1 = (F16 *__restrict__) (Qvar_L1_Memory+0);
	KerArg0->In2 = (F16 *__restrict__) (Qvar_L1_Memory+2560);
	KerArg0->Out = (F16 *__restrict__) (Qvar_L1_Memory+5120);
	KerArg0->W = (unsigned short int) (32);
	KerArg0->H = (unsigned short int) (40);
	KerArg0->N = (unsigned short int) (1);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In1+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+0), 2560, 0, DmaR_Evt1);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) In2+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+2560), 2560, 0, 0);
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
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+5120), 2560, 1, DmaW_Evt1);
	AT_L2_WAIT(0, DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S48_Gemm_31(
		F16 * __restrict__ In,
		F16 * __restrict__ Filter,
		F16 * __restrict__ Bias,
		F16 * __restrict__ Out)

{
	/* Shared L1: 28200 bytes, L2 buffer: 0 bytes */
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
		[D0 Dim: Init: 10, Tiled: 1][Tile0 Dim: 1]
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
			@ 2560 (Total Size: 25600 )[D0, [0 x 25600, 25600]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 25600, 25600]]
		Tile0: [0, 25600, 25600], Tile1: [0, 25600, 25600], Tile2; [0, 25600, 25600]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 28160 (Total Size: 20 )[D0, [0 x 20, 20]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 20, 20]]
		Tile0: [0, 20, 20], Tile1: [0, 20, 20], Tile2; [0, 20, 20]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 28180 (Total Size: 20 )[D0, [0 x 20, 20]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 20, 20]]
		Tile0: [0, 20, 20], Tile1: [0, 20, 20], Tile2; [0, 20, 20]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (F16 * __restrict__) (Qvar_L1_Memory+0);
	KerArg0->Filter = (F16 * __restrict__) (Qvar_L1_Memory+2560);
	KerArg0->Bias = (F16 * __restrict__) (Qvar_L1_Memory+28160);
	KerArg0->Out = (F16 * __restrict__) (Qvar_L1_Memory+28180);
	KerArg0->InDim = (unsigned short int) (1280);
	KerArg0->TotalInDim = (unsigned short int) (1280);
	KerArg0->OutDim = (unsigned short int) (10);
	KerArg0->UB = (F16) (6.000000e+00);
	KerArg0->LB = (F16) (0.000000e+00);
	KerArg0->TileIndex = (unsigned short int) (0);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+2560), 25600, 0, DmaR_Evt1);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+0), 2560, 0, 0);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+28160), 20, 0, 0);
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
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+28180), 20, 1, DmaW_Evt1);
	AT_L2_WAIT(0, DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S49_Softmax_32(
		F16 * __restrict__ In,
		F16 * __restrict__ Out)

{
	/* Shared L1: 40 bytes, L2 buffer: 0 bytes */
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
			@ 0 (Total Size: 20 )[Tile0, 1:[10x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[10x1], 2]
		Tile0: [0, 20, 20], Tile1: [0, 20, 20], Tile2; [0, 20, 20]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 20 (Total Size: 20 )[Tile0, 1:[10x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[10x1], 2]
		Tile0: [0, 20, 20], Tile1: [0, 20, 20], Tile2; [0, 20, 20]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (F16 *__restrict__) (Qvar_L1_Memory+0);
	KerArg0->Feat = (unsigned short int) (1);
	KerArg0->N = (unsigned short int) (10);
	KerArg0->Out = (F16 *__restrict__) (Qvar_L1_Memory+20);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+0), 20, 0, DmaR_Evt1);
	AT_L2_WAIT(0, DmaR_Evt1); /* Wait previous DMA read In */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on Tile0 */
		int T0Ind_Last = 1;
		/*====================== Call Kernel LOC_LOOP =========================*/
		AT_FORK(gap_ncore(), (void *) KerParSoftMax_fp16, (void *) KerArg0);
		__CALL(KerParSoftMax_fp16, KerArg0);
	} /* End iteration on Tile0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+20), 20, 1, DmaW_Evt1);
	AT_L2_WAIT(0, DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
#pragma GCC diagnostic pop
int QvarCNN_Construct()

{
	AT_DEFAULTFLASH_FS_CONF_T DefaultFlashConf;

	int Error;
	AT_DEFAULTFLASH_FS_CONF_INIT(&DefaultFlashConf, AT_MEM_L3_DEFAULTFLASH, 0);
	AT_DEFAULTFLASH_FS_OPEN(&DefaultFlash, &DefaultFlashConf, "Qvar_L3_Flash_Const.dat", &Error);
	if (Error) return AT_FLASH_OPEN_ERROR;

	Qvar_L2_Memory = (AT_L2_POINTER) AT_L2_ALLOC(0, 243348);
	if (Qvar_L2_Memory == 0) return AT_L2_OPEN_ERROR;
	Qvar_L2_Memory_Dyn = (AT_L2_POINTER) AT_L2_ALLOC(0, 20480);
	if (Qvar_L2_Memory_Dyn == 0) return AT_L2_OPEN_ERROR;
	Qvar_L1_Memory = (AT_L1_POINTER) AT_L1_ALLOC(0, 35328);
	if (Qvar_L1_Memory == 0) return AT_L1_OPEN_ERROR;
	AT_DEFAULTFLASH_FS_FC_EVENT _UchanHF1, *UchanHF1 = &_UchanHF1;
	/* Static Moving Conv_0_weights, size 3456 from DefaultFlash at 238592 to (size 3456) L2 at 238592..242047 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Qvar_L3_Flash + 238592), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Qvar_L2_Memory + 238592), 3456, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_onnx__conv_123, size 128 from DefaultFlash at 242048 to (size 128) L2 at 242048..242175 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Qvar_L3_Flash + 242048), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Qvar_L2_Memory + 242048), 128, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Conv_2_weights, size 24576 from DefaultFlash at 25600 to (size 24576) L2 at 25600..50175 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Qvar_L3_Flash + 25600), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Qvar_L2_Memory + 25600), 24576, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_onnx__conv_126, size 128 from DefaultFlash at 242176 to (size 128) L2 at 242176..242303 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Qvar_L3_Flash + 242176), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Qvar_L2_Memory + 242176), 128, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Conv_4_weights, size 24576 from DefaultFlash at 50176 to (size 24576) L2 at 50176..74751 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Qvar_L3_Flash + 50176), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Qvar_L2_Memory + 50176), 24576, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_onnx__conv_129, size 128 from DefaultFlash at 242304 to (size 128) L2 at 242304..242431 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Qvar_L3_Flash + 242304), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Qvar_L2_Memory + 242304), 128, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Conv_6_weights, size 24576 from DefaultFlash at 74752 to (size 24576) L2 at 74752..99327 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Qvar_L3_Flash + 74752), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Qvar_L2_Memory + 74752), 24576, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_onnx__conv_132, size 128 from DefaultFlash at 242432 to (size 128) L2 at 242432..242559 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Qvar_L3_Flash + 242432), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Qvar_L2_Memory + 242432), 128, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Conv_9_weights, size 24576 from DefaultFlash at 99328 to (size 24576) L2 at 99328..123903 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Qvar_L3_Flash + 99328), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Qvar_L2_Memory + 99328), 24576, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_onnx__conv_135, size 128 from DefaultFlash at 242560 to (size 128) L2 at 242560..242687 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Qvar_L3_Flash + 242560), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Qvar_L2_Memory + 242560), 128, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Conv_11_weights, size 24576 from DefaultFlash at 123904 to (size 24576) L2 at 123904..148479 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Qvar_L3_Flash + 123904), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Qvar_L2_Memory + 123904), 24576, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_onnx__conv_138, size 128 from DefaultFlash at 242688 to (size 128) L2 at 242688..242815 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Qvar_L3_Flash + 242688), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Qvar_L2_Memory + 242688), 128, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Conv_13_weights, size 24576 from DefaultFlash at 148480 to (size 24576) L2 at 148480..173055 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Qvar_L3_Flash + 148480), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Qvar_L2_Memory + 148480), 24576, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_onnx__conv_141, size 128 from DefaultFlash at 242816 to (size 128) L2 at 242816..242943 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Qvar_L3_Flash + 242816), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Qvar_L2_Memory + 242816), 128, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Conv_16_weights, size 24576 from DefaultFlash at 173056 to (size 24576) L2 at 173056..197631 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Qvar_L3_Flash + 173056), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Qvar_L2_Memory + 173056), 24576, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_onnx__conv_144, size 128 from DefaultFlash at 242944 to (size 128) L2 at 242944..243071 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Qvar_L3_Flash + 242944), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Qvar_L2_Memory + 242944), 128, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Conv_18_weights, size 24576 from DefaultFlash at 197632 to (size 24576) L2 at 197632..222207 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Qvar_L3_Flash + 197632), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Qvar_L2_Memory + 197632), 24576, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_onnx__conv_147, size 128 from DefaultFlash at 243072 to (size 128) L2 at 243072..243199 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Qvar_L3_Flash + 243072), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Qvar_L2_Memory + 243072), 128, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Conv_20_weights, size 12288 from DefaultFlash at 222208 to (size 12288) L2 at 222208..234495 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Qvar_L3_Flash + 222208), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Qvar_L2_Memory + 222208), 12288, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_onnx__conv_150, size 64 from DefaultFlash at 243200 to (size 64) L2 at 243200..243263 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Qvar_L3_Flash + 243200), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Qvar_L2_Memory + 243200), 64, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Conv_21_weights, size 4096 from DefaultFlash at 234496 to (size 4096) L2 at 234496..238591 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Qvar_L3_Flash + 234496), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Qvar_L2_Memory + 234496), 4096, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_backbone_identity3_channel_adapt_bias, size 64 from DefaultFlash at 243264 to (size 64) L2 at 243264..243327 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Qvar_L3_Flash + 243264), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Qvar_L2_Memory + 243264), 64, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Gemm_31_weights, size 25600 from DefaultFlash at 0 to (size 25600) L2 at 0..25599 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Qvar_L3_Flash + 0), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Qvar_L2_Memory + 0), 25600, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Gemm_31_biases, size 20 from DefaultFlash at 243328 to (size 20) L2 at 243328..243347 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Qvar_L3_Flash + 243328), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Qvar_L2_Memory + 243328), 20, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	return AT_NO_ERROR;
}
void QvarCNN_ConstructCluster()

{
}
int QvarCNN_Destruct()

{
	AT_L2_FREE(0, Qvar_L2_Memory, 243348);
	AT_L2_FREE(0, Qvar_L2_Memory_Dyn, 20480);
	AT_L1_FREE(0, Qvar_L1_Memory, 35328);
	AT_DEFAULTFLASH_FS_CLOSE(&DefaultFlash);
	return 0;
}
int QvarCNN_Memory(AT_MEM_TYPE Which)

{
	switch (Which) {
		case AT_L1_MEM:     return 35328; /* L1 Memory */
		case AT_L2_MEM:     return 243348; /* L2 Memory, permanent */
		case AT_L2_DYN_MEM: return 20480; /* L2 Memory, dynamic */
		case AT_L3_MEM:     return 0; /* L3 Memory, permanent */
		case AT_L3_DYN_MEM: return 0; /* L3 Memory, dynamic */
		default:            return 0;
	}
}
unsigned int AT_GraphPerf[17];
unsigned int AT_GraphPerf_CNN_Total = 0;
unsigned int AT_GraphOperInfosNames[17] = {
	71680,
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
	12800,
	10,
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
int QvarCNN(
		F16 * __restrict__ Input_1,
		F16 * __restrict__ Output_1)

{
	unsigned int Start_IO;
	AT_GraphPerf_CNN_Total = gap_cl_readhwtimer();
	AT_GraphPerf[0] = gap_cl_readhwtimer();
	AT_GraphPerf[16] = 0;
	S4_Conv_0_fusion(
		((F16 * __restrict__) Input_1), /* In */
		((F16 * __restrict__) (Qvar_L2_Memory+238592)), /* Filter */
		((F16 * __restrict__) (Qvar_L2_Memory+242048)), /* Bias */
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+10240)) /* Out */
	);
	AT_GraphPerf[0] = gap_cl_readhwtimer() - AT_GraphPerf[0];
	AT_GraphPerf[1] = gap_cl_readhwtimer();
	S9_Conv_2_fusion(
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+10240)), /* In */
		((F16 * __restrict__) (Qvar_L2_Memory+25600)), /* Filter */
		((F16 * __restrict__) (Qvar_L2_Memory+242176)), /* Bias */
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+0)) /* Out */
	);
	AT_GraphPerf[1] = gap_cl_readhwtimer() - AT_GraphPerf[1];
	AT_GraphPerf[2] = gap_cl_readhwtimer();
	S12_Conv_4_fusion(
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+0)), /* In */
		((F16 * __restrict__) (Qvar_L2_Memory+50176)), /* Filter */
		((F16 * __restrict__) (Qvar_L2_Memory+242304)), /* Bias */
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+5120)) /* Out */
	);
	AT_GraphPerf[2] = gap_cl_readhwtimer() - AT_GraphPerf[2];
	AT_GraphPerf[3] = gap_cl_readhwtimer();
	S15_Conv_6(
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+5120)), /* In */
		((F16 * __restrict__) (Qvar_L2_Memory+74752)), /* Filter */
		((F16 * __restrict__) (Qvar_L2_Memory+242432)), /* Bias */
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+0)) /* Out */
	);
	AT_GraphPerf[3] = gap_cl_readhwtimer() - AT_GraphPerf[3];
	AT_GraphPerf[4] = gap_cl_readhwtimer();
	S17_Add_7_fusion(
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+0)), /* In1 */
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+10240)), /* In2 */
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+5120)) /* Out */
	);
	AT_GraphPerf[4] = gap_cl_readhwtimer() - AT_GraphPerf[4];
	AT_GraphPerf[5] = gap_cl_readhwtimer();
	S21_Conv_9_fusion(
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+5120)), /* In */
		((F16 * __restrict__) (Qvar_L2_Memory+99328)), /* Filter */
		((F16 * __restrict__) (Qvar_L2_Memory+242560)), /* Bias */
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+0)) /* Out */
	);
	AT_GraphPerf[5] = gap_cl_readhwtimer() - AT_GraphPerf[5];
	AT_GraphPerf[6] = gap_cl_readhwtimer();
	S24_Conv_11_fusion(
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+0)), /* In */
		((F16 * __restrict__) (Qvar_L2_Memory+123904)), /* Filter */
		((F16 * __restrict__) (Qvar_L2_Memory+242688)), /* Bias */
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+15360)) /* Out */
	);
	AT_GraphPerf[6] = gap_cl_readhwtimer() - AT_GraphPerf[6];
	AT_GraphPerf[7] = gap_cl_readhwtimer();
	S27_Conv_13(
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+15360)), /* In */
		((F16 * __restrict__) (Qvar_L2_Memory+148480)), /* Filter */
		((F16 * __restrict__) (Qvar_L2_Memory+242816)), /* Bias */
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+10240)) /* Out */
	);
	AT_GraphPerf[7] = gap_cl_readhwtimer() - AT_GraphPerf[7];
	AT_GraphPerf[8] = gap_cl_readhwtimer();
	S29_Add_14_fusion(
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+10240)), /* In1 */
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+5120)), /* In2 */
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+0)) /* Out */
	);
	AT_GraphPerf[8] = gap_cl_readhwtimer() - AT_GraphPerf[8];
	AT_GraphPerf[9] = gap_cl_readhwtimer();
	S43_Conv_21(
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+0)), /* In2 */
		((F16 * __restrict__) (Qvar_L2_Memory+234496)), /* In1 */
		((F16 * __restrict__) (Qvar_L2_Memory+243264)), /* Bias */
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+15360)) /* Out */
	);
	AT_GraphPerf[9] = gap_cl_readhwtimer() - AT_GraphPerf[9];
	AT_GraphPerf[10] = gap_cl_readhwtimer();
	S33_Conv_16_fusion(
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+0)), /* In */
		((F16 * __restrict__) (Qvar_L2_Memory+173056)), /* Filter */
		((F16 * __restrict__) (Qvar_L2_Memory+242944)), /* Bias */
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+5120)) /* Out */
	);
	AT_GraphPerf[10] = gap_cl_readhwtimer() - AT_GraphPerf[10];
	AT_GraphPerf[11] = gap_cl_readhwtimer();
	S36_Conv_18_fusion(
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+5120)), /* In */
		((F16 * __restrict__) (Qvar_L2_Memory+197632)), /* Filter */
		((F16 * __restrict__) (Qvar_L2_Memory+243072)), /* Bias */
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+10240)) /* Out */
	);
	AT_GraphPerf[11] = gap_cl_readhwtimer() - AT_GraphPerf[11];
	AT_GraphPerf[12] = gap_cl_readhwtimer();
	S39_Conv_20(
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+10240)), /* In */
		((F16 * __restrict__) (Qvar_L2_Memory+222208)), /* Filter */
		((F16 * __restrict__) (Qvar_L2_Memory+243200)), /* Bias */
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+0)) /* Out */
	);
	AT_GraphPerf[12] = gap_cl_readhwtimer() - AT_GraphPerf[12];
	AT_GraphPerf[13] = gap_cl_readhwtimer();
	S45_Add_22_fusion(
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+0)), /* In1 */
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+15360)), /* In2 */
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+2560)) /* Out */
	);
	AT_GraphPerf[13] = gap_cl_readhwtimer() - AT_GraphPerf[13];
	AT_GraphPerf[14] = gap_cl_readhwtimer();
	S48_Gemm_31(
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+2560)), /* In */
		((F16 * __restrict__) (Qvar_L2_Memory+0)), /* Filter */
		((F16 * __restrict__) (Qvar_L2_Memory+243328)), /* Bias */
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+0)) /* Out */
	);
	AT_GraphPerf[14] = gap_cl_readhwtimer() - AT_GraphPerf[14];
	AT_GraphPerf[15] = gap_cl_readhwtimer();
	S49_Softmax_32(
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+0)), /* In */
		((F16 * __restrict__) Output_1) /* Out */
	);
	AT_GraphPerf[15] = gap_cl_readhwtimer() - AT_GraphPerf[15];
	AT_GraphPerf_CNN_Total = gap_cl_readhwtimer() - AT_GraphPerf_CNN_Total;
	return 0;
}
