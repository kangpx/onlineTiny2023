#include <math.h>
#include "CNN_BasicKernels_fp16.h"
#include "online_training.h"

#if defined(OT_QVAR)
#define L1_IF_MEMORY        Qvar_L1_Memory
#define L2_MEMORY           Qvar_L2_Memory
#define L2_MEMORY_DYN       Qvar_L2_Memory_Dyn
#define L2_WEIGHT_ADDR      (L2_MEMORY + 0)
#define L2_BIAS_ADDR        (L2_MEMORY + 83264)
#define L2_DENSE_INPUT_ADDR (L2_MEMORY_DYN + 2560)

#elif defined(OT_ULTRA)
#define L1_IF_MEMORY        Ultra_L1_Memory
#define L2_MEMORY           Ultra_L2_Memory
#define L2_MEMORY_DYN       Ultra_L2_Memory_Dyn
#define L2_WEIGHT_ADDR      (L2_MEMORY + 0)
#define L2_BIAS_ADDR        (L2_MEMORY + 74304)
#define L2_DENSE_INPUT_ADDR (L2_MEMORY_DYN + 1216)

#elif defined(OT_GYM)
#define L1_IF_MEMORY        Gym_L1_Memory
#define L2_MEMORY           Gym_L2_Memory
#define L2_MEMORY_DYN       Gym_L2_Memory_Dyn
#define L2_WEIGHT_ADDR      (L2_MEMORY + 0)
#define L2_BIAS_ADDR        (L2_MEMORY + 88000)
#define L2_DENSE_INPUT_ADDR (L2_MEMORY_DYN + 2560)
#endif

#define L1_OT_MEMORY        Ot_L1_Memory

extern AT_L1_POINTER L1_IF_MEMORY;
extern AT_L2_POINTER L2_MEMORY;
extern AT_L2_POINTER L2_MEMORY_DYN;
L1_CL_MEM AT_L1_POINTER L1_OT_MEMORY = NULL;

unsigned int ot_flag;
unsigned int y_real;

L2_MEM F16 in_data[INPUT_DATA_SIZE]           = {(F16)0.f};
L2_MEM F16 out_data[DENSE_OUTPUT_SIZE]        = {(F16)0.f};

#if (OPTIMIZER==SGD)
L2_MEM F16 w_icmt_t_cache[DENSE_WEIGHTS_SIZE] = {(F16)0.f};
L2_MEM F16 b_icmt_t_cache[DENSE_BIASES_SIZE]  = {(F16)0.f};
#elif (OPTIMIZER==ADAM)
L2_MEM F16 w_m_t_cache[DENSE_WEIGHTS_SIZE] = {(F16)0.f};
L2_MEM F16 w_v_t_cache[DENSE_WEIGHTS_SIZE] = {(F16)0.f};
L2_MEM F16 b_m_t_cache[DENSE_BIASES_SIZE]  = {(F16)0.f};
L2_MEM F16 b_v_t_cache[DENSE_BIASES_SIZE]  = {(F16)0.f};
#endif

L2_MEM AT_L2_POINTER l2_dense_weights_ptr, l2_dense_biases_ptr, l2_dense_input_ptr, l2_out_data_ptr, l2_y_real_ptr;
L1_CL_MEM AT_L1_POINTER l1_dense_weights_ptr, l1_dense_biases_ptr, l1_dense_input_ptr, l1_out_data_ptr, l1_y_real_ptr;

#if (OPTIMIZER==SGD)
L2_MEM AT_L2_POINTER l2_w_icmt_t_cache_ptr, l2_b_icmt_t_cache_ptr;
L1_CL_MEM AT_L1_POINTER l1_w_icmt_t_cache_ptr, l1_b_icmt_t_cache_ptr;
#elif (OPTIMIZER==ADAM)
L2_MEM AT_L2_POINTER l2_w_m_t_cache_ptr, l2_b_m_t_cache_ptr, l2_w_v_t_cache_ptr, l2_b_v_t_cache_ptr;
L1_CL_MEM AT_L1_POINTER l1_w_m_t_cache_ptr, l1_b_m_t_cache_ptr, l1_w_v_t_cache_ptr, l1_b_v_t_cache_ptr;
#endif

#if (OPTIMIZER==ADAM)
L1_CL_MEM F16 beta1_pow = BETA1;
L1_CL_MEM F16 beta2_pow = BETA2;
#endif


