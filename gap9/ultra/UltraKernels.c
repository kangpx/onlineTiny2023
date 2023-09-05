#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#include "UltraKernels.h"
L1_CL_MEM AT_L1_POINTER Ultra_L1_Memory;
L2_MEM AT_L2_POINTER Ultra_L2_Memory;
L2_MEM AT_L2_POINTER Ultra_L2_Memory_Dyn;
static AT_DEFAULTFLASH_FS_T DefaultFlash;
void S4_Conv_0_fusion(
		F16 * __restrict__ In,
		F16 * __restrict__ Filter,
		F16 * __restrict__ Bias,
		F16 * __restrict__ Out)

{
	/* Shared L1: 21824 bytes, L2 buffer: 0 bytes */
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
		[D1 Dim: Init: 64, Tiled: 1][Tile0 Dim: 1][D0 Dim: Init: 45, Tiled: 1]
	Ker Arg: KerBuff, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 0 (Total Size: 272 )[Tile0, 1:[136x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[136x1], 2]
		Tile0: [0, 272, 272], Tile1: [0, 272, 272], Tile2; [0, 272, 272]
	Ker Arg: In, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 272 (Total Size: 1710 )[D0, [0 x 1710, 1710]][Tile0, 1:[19x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[19x1], 2][D0, [0 x 1710, 1710]]
		Tile0: [0, 1710, 1710], Tile1: [0, 1710, 1710], Tile2; [0, 1710, 1710]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 1984 (Total Size: 128 )[D1, [0 x 128, 128]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 128, 128]]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 2112 (Total Size: 17280 )[D1, [0 x 17280, 17280]][D0, [0 x 270, 270]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 17280, 17280]][D0, [0 x 270, 270]]
		Tile0: [0, 17280, 17280], Tile1: [0, 17280, 17280], Tile2; [0, 17280, 17280]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 19392 (Total Size: 2432 )[D1, [0 x 2432, 2432]][Tile0, 1:[19x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 2432, 2432]][Tile0, 1:[19x1], 2]
		Tile0: [0, 2432, 2432], Tile1: [0, 2432, 2432], Tile2; [0, 2432, 2432]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (F16 * __restrict__) (Ultra_L1_Memory+272);
	KerArg0->W = (unsigned short int) (19);
	KerArg0->H = (unsigned short int) (1);
	KerArg0->Fx = (unsigned char) (3);
	KerArg0->Sx = (unsigned char) (1);
	KerArg0->Sy = (unsigned char) (1);
	KerArg0->FirstTile = (unsigned char) ((1));
	KerArg0->Pad = (v4s) ((v4s){1,1,0,0});
	KerArg0->Filter = (F16 * __restrict__) (Ultra_L1_Memory+2112);
	KerArg0->Bias = (F16 * __restrict__) (Ultra_L1_Memory+1984);
	KerArg0->Out = (F16 * __restrict__) (Ultra_L1_Memory+19392);
	KerArg0->InFeat = (unsigned short int) (45);
	KerArg0->OutFeat = (unsigned short int) (64);
	KerArg0->Wo = (unsigned short int) (19);
	KerArg0->Ho = (unsigned short int) (1);
	KerArg0->ColBuff = (F16 * __restrict__) (Ultra_L1_Memory+0);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+2112), 17280, 0, DmaR_Evt1);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+272), 1710, 0, 0);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+1984), 128, 0, 0);
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
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+19392), 2432, 1, DmaW_Evt1);
	AT_L2_WAIT(0, DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S9_Conv_2_fusion(
		F16 * __restrict__ In,
		F16 * __restrict__ Filter,
		F16 * __restrict__ Bias,
		F16 * __restrict__ Out)

{
	/* Shared L1: 29952 bytes, L2 buffer: 0 bytes */
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
			@ 384 (Total Size: 2432 )[D0, [0 x 2432, 2432]][Tile0, 1:[19x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[19x1], 2][D0, [0 x 2432, 2432]]
		Tile0: [0, 2432, 2432], Tile1: [0, 2432, 2432], Tile2; [0, 2432, 2432]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 2816 (Total Size: 128 )[D1, [0 x 128, 128]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 128, 128]]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 2944 (Total Size: 24576 )[D1, [0 x 24576, 24576]][D0, [0 x 384, 384]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 24576, 24576]][D0, [0 x 384, 384]]
		Tile0: [0, 24576, 24576], Tile1: [0, 24576, 24576], Tile2; [0, 24576, 24576]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 27520 (Total Size: 2432 )[D1, [0 x 2432, 2432]][Tile0, 1:[19x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 2432, 2432]][Tile0, 1:[19x1], 2]
		Tile0: [0, 2432, 2432], Tile1: [0, 2432, 2432], Tile2; [0, 2432, 2432]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (F16 * __restrict__) (Ultra_L1_Memory+384);
	KerArg0->W = (unsigned short int) (19);
	KerArg0->H = (unsigned short int) (1);
	KerArg0->Fx = (unsigned char) (3);
	KerArg0->Sx = (unsigned char) (1);
	KerArg0->Sy = (unsigned char) (1);
	KerArg0->FirstTile = (unsigned char) ((1));
	KerArg0->Pad = (v4s) ((v4s){1,1,0,0});
	KerArg0->Filter = (F16 * __restrict__) (Ultra_L1_Memory+2944);
	KerArg0->Bias = (F16 * __restrict__) (Ultra_L1_Memory+2816);
	KerArg0->Out = (F16 * __restrict__) (Ultra_L1_Memory+27520);
	KerArg0->InFeat = (unsigned short int) (64);
	KerArg0->OutFeat = (unsigned short int) (64);
	KerArg0->Wo = (unsigned short int) (19);
	KerArg0->Ho = (unsigned short int) (1);
	KerArg0->ColBuff = (F16 * __restrict__) (Ultra_L1_Memory+0);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+2944), 24576, 0, DmaR_Evt1);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+384), 2432, 0, 0);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+2816), 128, 0, 0);
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
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+27520), 2432, 1, DmaW_Evt1);
	AT_L2_WAIT(0, DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S12_Conv_4_fusion(
		F16 * __restrict__ In,
		F16 * __restrict__ Filter,
		F16 * __restrict__ Bias,
		F16 * __restrict__ Out)

{
	/* Shared L1: 29952 bytes, L2 buffer: 0 bytes */
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
			@ 384 (Total Size: 2432 )[D0, [0 x 2432, 2432]][Tile0, 1:[19x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[19x1], 2][D0, [0 x 2432, 2432]]
		Tile0: [0, 2432, 2432], Tile1: [0, 2432, 2432], Tile2; [0, 2432, 2432]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 2816 (Total Size: 128 )[D1, [0 x 128, 128]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 128, 128]]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 2944 (Total Size: 24576 )[D1, [0 x 24576, 24576]][D0, [0 x 384, 384]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 24576, 24576]][D0, [0 x 384, 384]]
		Tile0: [0, 24576, 24576], Tile1: [0, 24576, 24576], Tile2; [0, 24576, 24576]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 27520 (Total Size: 2432 )[D1, [0 x 2432, 2432]][Tile0, 1:[19x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 2432, 2432]][Tile0, 1:[19x1], 2]
		Tile0: [0, 2432, 2432], Tile1: [0, 2432, 2432], Tile2; [0, 2432, 2432]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (F16 * __restrict__) (Ultra_L1_Memory+384);
	KerArg0->W = (unsigned short int) (19);
	KerArg0->H = (unsigned short int) (1);
	KerArg0->Fx = (unsigned char) (3);
	KerArg0->Sx = (unsigned char) (1);
	KerArg0->Sy = (unsigned char) (1);
	KerArg0->FirstTile = (unsigned char) ((1));
	KerArg0->Pad = (v4s) ((v4s){1,1,0,0});
	KerArg0->Filter = (F16 * __restrict__) (Ultra_L1_Memory+2944);
	KerArg0->Bias = (F16 * __restrict__) (Ultra_L1_Memory+2816);
	KerArg0->Out = (F16 * __restrict__) (Ultra_L1_Memory+27520);
	KerArg0->InFeat = (unsigned short int) (64);
	KerArg0->OutFeat = (unsigned short int) (64);
	KerArg0->Wo = (unsigned short int) (19);
	KerArg0->Ho = (unsigned short int) (1);
	KerArg0->ColBuff = (F16 * __restrict__) (Ultra_L1_Memory+0);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+2944), 24576, 0, DmaR_Evt1);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+384), 2432, 0, 0);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+2816), 128, 0, 0);
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
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+27520), 2432, 1, DmaW_Evt1);
	AT_L2_WAIT(0, DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S15_Conv_6(
		F16 * __restrict__ In,
		F16 * __restrict__ Filter,
		F16 * __restrict__ Bias,
		F16 * __restrict__ Out)

{
	/* Shared L1: 29952 bytes, L2 buffer: 0 bytes */
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
			@ 384 (Total Size: 2432 )[D0, [0 x 2432, 2432]][Tile0, 1:[19x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[19x1], 2][D0, [0 x 2432, 2432]]
		Tile0: [0, 2432, 2432], Tile1: [0, 2432, 2432], Tile2; [0, 2432, 2432]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 2816 (Total Size: 128 )[D1, [0 x 128, 128]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 128, 128]]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 2944 (Total Size: 24576 )[D1, [0 x 24576, 24576]][D0, [0 x 384, 384]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 24576, 24576]][D0, [0 x 384, 384]]
		Tile0: [0, 24576, 24576], Tile1: [0, 24576, 24576], Tile2; [0, 24576, 24576]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 27520 (Total Size: 2432 )[D1, [0 x 2432, 2432]][Tile0, 1:[19x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 2432, 2432]][Tile0, 1:[19x1], 2]
		Tile0: [0, 2432, 2432], Tile1: [0, 2432, 2432], Tile2; [0, 2432, 2432]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (F16 * __restrict__) (Ultra_L1_Memory+384);
	KerArg0->W = (unsigned short int) (19);
	KerArg0->H = (unsigned short int) (1);
	KerArg0->Fx = (unsigned char) (3);
	KerArg0->Sx = (unsigned char) (1);
	KerArg0->Sy = (unsigned char) (1);
	KerArg0->FirstTile = (unsigned char) ((1));
	KerArg0->Pad = (v4s) ((v4s){1,1,0,0});
	KerArg0->Filter = (F16 * __restrict__) (Ultra_L1_Memory+2944);
	KerArg0->Bias = (F16 * __restrict__) (Ultra_L1_Memory+2816);
	KerArg0->Out = (F16 * __restrict__) (Ultra_L1_Memory+27520);
	KerArg0->InFeat = (unsigned short int) (64);
	KerArg0->OutFeat = (unsigned short int) (64);
	KerArg0->Wo = (unsigned short int) (19);
	KerArg0->Ho = (unsigned short int) (1);
	KerArg0->ColBuff = (F16 * __restrict__) (Ultra_L1_Memory+0);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+2944), 24576, 0, DmaR_Evt1);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+384), 2432, 0, 0);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+2816), 128, 0, 0);
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
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+27520), 2432, 1, DmaW_Evt1);
	AT_L2_WAIT(0, DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S17_Add_7_fusion(
		F16 * __restrict__ In1,
		F16 * __restrict__ In2,
		F16 * __restrict__ Out)

{
	/* Shared L1: 7296 bytes, L2 buffer: 0 bytes */
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
			@ 0 (Total Size: 2432 )[D0, [0 x 2432, 2432]][Tile0, 1:[64x19], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 2432, 2432]][Tile0, 1:[64x19], 2]
		Tile0: [0, 2432, 2432], Tile1: [0, 2432, 2432], Tile2; [0, 2432, 2432]
	Ker Arg: In2, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 2432 (Total Size: 2432 )[D0, [0 x 2432, 2432]][Tile0, 1:[64x19], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 2432, 2432]][Tile0, 1:[64x19], 2]
		Tile0: [0, 2432, 2432], Tile1: [0, 2432, 2432], Tile2; [0, 2432, 2432]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 4864 (Total Size: 2432 )[D0, [0 x 2432, 2432]][Tile0, 1:[64x19], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 2432, 2432]][Tile0, 1:[64x19], 2]
		Tile0: [0, 2432, 2432], Tile1: [0, 2432, 2432], Tile2; [0, 2432, 2432]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In1 = (F16 *__restrict__) (Ultra_L1_Memory+0);
	KerArg0->In2 = (F16 *__restrict__) (Ultra_L1_Memory+2432);
	KerArg0->Out = (F16 *__restrict__) (Ultra_L1_Memory+4864);
	KerArg0->W = (unsigned short int) (64);
	KerArg0->H = (unsigned short int) (19);
	KerArg0->N = (unsigned short int) (1);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In1+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+0), 2432, 0, DmaR_Evt1);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) In2+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+2432), 2432, 0, 0);
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
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+4864), 2432, 1, DmaW_Evt1);
	AT_L2_WAIT(0, DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S21_Conv_9_fusion(
		F16 * __restrict__ In,
		F16 * __restrict__ Filter,
		F16 * __restrict__ Bias,
		F16 * __restrict__ Out)

{
	/* Shared L1: 29952 bytes, L2 buffer: 0 bytes */
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
			@ 384 (Total Size: 2432 )[D0, [0 x 2432, 2432]][Tile0, 1:[19x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[19x1], 2][D0, [0 x 2432, 2432]]
		Tile0: [0, 2432, 2432], Tile1: [0, 2432, 2432], Tile2; [0, 2432, 2432]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 2816 (Total Size: 128 )[D1, [0 x 128, 128]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 128, 128]]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 2944 (Total Size: 24576 )[D1, [0 x 24576, 24576]][D0, [0 x 384, 384]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 24576, 24576]][D0, [0 x 384, 384]]
		Tile0: [0, 24576, 24576], Tile1: [0, 24576, 24576], Tile2; [0, 24576, 24576]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 27520 (Total Size: 2432 )[D1, [0 x 2432, 2432]][Tile0, 1:[19x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 2432, 2432]][Tile0, 1:[19x1], 2]
		Tile0: [0, 2432, 2432], Tile1: [0, 2432, 2432], Tile2; [0, 2432, 2432]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (F16 * __restrict__) (Ultra_L1_Memory+384);
	KerArg0->W = (unsigned short int) (19);
	KerArg0->H = (unsigned short int) (1);
	KerArg0->Fx = (unsigned char) (3);
	KerArg0->Sx = (unsigned char) (1);
	KerArg0->Sy = (unsigned char) (1);
	KerArg0->FirstTile = (unsigned char) ((1));
	KerArg0->Pad = (v4s) ((v4s){1,1,0,0});
	KerArg0->Filter = (F16 * __restrict__) (Ultra_L1_Memory+2944);
	KerArg0->Bias = (F16 * __restrict__) (Ultra_L1_Memory+2816);
	KerArg0->Out = (F16 * __restrict__) (Ultra_L1_Memory+27520);
	KerArg0->InFeat = (unsigned short int) (64);
	KerArg0->OutFeat = (unsigned short int) (64);
	KerArg0->Wo = (unsigned short int) (19);
	KerArg0->Ho = (unsigned short int) (1);
	KerArg0->ColBuff = (F16 * __restrict__) (Ultra_L1_Memory+0);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+2944), 24576, 0, DmaR_Evt1);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+384), 2432, 0, 0);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+2816), 128, 0, 0);
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
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+27520), 2432, 1, DmaW_Evt1);
	AT_L2_WAIT(0, DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S24_Conv_11_fusion(
		F16 * __restrict__ In,
		F16 * __restrict__ Filter,
		F16 * __restrict__ Bias,
		F16 * __restrict__ Out)

{
	/* Shared L1: 29952 bytes, L2 buffer: 0 bytes */
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
			@ 384 (Total Size: 2432 )[D0, [0 x 2432, 2432]][Tile0, 1:[19x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[19x1], 2][D0, [0 x 2432, 2432]]
		Tile0: [0, 2432, 2432], Tile1: [0, 2432, 2432], Tile2; [0, 2432, 2432]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 2816 (Total Size: 128 )[D1, [0 x 128, 128]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 128, 128]]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 2944 (Total Size: 24576 )[D1, [0 x 24576, 24576]][D0, [0 x 384, 384]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 24576, 24576]][D0, [0 x 384, 384]]
		Tile0: [0, 24576, 24576], Tile1: [0, 24576, 24576], Tile2; [0, 24576, 24576]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 27520 (Total Size: 2432 )[D1, [0 x 2432, 2432]][Tile0, 1:[19x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 2432, 2432]][Tile0, 1:[19x1], 2]
		Tile0: [0, 2432, 2432], Tile1: [0, 2432, 2432], Tile2; [0, 2432, 2432]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (F16 * __restrict__) (Ultra_L1_Memory+384);
	KerArg0->W = (unsigned short int) (19);
	KerArg0->H = (unsigned short int) (1);
	KerArg0->Fx = (unsigned char) (3);
	KerArg0->Sx = (unsigned char) (1);
	KerArg0->Sy = (unsigned char) (1);
	KerArg0->FirstTile = (unsigned char) ((1));
	KerArg0->Pad = (v4s) ((v4s){1,1,0,0});
	KerArg0->Filter = (F16 * __restrict__) (Ultra_L1_Memory+2944);
	KerArg0->Bias = (F16 * __restrict__) (Ultra_L1_Memory+2816);
	KerArg0->Out = (F16 * __restrict__) (Ultra_L1_Memory+27520);
	KerArg0->InFeat = (unsigned short int) (64);
	KerArg0->OutFeat = (unsigned short int) (64);
	KerArg0->Wo = (unsigned short int) (19);
	KerArg0->Ho = (unsigned short int) (1);
	KerArg0->ColBuff = (F16 * __restrict__) (Ultra_L1_Memory+0);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+2944), 24576, 0, DmaR_Evt1);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+384), 2432, 0, 0);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+2816), 128, 0, 0);
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
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+27520), 2432, 1, DmaW_Evt1);
	AT_L2_WAIT(0, DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S27_Conv_13(
		F16 * __restrict__ In,
		F16 * __restrict__ Filter,
		F16 * __restrict__ Bias,
		F16 * __restrict__ Out)

{
	/* Shared L1: 29952 bytes, L2 buffer: 0 bytes */
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
			@ 384 (Total Size: 2432 )[D0, [0 x 2432, 2432]][Tile0, 1:[19x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[19x1], 2][D0, [0 x 2432, 2432]]
		Tile0: [0, 2432, 2432], Tile1: [0, 2432, 2432], Tile2; [0, 2432, 2432]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 2816 (Total Size: 128 )[D1, [0 x 128, 128]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 128, 128]]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 2944 (Total Size: 24576 )[D1, [0 x 24576, 24576]][D0, [0 x 384, 384]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 24576, 24576]][D0, [0 x 384, 384]]
		Tile0: [0, 24576, 24576], Tile1: [0, 24576, 24576], Tile2; [0, 24576, 24576]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 27520 (Total Size: 2432 )[D1, [0 x 2432, 2432]][Tile0, 1:[19x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 2432, 2432]][Tile0, 1:[19x1], 2]
		Tile0: [0, 2432, 2432], Tile1: [0, 2432, 2432], Tile2; [0, 2432, 2432]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (F16 * __restrict__) (Ultra_L1_Memory+384);
	KerArg0->W = (unsigned short int) (19);
	KerArg0->H = (unsigned short int) (1);
	KerArg0->Fx = (unsigned char) (3);
	KerArg0->Sx = (unsigned char) (1);
	KerArg0->Sy = (unsigned char) (1);
	KerArg0->FirstTile = (unsigned char) ((1));
	KerArg0->Pad = (v4s) ((v4s){1,1,0,0});
	KerArg0->Filter = (F16 * __restrict__) (Ultra_L1_Memory+2944);
	KerArg0->Bias = (F16 * __restrict__) (Ultra_L1_Memory+2816);
	KerArg0->Out = (F16 * __restrict__) (Ultra_L1_Memory+27520);
	KerArg0->InFeat = (unsigned short int) (64);
	KerArg0->OutFeat = (unsigned short int) (64);
	KerArg0->Wo = (unsigned short int) (19);
	KerArg0->Ho = (unsigned short int) (1);
	KerArg0->ColBuff = (F16 * __restrict__) (Ultra_L1_Memory+0);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+2944), 24576, 0, DmaR_Evt1);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+384), 2432, 0, 0);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+2816), 128, 0, 0);
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
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+27520), 2432, 1, DmaW_Evt1);
	AT_L2_WAIT(0, DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S29_Add_14_fusion(
		F16 * __restrict__ In1,
		F16 * __restrict__ In2,
		F16 * __restrict__ Out)

{
	/* Shared L1: 7296 bytes, L2 buffer: 0 bytes */
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
			@ 0 (Total Size: 2432 )[D0, [0 x 2432, 2432]][Tile0, 1:[64x19], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 2432, 2432]][Tile0, 1:[64x19], 2]
		Tile0: [0, 2432, 2432], Tile1: [0, 2432, 2432], Tile2; [0, 2432, 2432]
	Ker Arg: In2, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 2432 (Total Size: 2432 )[D0, [0 x 2432, 2432]][Tile0, 1:[64x19], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 2432, 2432]][Tile0, 1:[64x19], 2]
		Tile0: [0, 2432, 2432], Tile1: [0, 2432, 2432], Tile2; [0, 2432, 2432]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 4864 (Total Size: 2432 )[D0, [0 x 2432, 2432]][Tile0, 1:[64x19], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 2432, 2432]][Tile0, 1:[64x19], 2]
		Tile0: [0, 2432, 2432], Tile1: [0, 2432, 2432], Tile2; [0, 2432, 2432]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In1 = (F16 *__restrict__) (Ultra_L1_Memory+0);
	KerArg0->In2 = (F16 *__restrict__) (Ultra_L1_Memory+2432);
	KerArg0->Out = (F16 *__restrict__) (Ultra_L1_Memory+4864);
	KerArg0->W = (unsigned short int) (64);
	KerArg0->H = (unsigned short int) (19);
	KerArg0->N = (unsigned short int) (1);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In1+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+0), 2432, 0, DmaR_Evt1);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) In2+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+2432), 2432, 0, 0);
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
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+4864), 2432, 1, DmaW_Evt1);
	AT_L2_WAIT(0, DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S33_Conv_16_fusion(
		F16 * __restrict__ In,
		F16 * __restrict__ Filter,
		F16 * __restrict__ Bias,
		F16 * __restrict__ Out)

{
	/* Shared L1: 29952 bytes, L2 buffer: 0 bytes */
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
			@ 384 (Total Size: 2432 )[D0, [0 x 2432, 2432]][Tile0, 1:[19x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[19x1], 2][D0, [0 x 2432, 2432]]
		Tile0: [0, 2432, 2432], Tile1: [0, 2432, 2432], Tile2; [0, 2432, 2432]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 2816 (Total Size: 128 )[D1, [0 x 128, 128]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 128, 128]]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 2944 (Total Size: 24576 )[D1, [0 x 24576, 24576]][D0, [0 x 384, 384]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 24576, 24576]][D0, [0 x 384, 384]]
		Tile0: [0, 24576, 24576], Tile1: [0, 24576, 24576], Tile2; [0, 24576, 24576]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 27520 (Total Size: 2432 )[D1, [0 x 2432, 2432]][Tile0, 1:[19x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 2432, 2432]][Tile0, 1:[19x1], 2]
		Tile0: [0, 2432, 2432], Tile1: [0, 2432, 2432], Tile2; [0, 2432, 2432]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (F16 * __restrict__) (Ultra_L1_Memory+384);
	KerArg0->W = (unsigned short int) (19);
	KerArg0->H = (unsigned short int) (1);
	KerArg0->Fx = (unsigned char) (3);
	KerArg0->Sx = (unsigned char) (1);
	KerArg0->Sy = (unsigned char) (1);
	KerArg0->FirstTile = (unsigned char) ((1));
	KerArg0->Pad = (v4s) ((v4s){1,1,0,0});
	KerArg0->Filter = (F16 * __restrict__) (Ultra_L1_Memory+2944);
	KerArg0->Bias = (F16 * __restrict__) (Ultra_L1_Memory+2816);
	KerArg0->Out = (F16 * __restrict__) (Ultra_L1_Memory+27520);
	KerArg0->InFeat = (unsigned short int) (64);
	KerArg0->OutFeat = (unsigned short int) (64);
	KerArg0->Wo = (unsigned short int) (19);
	KerArg0->Ho = (unsigned short int) (1);
	KerArg0->ColBuff = (F16 * __restrict__) (Ultra_L1_Memory+0);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+2944), 24576, 0, DmaR_Evt1);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+384), 2432, 0, 0);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+2816), 128, 0, 0);
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
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+27520), 2432, 1, DmaW_Evt1);
	AT_L2_WAIT(0, DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S36_Conv_18_fusion(
		F16 * __restrict__ In,
		F16 * __restrict__ Filter,
		F16 * __restrict__ Bias,
		F16 * __restrict__ Out)

{
	/* Shared L1: 29952 bytes, L2 buffer: 0 bytes */
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
			@ 384 (Total Size: 2432 )[D0, [0 x 2432, 2432]][Tile0, 1:[19x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[19x1], 2][D0, [0 x 2432, 2432]]
		Tile0: [0, 2432, 2432], Tile1: [0, 2432, 2432], Tile2; [0, 2432, 2432]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 2816 (Total Size: 128 )[D1, [0 x 128, 128]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 128, 128]]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 2944 (Total Size: 24576 )[D1, [0 x 24576, 24576]][D0, [0 x 384, 384]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 24576, 24576]][D0, [0 x 384, 384]]
		Tile0: [0, 24576, 24576], Tile1: [0, 24576, 24576], Tile2; [0, 24576, 24576]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 27520 (Total Size: 2432 )[D1, [0 x 2432, 2432]][Tile0, 1:[19x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 2432, 2432]][Tile0, 1:[19x1], 2]
		Tile0: [0, 2432, 2432], Tile1: [0, 2432, 2432], Tile2; [0, 2432, 2432]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (F16 * __restrict__) (Ultra_L1_Memory+384);
	KerArg0->W = (unsigned short int) (19);
	KerArg0->H = (unsigned short int) (1);
	KerArg0->Fx = (unsigned char) (3);
	KerArg0->Sx = (unsigned char) (1);
	KerArg0->Sy = (unsigned char) (1);
	KerArg0->FirstTile = (unsigned char) ((1));
	KerArg0->Pad = (v4s) ((v4s){1,1,0,0});
	KerArg0->Filter = (F16 * __restrict__) (Ultra_L1_Memory+2944);
	KerArg0->Bias = (F16 * __restrict__) (Ultra_L1_Memory+2816);
	KerArg0->Out = (F16 * __restrict__) (Ultra_L1_Memory+27520);
	KerArg0->InFeat = (unsigned short int) (64);
	KerArg0->OutFeat = (unsigned short int) (64);
	KerArg0->Wo = (unsigned short int) (19);
	KerArg0->Ho = (unsigned short int) (1);
	KerArg0->ColBuff = (F16 * __restrict__) (Ultra_L1_Memory+0);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+2944), 24576, 0, DmaR_Evt1);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+384), 2432, 0, 0);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+2816), 128, 0, 0);
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
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+27520), 2432, 1, DmaW_Evt1);
	AT_L2_WAIT(0, DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S39_Conv_20(
		F16 * __restrict__ In,
		F16 * __restrict__ Filter,
		F16 * __restrict__ Bias,
		F16 * __restrict__ Out)

{
	/* Shared L1: 29952 bytes, L2 buffer: 0 bytes */
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
			@ 384 (Total Size: 2432 )[D0, [0 x 2432, 2432]][Tile0, 1:[19x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[19x1], 2][D0, [0 x 2432, 2432]]
		Tile0: [0, 2432, 2432], Tile1: [0, 2432, 2432], Tile2; [0, 2432, 2432]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 2816 (Total Size: 128 )[D1, [0 x 128, 128]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 128, 128]]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 2944 (Total Size: 24576 )[D1, [0 x 24576, 24576]][D0, [0 x 384, 384]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 24576, 24576]][D0, [0 x 384, 384]]
		Tile0: [0, 24576, 24576], Tile1: [0, 24576, 24576], Tile2; [0, 24576, 24576]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 27520 (Total Size: 2432 )[D1, [0 x 2432, 2432]][Tile0, 1:[19x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 2432, 2432]][Tile0, 1:[19x1], 2]
		Tile0: [0, 2432, 2432], Tile1: [0, 2432, 2432], Tile2; [0, 2432, 2432]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (F16 * __restrict__) (Ultra_L1_Memory+384);
	KerArg0->W = (unsigned short int) (19);
	KerArg0->H = (unsigned short int) (1);
	KerArg0->Fx = (unsigned char) (3);
	KerArg0->Sx = (unsigned char) (1);
	KerArg0->Sy = (unsigned char) (1);
	KerArg0->FirstTile = (unsigned char) ((1));
	KerArg0->Pad = (v4s) ((v4s){1,1,0,0});
	KerArg0->Filter = (F16 * __restrict__) (Ultra_L1_Memory+2944);
	KerArg0->Bias = (F16 * __restrict__) (Ultra_L1_Memory+2816);
	KerArg0->Out = (F16 * __restrict__) (Ultra_L1_Memory+27520);
	KerArg0->InFeat = (unsigned short int) (64);
	KerArg0->OutFeat = (unsigned short int) (64);
	KerArg0->Wo = (unsigned short int) (19);
	KerArg0->Ho = (unsigned short int) (1);
	KerArg0->ColBuff = (F16 * __restrict__) (Ultra_L1_Memory+0);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+2944), 24576, 0, DmaR_Evt1);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+384), 2432, 0, 0);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+2816), 128, 0, 0);
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
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+27520), 2432, 1, DmaW_Evt1);
	AT_L2_WAIT(0, DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S41_Add_21_fusion(
		F16 * __restrict__ In1,
		F16 * __restrict__ In2,
		F16 * __restrict__ Out)

{
	/* Shared L1: 7296 bytes, L2 buffer: 0 bytes */
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
			@ 0 (Total Size: 2432 )[D0, [0 x 2432, 2432]][Tile0, 1:[64x19], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 2432, 2432]][Tile0, 1:[64x19], 2]
		Tile0: [0, 2432, 2432], Tile1: [0, 2432, 2432], Tile2; [0, 2432, 2432]
	Ker Arg: In2, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 2432 (Total Size: 2432 )[D0, [0 x 2432, 2432]][Tile0, 1:[64x19], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 2432, 2432]][Tile0, 1:[64x19], 2]
		Tile0: [0, 2432, 2432], Tile1: [0, 2432, 2432], Tile2; [0, 2432, 2432]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 4864 (Total Size: 2432 )[D0, [0 x 2432, 2432]][Tile0, 1:[64x19], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 2432, 2432]][Tile0, 1:[64x19], 2]
		Tile0: [0, 2432, 2432], Tile1: [0, 2432, 2432], Tile2; [0, 2432, 2432]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In1 = (F16 *__restrict__) (Ultra_L1_Memory+0);
	KerArg0->In2 = (F16 *__restrict__) (Ultra_L1_Memory+2432);
	KerArg0->Out = (F16 *__restrict__) (Ultra_L1_Memory+4864);
	KerArg0->W = (unsigned short int) (64);
	KerArg0->H = (unsigned short int) (19);
	KerArg0->N = (unsigned short int) (1);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In1+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+0), 2432, 0, DmaR_Evt1);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) In2+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+2432), 2432, 0, 0);
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
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+4864), 2432, 1, DmaW_Evt1);
	AT_L2_WAIT(0, DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S44_Gemm_30(
		F16 * __restrict__ In,
		F16 * __restrict__ Filter,
		F16 * __restrict__ Bias,
		F16 * __restrict__ Out)

{
	/* Shared L1: 21920 bytes, L2 buffer: 0 bytes */
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
		[D0 Dim: Init: 8, Tiled: 1][Tile0 Dim: 1]
	Ker Arg: In, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 0 (Total Size: 2432 )[Tile0, 1:[1x1], 2432]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x1], 2432]
		Tile0: [0, 2432, 2432], Tile1: [0, 2432, 2432], Tile2; [0, 2432, 2432]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 2432 (Total Size: 19456 )[D0, [0 x 19456, 19456]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 19456, 19456]]
		Tile0: [0, 19456, 19456], Tile1: [0, 19456, 19456], Tile2; [0, 19456, 19456]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 21888 (Total Size: 16 )[D0, [0 x 16, 16]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 16, 16]]
		Tile0: [0, 16, 16], Tile1: [0, 16, 16], Tile2; [0, 16, 16]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 21904 (Total Size: 16 )[D0, [0 x 16, 16]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 16, 16]]
		Tile0: [0, 16, 16], Tile1: [0, 16, 16], Tile2; [0, 16, 16]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (F16 * __restrict__) (Ultra_L1_Memory+0);
	KerArg0->Filter = (F16 * __restrict__) (Ultra_L1_Memory+2432);
	KerArg0->Bias = (F16 * __restrict__) (Ultra_L1_Memory+21888);
	KerArg0->Out = (F16 * __restrict__) (Ultra_L1_Memory+21904);
	KerArg0->InDim = (unsigned short int) (1216);
	KerArg0->TotalInDim = (unsigned short int) (1216);
	KerArg0->OutDim = (unsigned short int) (8);
	KerArg0->UB = (F16) (6.000000e+00);
	KerArg0->LB = (F16) (0.000000e+00);
	KerArg0->TileIndex = (unsigned short int) (0);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+2432), 19456, 0, DmaR_Evt1);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+0), 2432, 0, 0);
	AT_L2_COPY_MERGED(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+21888), 16, 0, 0);
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
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+21904), 16, 1, DmaW_Evt1);
	AT_L2_WAIT(0, DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S45_Softmax_31(
		F16 * __restrict__ In,
		F16 * __restrict__ Out)

{
	/* Shared L1: 32 bytes, L2 buffer: 0 bytes */
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
			@ 0 (Total Size: 16 )[Tile0, 1:[8x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[8x1], 2]
		Tile0: [0, 16, 16], Tile1: [0, 16, 16], Tile2; [0, 16, 16]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			@ 16 (Total Size: 16 )[Tile0, 1:[8x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[8x1], 2]
		Tile0: [0, 16, 16], Tile1: [0, 16, 16], Tile2; [0, 16, 16]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (F16 *__restrict__) (Ultra_L1_Memory+0);
	KerArg0->Feat = (unsigned short int) (1);
	KerArg0->N = (unsigned short int) (8);
	KerArg0->Out = (F16 *__restrict__) (Ultra_L1_Memory+16);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+0), 16, 0, DmaR_Evt1);
	AT_L2_WAIT(0, DmaR_Evt1); /* Wait previous DMA read In */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on Tile0 */
		int T0Ind_Last = 1;
		/*====================== Call Kernel LOC_LOOP =========================*/
		AT_FORK(gap_ncore(), (void *) KerParSoftMax_fp16, (void *) KerArg0);
		__CALL(KerParSoftMax_fp16, KerArg0);
	} /* End iteration on Tile0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) Ultra_L1_Memory+16), 16, 1, DmaW_Evt1);
	AT_L2_WAIT(0, DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
#pragma GCC diagnostic pop
int UltraCNN_Construct()

{
	AT_DEFAULTFLASH_FS_CONF_T DefaultFlashConf;

	int Error;
	AT_DEFAULTFLASH_FS_CONF_INIT(&DefaultFlashConf, AT_MEM_L3_DEFAULTFLASH, 0);
	AT_DEFAULTFLASH_FS_OPEN(&DefaultFlash, &DefaultFlashConf, "Ultra_L3_Flash_Const.dat", &Error);
	if (Error) return AT_FLASH_OPEN_ERROR;

	Ultra_L2_Memory = (AT_L2_POINTER) AT_L2_ALLOC(0, 259216);
	if (Ultra_L2_Memory == 0) return AT_L2_OPEN_ERROR;
	Ultra_L2_Memory_Dyn = (AT_L2_POINTER) AT_L2_ALLOC(0, 9728);
	if (Ultra_L2_Memory_Dyn == 0) return AT_L2_OPEN_ERROR;
	Ultra_L1_Memory = (AT_L1_POINTER) AT_L1_ALLOC(0, 29952);
	if (Ultra_L1_Memory == 0) return AT_L1_OPEN_ERROR;
	AT_DEFAULTFLASH_FS_FC_EVENT _UchanHF1, *UchanHF1 = &_UchanHF1;
	/* Static Moving Conv_0_weights, size 17280 from DefaultFlash at 240640 to (size 17280) L2 at 240640..257919 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Ultra_L3_Flash + 240640), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Ultra_L2_Memory + 240640), 17280, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_onnx__conv_120, size 128 from DefaultFlash at 257920 to (size 128) L2 at 257920..258047 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Ultra_L3_Flash + 257920), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Ultra_L2_Memory + 257920), 128, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Conv_2_weights, size 24576 from DefaultFlash at 0 to (size 24576) L2 at 0..24575 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Ultra_L3_Flash + 0), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Ultra_L2_Memory + 0), 24576, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_onnx__conv_123, size 128 from DefaultFlash at 258048 to (size 128) L2 at 258048..258175 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Ultra_L3_Flash + 258048), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Ultra_L2_Memory + 258048), 128, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Conv_4_weights, size 24576 from DefaultFlash at 24576 to (size 24576) L2 at 24576..49151 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Ultra_L3_Flash + 24576), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Ultra_L2_Memory + 24576), 24576, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_onnx__conv_126, size 128 from DefaultFlash at 258176 to (size 128) L2 at 258176..258303 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Ultra_L3_Flash + 258176), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Ultra_L2_Memory + 258176), 128, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Conv_6_weights, size 24576 from DefaultFlash at 49152 to (size 24576) L2 at 49152..73727 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Ultra_L3_Flash + 49152), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Ultra_L2_Memory + 49152), 24576, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_onnx__conv_129, size 128 from DefaultFlash at 258304 to (size 128) L2 at 258304..258431 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Ultra_L3_Flash + 258304), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Ultra_L2_Memory + 258304), 128, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Conv_9_weights, size 24576 from DefaultFlash at 73728 to (size 24576) L2 at 73728..98303 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Ultra_L3_Flash + 73728), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Ultra_L2_Memory + 73728), 24576, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_onnx__conv_132, size 128 from DefaultFlash at 258432 to (size 128) L2 at 258432..258559 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Ultra_L3_Flash + 258432), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Ultra_L2_Memory + 258432), 128, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Conv_11_weights, size 24576 from DefaultFlash at 98304 to (size 24576) L2 at 98304..122879 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Ultra_L3_Flash + 98304), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Ultra_L2_Memory + 98304), 24576, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_onnx__conv_135, size 128 from DefaultFlash at 258560 to (size 128) L2 at 258560..258687 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Ultra_L3_Flash + 258560), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Ultra_L2_Memory + 258560), 128, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Conv_13_weights, size 24576 from DefaultFlash at 122880 to (size 24576) L2 at 122880..147455 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Ultra_L3_Flash + 122880), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Ultra_L2_Memory + 122880), 24576, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_onnx__conv_138, size 128 from DefaultFlash at 258688 to (size 128) L2 at 258688..258815 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Ultra_L3_Flash + 258688), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Ultra_L2_Memory + 258688), 128, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Conv_16_weights, size 24576 from DefaultFlash at 147456 to (size 24576) L2 at 147456..172031 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Ultra_L3_Flash + 147456), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Ultra_L2_Memory + 147456), 24576, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_onnx__conv_141, size 128 from DefaultFlash at 258816 to (size 128) L2 at 258816..258943 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Ultra_L3_Flash + 258816), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Ultra_L2_Memory + 258816), 128, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Conv_18_weights, size 24576 from DefaultFlash at 172032 to (size 24576) L2 at 172032..196607 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Ultra_L3_Flash + 172032), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Ultra_L2_Memory + 172032), 24576, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_onnx__conv_144, size 128 from DefaultFlash at 258944 to (size 128) L2 at 258944..259071 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Ultra_L3_Flash + 258944), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Ultra_L2_Memory + 258944), 128, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Conv_20_weights, size 24576 from DefaultFlash at 196608 to (size 24576) L2 at 196608..221183 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Ultra_L3_Flash + 196608), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Ultra_L2_Memory + 196608), 24576, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Constant_onnx__conv_147, size 128 from DefaultFlash at 259072 to (size 128) L2 at 259072..259199 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Ultra_L3_Flash + 259072), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Ultra_L2_Memory + 259072), 128, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Gemm_30_weights, size 19456 from DefaultFlash at 221184 to (size 19456) L2 at 221184..240639 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Ultra_L3_Flash + 221184), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Ultra_L2_Memory + 221184), 19456, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	/* Static Moving Gemm_30_biases, size 16 from DefaultFlash at 259200 to (size 16) L2 at 259200..259215 */
	AT_DEFAULTFLASH_FS_FC_COPY(&DefaultFlash, ((AT_DEFAULTFLASH_FS_EXT_ADDR_TYPE) Ultra_L3_Flash + 259200), ((AT_DEFAULTFLASH_FS_INT_ADDR_TYPE) Ultra_L2_Memory + 259200), 16, 0, UchanHF1);
	AT_DEFAULTFLASH_FS_FC_WAIT(&DefaultFlash, UchanHF1);
	return AT_NO_ERROR;
}
void UltraCNN_ConstructCluster()

