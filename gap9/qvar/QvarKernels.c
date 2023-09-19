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
void S44_Gemm_30(
		F16 * __restrict__ In,
		F16 * __restrict__ Filter,
		F16 * __restrict__ Bias,
		F16 * __restrict__ Out)

{
	/* Shared L1: 56360 bytes, L2 buffer: 0 bytes */
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
			@ 0 (Total Size: 5120 )[Tile0, 1:[1x1], 5120]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x1], 5120]
		Tile0: [0, 5120, 5120], Tile1: [0, 5120, 5120], Tile2; [0, 5120, 5120]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 5120 (Total Size: 51200 )[D0, [0 x 51200, 51200]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 51200, 51200]]
		Tile0: [0, 51200, 51200], Tile1: [0, 51200, 51200], Tile2; [0, 51200, 51200]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 56320 (Total Size: 20 )[D0, [0 x 20, 20]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 20, 20]]
		Tile0: [0, 20, 20], Tile1: [0, 20, 20], Tile2; [0, 20, 20]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 56340 (Total Size: 20 )[D0, [0 x 20, 20]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 20, 20]]
		Tile0: [0, 20, 20], Tile1: [0, 20, 20], Tile2; [0, 20, 20]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (F16 * __restrict__) (Qvar_L1_Memory+0);
	KerArg0->Filter = (F16 * __restrict__) (Qvar_L1_Memory+5120);
	KerArg0->Bias = (F16 * __restrict__) (Qvar_L1_Memory+56320);
	KerArg0->Out = (F16 * __restrict__) (Qvar_L1_Memory+56340);
	KerArg0->InDim = (unsigned short int) (2560);
	KerArg0->TotalInDim = (unsigned short int) (2560);
	KerArg0->OutDim = (unsigned short int) (10);
	KerArg0->UB = (F16) (6.000000e+00);
	KerArg0->LB = (F16) (0.000000e+00);
	KerArg0->TileIndex = (unsigned short int) (0);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+5120), 51200, 0, DmaR_Evt1);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+0), 5120, 0, 0);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+56320), 20, 0, 0);
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
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) Qvar_L1_Memory+56340), 20, 1, DmaW_Evt1);
	AT_L2_WAIT(0, DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S45_Softmax_31(
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

	Qvar_L2_Memory = (AT_L2_POINTER) AT_L2_ALLOC(0, 277140);
	if (Qvar_L2_Memory == 0) return AT_L2_OPEN_ERROR;
	Qvar_L2_Memory_Dyn = (AT_L2_POINTER) AT_L2_ALLOC(0, 20480);
	if (Qvar_L2_Memory_Dyn == 0) return AT_L2_OPEN_ERROR;
	Qvar_L1_Memory = (AT_L1_POINTER) AT_L1_ALLOC(0, 56360);
	if (Qvar_L1_Memory == 0) return AT_L1_OPEN_ERROR;
	AT_DEFAULTFLASH_FS_FC_EVENT _UchanHF1, *UchanHF1 = &_UchanHF1;
	/* Static Moving Conv_0_weights, size 3456 from DefaultFlash at 272384 to (size 3456) L2 at 272384..275839 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Qvar_L3_Flash + 272384), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Qvar_L2_Memory + 272384), 3456, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_onnx__conv_120, size 128 from DefaultFlash at 275840 to (size 128) L2 at 275840..275967 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Qvar_L3_Flash + 275840), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Qvar_L2_Memory + 275840), 128, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Conv_2_weights, size 24576 from DefaultFlash at 51200 to (size 24576) L2 at 51200..75775 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Qvar_L3_Flash + 51200), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Qvar_L2_Memory + 51200), 24576, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_onnx__conv_123, size 128 from DefaultFlash at 275968 to (size 128) L2 at 275968..276095 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Qvar_L3_Flash + 275968), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Qvar_L2_Memory + 275968), 128, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Conv_4_weights, size 24576 from DefaultFlash at 75776 to (size 24576) L2 at 75776..100351 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Qvar_L3_Flash + 75776), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Qvar_L2_Memory + 75776), 24576, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_onnx__conv_126, size 128 from DefaultFlash at 276096 to (size 128) L2 at 276096..276223 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Qvar_L3_Flash + 276096), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Qvar_L2_Memory + 276096), 128, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Conv_6_weights, size 24576 from DefaultFlash at 100352 to (size 24576) L2 at 100352..124927 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Qvar_L3_Flash + 100352), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Qvar_L2_Memory + 100352), 24576, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_onnx__conv_129, size 128 from DefaultFlash at 276224 to (size 128) L2 at 276224..276351 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Qvar_L3_Flash + 276224), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Qvar_L2_Memory + 276224), 128, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Conv_9_weights, size 24576 from DefaultFlash at 124928 to (size 24576) L2 at 124928..149503 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Qvar_L3_Flash + 124928), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Qvar_L2_Memory + 124928), 24576, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_onnx__conv_132, size 128 from DefaultFlash at 276352 to (size 128) L2 at 276352..276479 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Qvar_L3_Flash + 276352), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Qvar_L2_Memory + 276352), 128, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Conv_11_weights, size 24576 from DefaultFlash at 149504 to (size 24576) L2 at 149504..174079 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Qvar_L3_Flash + 149504), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Qvar_L2_Memory + 149504), 24576, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_onnx__conv_135, size 128 from DefaultFlash at 276480 to (size 128) L2 at 276480..276607 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Qvar_L3_Flash + 276480), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Qvar_L2_Memory + 276480), 128, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Conv_13_weights, size 24576 from DefaultFlash at 174080 to (size 24576) L2 at 174080..198655 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Qvar_L3_Flash + 174080), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Qvar_L2_Memory + 174080), 24576, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_onnx__conv_138, size 128 from DefaultFlash at 276608 to (size 128) L2 at 276608..276735 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Qvar_L3_Flash + 276608), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Qvar_L2_Memory + 276608), 128, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Conv_16_weights, size 24576 from DefaultFlash at 198656 to (size 24576) L2 at 198656..223231 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Qvar_L3_Flash + 198656), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Qvar_L2_Memory + 198656), 24576, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_onnx__conv_141, size 128 from DefaultFlash at 276736 to (size 128) L2 at 276736..276863 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Qvar_L3_Flash + 276736), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Qvar_L2_Memory + 276736), 128, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Conv_18_weights, size 24576 from DefaultFlash at 223232 to (size 24576) L2 at 223232..247807 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Qvar_L3_Flash + 223232), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Qvar_L2_Memory + 223232), 24576, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_onnx__conv_144, size 128 from DefaultFlash at 276864 to (size 128) L2 at 276864..276991 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Qvar_L3_Flash + 276864), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Qvar_L2_Memory + 276864), 128, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Conv_20_weights, size 24576 from DefaultFlash at 247808 to (size 24576) L2 at 247808..272383 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Qvar_L3_Flash + 247808), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Qvar_L2_Memory + 247808), 24576, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_onnx__conv_147, size 128 from DefaultFlash at 276992 to (size 128) L2 at 276992..277119 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Qvar_L3_Flash + 276992), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Qvar_L2_Memory + 276992), 128, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Gemm_30_weights, size 51200 from DefaultFlash at 0 to (size 51200) L2 at 0..51199 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Qvar_L3_Flash + 0), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Qvar_L2_Memory + 0), 51200, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Gemm_30_biases, size 20 from DefaultFlash at 277120 to (size 20) L2 at 277120..277139 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Qvar_L3_Flash + 277120), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Qvar_L2_Memory + 277120), 20, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	return AT_NO_ERROR;
}
void QvarCNN_ConstructCluster()

{
}
int QvarCNN_Destruct()

{
	AT_L2_FREE(0, Qvar_L2_Memory, 277140);
	AT_L2_FREE(0, Qvar_L2_Memory_Dyn, 20480);
	AT_L1_FREE(0, Qvar_L1_Memory, 56360);
	AT_DEFAULTFLASH_FS_CLOSE(&DefaultFlash);
	return 0;
}
int QvarCNN_Memory(AT_MEM_TYPE Which)

{
	switch (Which) {
		case AT_L1_MEM:     return 56360; /* L1 Memory */
		case AT_L2_MEM:     return 277140; /* L2 Memory, permanent */
		case AT_L2_DYN_MEM: return 20480; /* L2 Memory, dynamic */
		case AT_L3_MEM:     return 0; /* L3 Memory, permanent */
		case AT_L3_DYN_MEM: return 0; /* L3 Memory, dynamic */
		default:            return 0;
	}
}
unsigned int AT_GraphPerf[16];
unsigned int AT_GraphPerf_CNN_Total = 0;
unsigned int AT_GraphOperInfosNames[16] = {
	71680,
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
	25600,
	10,
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
int QvarCNN(
		F16 * __restrict__ Input_1,
		F16 * __restrict__ Output_1)

{
	unsigned int Start_IO;
	AT_GraphPerf_CNN_Total = gap_cl_readhwtimer();
	AT_GraphPerf[0] = gap_cl_readhwtimer();
	AT_GraphPerf[15] = 0;
	S4_Conv_0_fusion(
		((F16 * __restrict__) Input_1), /* In */
		((F16 * __restrict__) (Qvar_L2_Memory+272384)), /* Filter */
		((F16 * __restrict__) (Qvar_L2_Memory+275840)), /* Bias */
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+10240)) /* Out */
	);
	AT_GraphPerf[0] = gap_cl_readhwtimer() - AT_GraphPerf[0];
	AT_GraphPerf[1] = gap_cl_readhwtimer();
	S9_Conv_2_fusion(
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+10240)), /* In */
		((F16 * __restrict__) (Qvar_L2_Memory+51200)), /* Filter */
		((F16 * __restrict__) (Qvar_L2_Memory+275968)), /* Bias */
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+0)) /* Out */
	);
	AT_GraphPerf[1] = gap_cl_readhwtimer() - AT_GraphPerf[1];
	AT_GraphPerf[2] = gap_cl_readhwtimer();
	S12_Conv_4_fusion(
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+0)), /* In */
		((F16 * __restrict__) (Qvar_L2_Memory+75776)), /* Filter */
		((F16 * __restrict__) (Qvar_L2_Memory+276096)), /* Bias */
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+5120)) /* Out */
	);
	AT_GraphPerf[2] = gap_cl_readhwtimer() - AT_GraphPerf[2];
	AT_GraphPerf[3] = gap_cl_readhwtimer();
	S15_Conv_6(
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+5120)), /* In */
		((F16 * __restrict__) (Qvar_L2_Memory+100352)), /* Filter */
		((F16 * __restrict__) (Qvar_L2_Memory+276224)), /* Bias */
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
		((F16 * __restrict__) (Qvar_L2_Memory+124928)), /* Filter */
		((F16 * __restrict__) (Qvar_L2_Memory+276352)), /* Bias */
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+0)) /* Out */
	);
	AT_GraphPerf[5] = gap_cl_readhwtimer() - AT_GraphPerf[5];
	AT_GraphPerf[6] = gap_cl_readhwtimer();
	S24_Conv_11_fusion(
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+0)), /* In */
		((F16 * __restrict__) (Qvar_L2_Memory+149504)), /* Filter */
		((F16 * __restrict__) (Qvar_L2_Memory+276480)), /* Bias */
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+15360)) /* Out */
	);
	AT_GraphPerf[6] = gap_cl_readhwtimer() - AT_GraphPerf[6];
	AT_GraphPerf[7] = gap_cl_readhwtimer();
	S27_Conv_13(
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+15360)), /* In */
		((F16 * __restrict__) (Qvar_L2_Memory+174080)), /* Filter */
		((F16 * __restrict__) (Qvar_L2_Memory+276608)), /* Bias */
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
	S33_Conv_16_fusion(
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+0)), /* In */
		((F16 * __restrict__) (Qvar_L2_Memory+198656)), /* Filter */
		((F16 * __restrict__) (Qvar_L2_Memory+276736)), /* Bias */
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+5120)) /* Out */
	);
	AT_GraphPerf[9] = gap_cl_readhwtimer() - AT_GraphPerf[9];
	AT_GraphPerf[10] = gap_cl_readhwtimer();
	S36_Conv_18_fusion(
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+5120)), /* In */
		((F16 * __restrict__) (Qvar_L2_Memory+223232)), /* Filter */
		((F16 * __restrict__) (Qvar_L2_Memory+276864)), /* Bias */
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+15360)) /* Out */
	);
	AT_GraphPerf[10] = gap_cl_readhwtimer() - AT_GraphPerf[10];
	AT_GraphPerf[11] = gap_cl_readhwtimer();
	S39_Conv_20(
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+15360)), /* In */
		((F16 * __restrict__) (Qvar_L2_Memory+247808)), /* Filter */
		((F16 * __restrict__) (Qvar_L2_Memory+276992)), /* Bias */
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+10240)) /* Out */
	);
	AT_GraphPerf[11] = gap_cl_readhwtimer() - AT_GraphPerf[11];
	AT_GraphPerf[12] = gap_cl_readhwtimer();
	S41_Add_21_fusion(
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+10240)), /* In1 */
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+0)), /* In2 */
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+5120)) /* Out */
	);
	AT_GraphPerf[12] = gap_cl_readhwtimer() - AT_GraphPerf[12];
	AT_GraphPerf[13] = gap_cl_readhwtimer();
	S44_Gemm_30(
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+5120)), /* In */
		((F16 * __restrict__) (Qvar_L2_Memory+0)), /* Filter */
		((F16 * __restrict__) (Qvar_L2_Memory+277120)), /* Bias */
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+0)) /* Out */
	);
	AT_GraphPerf[13] = gap_cl_readhwtimer() - AT_GraphPerf[13];
	AT_GraphPerf[14] = gap_cl_readhwtimer();
	S45_Softmax_31(
		((F16 * __restrict__) (Qvar_L2_Memory_Dyn+0)), /* In */
		((F16 * __restrict__) Output_1) /* Out */
	);
	AT_GraphPerf[14] = gap_cl_readhwtimer() - AT_GraphPerf[14];
	AT_GraphPerf_CNN_Total = gap_cl_readhwtimer() - AT_GraphPerf_CNN_Total;
	return 0;
}