static inline float fastsqrt(float x){
    unsigned int i = *(unsigned int*) &x;
    i += 127 << 23;
    i >>= 1;
    return *(float*)&i;
}

void ot_reset_icmt_t_cache(void){
    #if (OPTIMIZER==SGD)
    for (unsigned int i=0; i<DENSE_WEIGHTS_SIZE; i++)
        ((F16*)w_icmt_t_cache)[i] = (F16)0.0f;
    for (unsigned int i=0; i<DENSE_BIASES_SIZE; i++)
        ((F16*)b_icmt_t_cache)[i] = (F16)0.0f;
    #elif (OPTIMZIER==ADAM)
    for (unsigned int i=0; i<DENSE_WEIGHTS_SIZE; i++){
        ((F16*)w_m_t_cache)[i] = (F16)0.0f;
        ((F16*)w_v_t_cache)[i] = (F16)0.0f;
    }
    for (unsigned int i=0; i<DENSE_BIASES_SIZE; i++){
        ((F16*)b_m_t_cache)[i] = (F16)0.0f;
        ((F16*)b_v_t_cache)[i] = (F16)0.0f;
    }
    #endif
}

int ot_init_chunk(void){
#if (OPTIMIZER==SGD)
    L1_OT_MEMORY = (AT_L1_POINTER) AT_L1_ALLOC(0, DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK + DENSE_BIASES_SIZE_BYTES / NUM_CHUNK + DENSE_OUTPUT_SIZE_BYTES / NUM_CHUNK);
#elif (OPTIMIZER==ADAM)
    L1_OT_MEMORY = (AT_L1_POINTER) AT_L1_ALLOC(0, 2 * DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK + 2 * DENSE_BIASES_SIZE_BYTES / NUM_CHUNK + DENSE_OUTPUT_SIZE_BYTES / NUM_CHUNK);
#endif
    if (L1_OT_MEMORY == 0) return -1;

    l2_dense_weights_ptr  = L2_WEIGHT_ADDR;
    l2_dense_biases_ptr   = L2_BIAS_ADDR;
    l2_dense_input_ptr    = L2_DENSE_INPUT_ADDR;
    l2_out_data_ptr       = (AT_L2_POINTER)out_data;
    l2_y_real_ptr         = (AT_L2_POINTER)(&y_real);
#if (OPTIMIZER==SGD)
    l2_w_icmt_t_cache_ptr = (AT_L2_POINTER)(w_icmt_t_cache);
    l2_b_icmt_t_cache_ptr = (AT_L2_POINTER)(b_icmt_t_cache);
#elif (OPTIMIZER==ADAM)
    l2_w_m_t_cache_ptr    = (AT_L2_POINTER)(w_m_t_cache);
    l2_w_v_t_cache_ptr    = (AT_L2_POINTER)(w_v_t_cache);
    l2_b_m_t_cache_ptr    = (AT_L2_POINTER)(b_m_t_cache);
    l2_b_v_t_cache_ptr    = (AT_L2_POINTER)(b_v_t_cache);
#endif

    l1_dense_weights_ptr  = (L1_IF_MEMORY + 0);
    l1_dense_biases_ptr   = (L1_IF_MEMORY + DENSE_WEIGHTS_SIZE_BYTES);
    l1_dense_input_ptr    = (L1_IF_MEMORY + DENSE_WEIGHTS_SIZE_BYTES + DENSE_BIASES_SIZE_BYTES);
    l1_y_real_ptr         = (L1_IF_MEMORY + DENSE_WEIGHTS_SIZE_BYTES + DENSE_BIASES_SIZE_BYTES + DENSE_INPUT_SIZE_BYTES);
#if (OPTIMIZER==SGD)
    l1_w_icmt_t_cache_ptr = (L1_OT_MEMORY + 0);
    l1_b_icmt_t_cache_ptr = (L1_OT_MEMORY + DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK);
    l1_out_data_ptr       = (L1_OT_MEMORY + DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK + DENSE_BIASES_SIZE_BYTES / NUM_CHUNK);
#elif (OPTIMIZER==ADAM)
    l1_w_m_t_cache_ptr    = (L1_OT_MEMORY + 0);
    l1_w_v_t_cache_ptr    = (L1_OT_MEMORY + DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK);
    l1_b_m_t_cache_ptr    = (L1_OT_MEMORY + 2 * DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK);
    l1_b_v_t_cache_ptr    = (L1_OT_MEMORY + 2 * DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK + DENSE_BIASES_SIZE_BYTES / NUM_CHUNK);
    l1_out_data_ptr       = (L1_OT_MEMORY + 2 * DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK + 2 * DENSE_BIASES_SIZE_BYTES / NUM_CHUNK);
#endif

#if (OPTIMIZER==ADAM)
    beta1_pow = BETA1;
    beta2_pow = BETA2;
#endif

    ot_reset_icmt_t_cache();

    return 0;
}