{
}
int UltraCNN_Destruct()

{
	AT_L2_FREE(0, Ultra_L2_Memory, 259216);
	AT_L2_FREE(0, Ultra_L2_Memory_Dyn, 9728);
	AT_L1_FREE(0, Ultra_L1_Memory, 29952);
	AT_DEFAULTFLASH_FS_CLOSE(&DefaultFlash);
	return 0;
}
int UltraCNN_Memory(AT_MEM_TYPE Which)

{
	switch (Which) {
		case AT_L1_MEM:     return 29952; /* L1 Memory */
		case AT_L2_MEM:     return 259216; /* L2 Memory, permanent */
		case AT_L2_DYN_MEM: return 9728; /* L2 Memory, dynamic */
		case AT_L3_MEM:     return 0; /* L3 Memory, permanent */
		case AT_L3_DYN_MEM: return 0; /* L3 Memory, dynamic */
		default:            return 0;
	}
}
unsigned int AT_GraphPerf[16];
unsigned int AT_GraphPerf_CNN_Total = 0;
unsigned int AT_GraphOperInfosNames[16] = {
	165376,
	234688,
	234688,
	233472,
	1216,
	234688,
	234688,
	233472,
	1216,
	234688,
	234688,
	233472,
	1216,
	9728,
	8,
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
int UltraCNN(
		F16 * __restrict__ Input_1,
		F16 * __restrict__ Output_1)

{
	unsigned int Start_IO;
	AT_GraphPerf_CNN_Total = gap_cl_readhwtimer();
	AT_GraphPerf[0] = gap_cl_readhwtimer();
	AT_GraphPerf[15] = 0;
	S4_Conv_0_fusion(
		((F16 * __restrict__) Input_1), /* In */
		((F16 * __restrict__) (Ultra_L2_Memory+240640)), /* Filter */
		((F16 * __restrict__) (Ultra_L2_Memory+257920)), /* Bias */
		((F16 * __restrict__) (Ultra_L2_Memory_Dyn+4864)) /* Out */
	);
	AT_GraphPerf[0] = gap_cl_readhwtimer() - AT_GraphPerf[0];
	AT_GraphPerf[1] = gap_cl_readhwtimer();
	S9_Conv_2_fusion(
		((F16 * __restrict__) (Ultra_L2_Memory_Dyn+4864)), /* In */
		((F16 * __restrict__) (Ultra_L2_Memory+0)), /* Filter */
		((F16 * __restrict__) (Ultra_L2_Memory+258048)), /* Bias */
		((F16 * __restrict__) (Ultra_L2_Memory_Dyn+0)) /* Out */
	);
	AT_GraphPerf[1] = gap_cl_readhwtimer() - AT_GraphPerf[1];
	AT_GraphPerf[2] = gap_cl_readhwtimer();
	S12_Conv_4_fusion(
		((F16 * __restrict__) (Ultra_L2_Memory_Dyn+0)), /* In */
		((F16 * __restrict__) (Ultra_L2_Memory+24576)), /* Filter */
		((F16 * __restrict__) (Ultra_L2_Memory+258176)), /* Bias */
		((F16 * __restrict__) (Ultra_L2_Memory_Dyn+2432)) /* Out */
	);
	AT_GraphPerf[2] = gap_cl_readhwtimer() - AT_GraphPerf[2];
	AT_GraphPerf[3] = gap_cl_readhwtimer();
	S15_Conv_6(
		((F16 * __restrict__) (Ultra_L2_Memory_Dyn+2432)), /* In */
		((F16 * __restrict__) (Ultra_L2_Memory+49152)), /* Filter */
		((F16 * __restrict__) (Ultra_L2_Memory+258304)), /* Bias */
		((F16 * __restrict__) (Ultra_L2_Memory_Dyn+0)) /* Out */
	);
	AT_GraphPerf[3] = gap_cl_readhwtimer() - AT_GraphPerf[3];
	AT_GraphPerf[4] = gap_cl_readhwtimer();
	S17_Add_7_fusion(
		((F16 * __restrict__) (Ultra_L2_Memory_Dyn+0)), /* In1 */
		((F16 * __restrict__) (Ultra_L2_Memory_Dyn+4864)), /* In2 */
		((F16 * __restrict__) (Ultra_L2_Memory_Dyn+2432)) /* Out */
	);
	AT_GraphPerf[4] = gap_cl_readhwtimer() - AT_GraphPerf[4];
	AT_GraphPerf[5] = gap_cl_readhwtimer();
	S21_Conv_9_fusion(
		((F16 * __restrict__) (Ultra_L2_Memory_Dyn+2432)), /* In */
		((F16 * __restrict__) (Ultra_L2_Memory+73728)), /* Filter */
		((F16 * __restrict__) (Ultra_L2_Memory+258432)), /* Bias */
		((F16 * __restrict__) (Ultra_L2_Memory_Dyn+0)) /* Out */
	);
	AT_GraphPerf[5] = gap_cl_readhwtimer() - AT_GraphPerf[5];
	AT_GraphPerf[6] = gap_cl_readhwtimer();
	S24_Conv_11_fusion(
		((F16 * __restrict__) (Ultra_L2_Memory_Dyn+0)), /* In */
		((F16 * __restrict__) (Ultra_L2_Memory+98304)), /* Filter */
		((F16 * __restrict__) (Ultra_L2_Memory+258560)), /* Bias */
		((F16 * __restrict__) (Ultra_L2_Memory_Dyn+7296)) /* Out */
	);
	AT_GraphPerf[6] = gap_cl_readhwtimer() - AT_GraphPerf[6];
	AT_GraphPerf[7] = gap_cl_readhwtimer();
	S27_Conv_13(
		((F16 * __restrict__) (Ultra_L2_Memory_Dyn+7296)), /* In */
		((F16 * __restrict__) (Ultra_L2_Memory+122880)), /* Filter */
		((F16 * __restrict__) (Ultra_L2_Memory+258688)), /* Bias */
		((F16 * __restrict__) (Ultra_L2_Memory_Dyn+4864)) /* Out */
	);
	AT_GraphPerf[7] = gap_cl_readhwtimer() - AT_GraphPerf[7];
	AT_GraphPerf[8] = gap_cl_readhwtimer();
	S29_Add_14_fusion(
		((F16 * __restrict__) (Ultra_L2_Memory_Dyn+4864)), /* In1 */
		((F16 * __restrict__) (Ultra_L2_Memory_Dyn+2432)), /* In2 */
		((F16 * __restrict__) (Ultra_L2_Memory_Dyn+0)) /* Out */
	);
	AT_GraphPerf[8] = gap_cl_readhwtimer() - AT_GraphPerf[8];
	AT_GraphPerf[9] = gap_cl_readhwtimer();
	S33_Conv_16_fusion(
		((F16 * __restrict__) (Ultra_L2_Memory_Dyn+0)), /* In */
		((F16 * __restrict__) (Ultra_L2_Memory+147456)), /* Filter */
		((F16 * __restrict__) (Ultra_L2_Memory+258816)), /* Bias */
		((F16 * __restrict__) (Ultra_L2_Memory_Dyn+2432)) /* Out */
	);
	AT_GraphPerf[9] = gap_cl_readhwtimer() - AT_GraphPerf[9];
	AT_GraphPerf[10] = gap_cl_readhwtimer();
	S36_Conv_18_fusion(
		((F16 * __restrict__) (Ultra_L2_Memory_Dyn+2432)), /* In */
		((F16 * __restrict__) (Ultra_L2_Memory+172032)), /* Filter */
		((F16 * __restrict__) (Ultra_L2_Memory+258944)), /* Bias */
		((F16 * __restrict__) (Ultra_L2_Memory_Dyn+7296)) /* Out */
	);
	AT_GraphPerf[10] = gap_cl_readhwtimer() - AT_GraphPerf[10];
	AT_GraphPerf[11] = gap_cl_readhwtimer();
	S39_Conv_20(
		((F16 * __restrict__) (Ultra_L2_Memory_Dyn+7296)), /* In */
		((F16 * __restrict__) (Ultra_L2_Memory+196608)), /* Filter */
		((F16 * __restrict__) (Ultra_L2_Memory+259072)), /* Bias */
		((F16 * __restrict__) (Ultra_L2_Memory_Dyn+4864)) /* Out */
	);
	AT_GraphPerf[11] = gap_cl_readhwtimer() - AT_GraphPerf[11];
	AT_GraphPerf[12] = gap_cl_readhwtimer();
	S41_Add_21_fusion(
		((F16 * __restrict__) (Ultra_L2_Memory_Dyn+4864)), /* In1 */
		((F16 * __restrict__) (Ultra_L2_Memory_Dyn+0)), /* In2 */
		((F16 * __restrict__) (Ultra_L2_Memory_Dyn+2432)) /* Out */
	);
	AT_GraphPerf[12] = gap_cl_readhwtimer() - AT_GraphPerf[12];
	AT_GraphPerf[13] = gap_cl_readhwtimer();
	S44_Gemm_30(
		((F16 * __restrict__) (Ultra_L2_Memory_Dyn+2432)), /* In */
		((F16 * __restrict__) (Ultra_L2_Memory+221184)), /* Filter */
		((F16 * __restrict__) (Ultra_L2_Memory+259200)), /* Bias */
		((F16 * __restrict__) (Ultra_L2_Memory_Dyn+0)) /* Out */
	);
	AT_GraphPerf[13] = gap_cl_readhwtimer() - AT_GraphPerf[13];
	AT_GraphPerf[14] = gap_cl_readhwtimer();
	S45_Softmax_31(
		((F16 * __restrict__) (Ultra_L2_Memory_Dyn+0)), /* In */
		((F16 * __restrict__) Output_1) /* Out */
	);
	AT_GraphPerf[14] = gap_cl_readhwtimer() - AT_GraphPerf[14];
	AT_GraphPerf_CNN_Total = gap_cl_readhwtimer() - AT_GraphPerf_CNN_Total;
	return 0;
}