void ot_clean_chunk(void){
#if (OPTIMIZER==SGD)
    if (L1_OT_MEMORY != NULL)
        AT_L1_FREE(0, L1_OT_MEMORY, DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK + DENSE_BIASES_SIZE_BYTES / NUM_CHUNK + DENSE_OUTPUT_SIZE_BYTES / NUM_CHUNK);
#elif (OPTIMIZER==ADAM)
    if (L1_OT_MEMORY != NULL)
        AT_L1_FREE(0, L1_OT_MEMORY, 2 * DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK + 2 * DENSE_BIASES_SIZE_BYTES / NUM_CHUNK + DENSE_OUTPUT_SIZE_BYTES / NUM_CHUNK);
#endif
}

static int CoreCountDynamic = 1;
static int ActiveCore = gap_ncore();
static inline unsigned int __attribute__((always_inline)) ChunkSize(unsigned int X)
{
	unsigned int NCore;
	unsigned int Log2Core;
	unsigned int Chunk;

	if (CoreCountDynamic) NCore = ActiveCore; else NCore = gap_ncore();
	Log2Core = gap_fl1(NCore);
	Chunk = (X>>Log2Core) + ((X&(NCore-1))!=0);
	return Chunk;
}

void KerParOtUpdate_fp16(KerOtUpdate_fp16_T *Arg){
    unsigned int       i_chunk                = Arg->i_chunk;
    unsigned int       N                      = Arg->N;
    unsigned int * __restrict__    y_ptr      = Arg->y_ptr;
    F16 *__restrict__ w_ptr                   = Arg->w_ptr;
    F16 *__restrict__ b_ptr                   = Arg->b_ptr;
    F16 *__restrict__ i_ptr                   = Arg->i_ptr;
    F16 *__restrict__ o_ptr                   = Arg->o_ptr;
#if (OPTIMIZER==SGD)
    F16 *__restrict__ w_icmt_ptr              = Arg->w_icmt_ptr;
    F16 *__restrict__ b_icmt_ptr              = Arg->b_icmt_ptr;
#elif (OPTIMIZER==ADAM)
    F16 * __restrict__ w_m_icmt_ptr           = Arg->w_m_icmt_ptr;
    F16 * __restrict__ w_v_icmt_ptr           = Arg->w_v_icmt_ptr;
    F16 * __restrict__ b_m_icmt_ptr           = Arg->b_m_icmt_ptr;
    F16 * __restrict__ b_v_icmt_ptr           = Arg->b_v_icmt_ptr;
#endif
    unsigned int       CoreId     = gap_coreid();
    unsigned int       ChunkCell  = ChunkSize(N);
    unsigned int       First      = CoreId * ChunkCell + i_chunk * (DENSE_OUTPUT_SIZE / NUM_CHUNK);
    unsigned int       Last       = Min(First+ChunkCell, N + i_chunk * (DENSE_OUTPUT_SIZE / NUM_CHUNK));
#if (OPTIMIZER==SGD)
    for (unsigned int s_global=First; s_global<Last; s_global++){
        unsigned int s_local = s_global % (DENSE_OUTPUT_SIZE / NUM_CHUNK);
        for (unsigned int t_=0; t_<DENSE_INPUT_SIZE; t_++){
            unsigned int i_global = s_global * DENSE_INPUT_SIZE + t_;
            unsigned int i_local = s_local * DENSE_INPUT_SIZE + t_;
            w_icmt_ptr[i_local] = MOMENTUM * w_icmt_ptr[i_local] + i_ptr[t_] * (o_ptr[s_local] - ((*y_ptr == s_global) ? (F16)1.0f : (F16)0.0f));
            w_ptr[i_global] -= LR * w_icmt_ptr[i_local];
        } 
        b_icmt_ptr[s_local] = MOMENTUM * b_icmt_ptr[s_local] + o_ptr[s_local] - ((*y_ptr == s_global) ? (F16)1.0f : (F16)0.0f);
        b_ptr[s_global]  -= LR * b_icmt_ptr[s_local];
    }
#elif (OPTIMIZER==ADAM)
    for (unsigned int s_global=First; s_global<Last; s_global++){
        unsigned int s_local = s_global % (DENSE_OUTPUT_SIZE / NUM_CHUNK);
        for (unsigned int t_=0; t_<DENSE_INPUT_SIZE; t_++){
            unsigned int i_global = s_global * DENSE_INPUT_SIZE + t_;
            unsigned int i_local = s_local * DENSE_INPUT_SIZE + t_;
            F16 g_t = i_ptr[t_] * (o_ptr[s_local] - ((*y_ptr == s_global) ? (F16)1.f : (F16)0.f));
            w_m_icmt_ptr[i_local] = BETA1 * w_m_icmt_ptr[i_local] + ((F16)1.0f - BETA1) * g_t;
            w_v_icmt_ptr[i_local] = BETA2 * w_v_icmt_ptr[i_local] + ((F16)1.0f - BETA2) * (g_t * g_t);
            F16 m_t_h = w_m_icmt_ptr[i_local] / ((F16)1.0f - beta1_pow);
            F16 v_t_h = w_v_icmt_ptr[i_local] / ((F16)1.0f - beta2_pow);
            w_ptr[i_global] -= LR * m_t_h / ((F16)fastsqrt((float)v_t_h) + EPS);
        } 
        F16 g_t = o_ptr[s_local] - ((*y_ptr == s_global) ? (F16)1.f : (F16)0.f);
        b_m_icmt_ptr[s_local] = BETA1 * b_m_icmt_ptr[s_local] + ((F16)1.0f - BETA1) * g_t;
        b_v_icmt_ptr[s_local] = BETA2 * b_v_icmt_ptr[s_local] + ((F16)1.0f - BETA2) * (g_t * g_t);
        F16 m_t_h = b_m_icmt_ptr[s_local] / ((F16)1.0f - beta1_pow);
        F16 v_t_h = b_v_icmt_ptr[s_local] / ((F16)1.0f - beta2_pow);
        b_ptr[s_global] -= LR * m_t_h / ((F16)fastsqrt((float)v_t_h) + EPS);
    }
#endif
    gap_waitbarrier(0);
}

void ot_update_chunk_parallel(void)
{
    if (ot_flag){
        /* copy dense weights, dense biases, dense_input, y_real (full) into l1_mem */
        AT_L2_EVENT _DmaR_Evt1, *DmaR_Evt1 = &_DmaR_Evt1;
        AT_L2_COPY        (0, (AT_L2_EXT_ADDR_TYPE)l2_dense_weights_ptr,  (AT_L2_INT_ADDR_TYPE)l1_dense_weights_ptr,  DENSE_WEIGHTS_SIZE_BYTES, 0, DmaR_Evt1);
        AT_L2_COPY_MERGED (0, (AT_L2_EXT_ADDR_TYPE)l2_dense_biases_ptr,   (AT_L2_INT_ADDR_TYPE)l1_dense_biases_ptr,   DENSE_BIASES_SIZE_BYTES,  0, 0);
        AT_L2_COPY_MERGED (0, (AT_L2_EXT_ADDR_TYPE)l2_dense_input_ptr,    (AT_L2_INT_ADDR_TYPE)l1_dense_input_ptr,    DENSE_INPUT_SIZE_BYTES,   0, 0);
        AT_L2_COPY_MERGED (0, (AT_L2_EXT_ADDR_TYPE)l2_y_real_ptr,         (AT_L2_INT_ADDR_TYPE)l1_y_real_ptr,         sizeof(y_real),           0, 0);
        AT_L2_WAIT        (0, DmaR_Evt1);
        
        for (unsigned int i_chunk=0;  i_chunk<NUM_CHUNK; i_chunk++){
            /* copy w_icmt_t_cahce, b_icmt_t_cache, out_data (chunk) to l1_mem */
            AT_L2_EVENT _DmaR_Evt2, *DmaR_Evt2 = &_DmaR_Evt2;
            #if (OPTIMIZER==SGD)
            AT_L2_COPY        (0, (AT_L2_EXT_ADDR_TYPE)(l2_w_icmt_t_cache_ptr + i_chunk * (DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK)), (AT_L2_INT_ADDR_TYPE)l1_w_icmt_t_cache_ptr, DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK,  0, DmaR_Evt2);
            AT_L2_COPY_MERGED (0, (AT_L2_EXT_ADDR_TYPE)(l2_b_icmt_t_cache_ptr + i_chunk * (DENSE_BIASES_SIZE_BYTES  / NUM_CHUNK)), (AT_L2_INT_ADDR_TYPE)l1_b_icmt_t_cache_ptr, DENSE_BIASES_SIZE_BYTES  / NUM_CHUNK,  0, 0);
            AT_L2_COPY_MERGED (0, (AT_L2_EXT_ADDR_TYPE)(l2_out_data_ptr       + i_chunk * (DENSE_OUTPUT_SIZE_BYTES  / NUM_CHUNK)), (AT_L2_INT_ADDR_TYPE)l1_out_data_ptr,       DENSE_OUTPUT_SIZE_BYTES  / NUM_CHUNK,  0, 0);
            AT_L2_WAIT        (0, DmaR_Evt2);
            #elif (OPTIMIZER==ADAM)
            AT_L2_COPY        (0, (AT_L2_EXT_ADDR_TYPE)(l2_w_m_t_cache_ptr    + i_chunk * (DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK)), (AT_L2_INT_ADDR_TYPE)l1_w_m_t_cache_ptr,    DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK,  0, DmaR_Evt2);
            AT_L2_COPY_MERGED (0, (AT_L2_EXT_ADDR_TYPE)(l2_w_v_t_cache_ptr    + i_chunk * (DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK)), (AT_L2_INT_ADDR_TYPE)l1_w_v_t_cache_ptr,    DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK,  0, 0);
            AT_L2_COPY_MERGED (0, (AT_L2_EXT_ADDR_TYPE)(l2_b_m_t_cache_ptr    + i_chunk * (DENSE_BIASES_SIZE_BYTES  / NUM_CHUNK)), (AT_L2_INT_ADDR_TYPE)l1_b_m_t_cache_ptr,    DENSE_BIASES_SIZE_BYTES  / NUM_CHUNK,  0, 0);
            AT_L2_COPY_MERGED (0, (AT_L2_EXT_ADDR_TYPE)(l2_b_v_t_cache_ptr    + i_chunk * (DENSE_BIASES_SIZE_BYTES  / NUM_CHUNK)), (AT_L2_INT_ADDR_TYPE)l1_b_v_t_cache_ptr,    DENSE_BIASES_SIZE_BYTES  / NUM_CHUNK,  0, 0);
            AT_L2_COPY_MERGED (0, (AT_L2_EXT_ADDR_TYPE)(l2_out_data_ptr       + i_chunk * (DENSE_OUTPUT_SIZE_BYTES  / NUM_CHUNK)), (AT_L2_INT_ADDR_TYPE)l1_out_data_ptr,       DENSE_OUTPUT_SIZE_BYTES  / NUM_CHUNK,  0, 0);
            AT_L2_WAIT        (0, DmaR_Evt2);
            #endif

            /* update */
            KerOtUpdate_fp16_T S_KerArg0, *KerArg0 = &S_KerArg0;
            KerArg0->N          = (DENSE_OUTPUT_SIZE / NUM_CHUNK);
            KerArg0->i_chunk    = i_chunk;
            KerArg0->y_ptr      = (unsigned int *__restrict__)l1_y_real_ptr ;
            KerArg0->w_ptr      = (F16 *__restrict__)l1_dense_weights_ptr;
            KerArg0->b_ptr      = (F16 *__restrict__)l1_dense_biases_ptr;
            KerArg0->i_ptr      = (F16 *__restrict__)l1_dense_input_ptr;
            KerArg0->o_ptr      = (F16 *__restrict__)l1_out_data_ptr;
            #if(OPTIMIZER==SGD)
            KerArg0->w_icmt_ptr = (F16 *__restrict__)l1_w_icmt_t_cache_ptr;
            KerArg0->b_icmt_ptr = (F16 *__restrict__)l1_b_icmt_t_cache_ptr;
            #elif(OPTIMIZER==ADAM)
            KerArg0->w_m_icmt_ptr = (F16 *__restrict__)l1_w_m_t_cache_ptr;
            KerArg0->w_v_icmt_ptr = (F16 *__restrict__)l1_w_v_t_cache_ptr;
            KerArg0->b_m_icmt_ptr = (F16 *__restrict__)l1_b_m_t_cache_ptr;
            KerArg0->b_v_icmt_ptr = (F16 *__restrict__)l1_b_v_t_cache_ptr;
            #endif

            AT_FORK(gap_ncore(), (void *) KerParOtUpdate_fp16, (void *) KerArg0);
            __CALL(KerParOtUpdate_fp16, KerArg0);

            /* write w_icmt_t_cahce, b_icmt_t_cache (chunk) back to l2_mem */
            AT_L2_EVENT _DmaW_Evt2, *DmaW_Evt2 = &_DmaW_Evt2;
            #if (OPTIMIZER==SGD)
            AT_L2_COPY        (0, (AT_L2_EXT_ADDR_TYPE)(l2_w_icmt_t_cache_ptr + i_chunk * (DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK)), (AT_L2_INT_ADDR_TYPE)l1_w_icmt_t_cache_ptr, DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK, 1, DmaW_Evt2);
            AT_L2_COPY_MERGED (0, (AT_L2_EXT_ADDR_TYPE)(l2_b_icmt_t_cache_ptr + i_chunk * (DENSE_BIASES_SIZE_BYTES  / NUM_CHUNK)), (AT_L2_INT_ADDR_TYPE)l1_b_icmt_t_cache_ptr, DENSE_BIASES_SIZE_BYTES  / NUM_CHUNK, 1, 0);
            AT_L2_WAIT        (0, DmaW_Evt2);
            #elif (OPTIMIZER==ADAM)
            AT_L2_COPY        (0, (AT_L2_EXT_ADDR_TYPE)(l2_w_m_t_cache_ptr    + i_chunk * (DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK)), (AT_L2_INT_ADDR_TYPE)l1_w_m_t_cache_ptr,    DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK, 1, DmaW_Evt2);
            AT_L2_COPY_MERGED (0, (AT_L2_EXT_ADDR_TYPE)(l2_w_v_t_cache_ptr    + i_chunk * (DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK)), (AT_L2_INT_ADDR_TYPE)l1_w_v_t_cache_ptr,    DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK, 1, 0);
            AT_L2_COPY_MERGED (0, (AT_L2_EXT_ADDR_TYPE)(l2_b_m_t_cache_ptr    + i_chunk * (DENSE_BIASES_SIZE_BYTES  / NUM_CHUNK)), (AT_L2_INT_ADDR_TYPE)l1_b_m_t_cache_ptr,    DENSE_BIASES_SIZE_BYTES  / NUM_CHUNK, 1, 0);
            AT_L2_COPY_MERGED (0, (AT_L2_EXT_ADDR_TYPE)(l2_b_v_t_cache_ptr    + i_chunk * (DENSE_BIASES_SIZE_BYTES  / NUM_CHUNK)), (AT_L2_INT_ADDR_TYPE)l1_b_v_t_cache_ptr,    DENSE_BIASES_SIZE_BYTES  / NUM_CHUNK, 1, 0);
            AT_L2_WAIT        (0, DmaW_Evt2);
            #endif
        }

        /* write dense weigths, dense biases (full) back to l2_mem */
        AT_L2_EVENT _DmaW_Evt1, *DmaW_Evt1 = &_DmaW_Evt1;
        AT_L2_COPY        (0, (AT_L2_EXT_ADDR_TYPE)l2_dense_weights_ptr,  (AT_L2_INT_ADDR_TYPE)l1_dense_weights_ptr,  DENSE_WEIGHTS_SIZE_BYTES, 1, DmaW_Evt1);
        AT_L2_COPY_MERGED (0, (AT_L2_EXT_ADDR_TYPE)l2_dense_biases_ptr,   (AT_L2_INT_ADDR_TYPE)l1_dense_biases_ptr,   DENSE_BIASES_SIZE_BYTES,  1, 0);
        AT_L2_WAIT        (0, DmaW_Evt1);

        #if (OPTIMIZER==ADAM)
        beta1_pow *= BETA1;
        beta2_pow *= BETA2;
        #endif
    }
}

