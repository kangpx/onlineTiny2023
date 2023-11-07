#include <math.h>
#include "CNN_BasicKernels_fp16.h"
#include "online_training.h"

#if defined(OT_QVAR)
#define L1_IF_MEMORY        Qvar_L1_Memory
#define L2_MEMORY           Qvar_L2_Memory
#define L2_MEMORY_DYN       Qvar_L2_Memory_Dyn
#define L2_WEIGHT_ADDR      (L2_MEMORY + 0)
#define L2_BIAS_ADDR        (L2_MEMORY + 277120)
#define L2_DENSE_INPUT_ADDR (L2_MEMORY_DYN + 5120)

#elif defined(OT_ULTRA)
#define L1_IF_MEMORY        Ultra_L1_Memory
#define L2_MEMORY           Ultra_L2_Memory
#define L2_MEMORY_DYN       Ultra_L2_Memory_Dyn
#if (BOUT_C==32)
#define L2_WEIGHT_ADDR      (L2_MEMORY + 226176)
#define L2_BIAS_ADDR        (L2_MEMORY + 241280)
#define L2_DENSE_INPUT_ADDR (L2_MEMORY_DYN + 1216)
#elif (BOUT_C==64)
#define L2_WEIGHT_ADDR      (L2_MEMORY + 221184)
#define L2_BIAS_ADDR        (L2_MEMORY + 259200)
#define L2_DENSE_INPUT_ADDR (L2_MEMORY_DYN + 2432)
#endif

#elif defined(OT_GYM)
#define L1_IF_MEMORY        Gym_L1_Memory
#define L2_MEMORY           Gym_L2_Memory
#define L2_MEMORY_DYN       Gym_L2_Memory_Dyn
#if (BOUT_C==32)
#define L2_WEIGHT_ADDR      (L2_MEMORY + 0)
#define L2_BIAS_ADDR        (L2_MEMORY + 247680)
#define L2_DENSE_INPUT_ADDR (L2_MEMORY_DYN + 2560)
#elif (BOUT_C==64)
#define L2_WEIGHT_ADDR      (L2_MEMORY + 0)
#define L2_BIAS_ADDR        (L2_MEMORY + 286592)
#define L2_DENSE_INPUT_ADDR (L2_MEMORY_DYN + 5120)
#endif
#endif

#define L1_OT_MEMORY        Ot_L1_Memory

extern char *L1_IF_MEMORY;
extern char *L2_MEMORY;
extern char *L2_MEMORY_DYN;

L1_CL_MEM AT_L1_POINTER L1_OT_MEMORY = NULL;

unsigned char ot_flag;
unsigned char y_real;

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

AT_L2_EXT_ADDR_TYPE l2_dense_weights_ptr, l2_dense_biases_ptr, l2_dense_input_ptr, l2_out_data_ptr, l2_y_real_ptr;
AT_L2_INT_ADDR_TYPE l1_dense_weights_ptr, l1_dense_biases_ptr, l1_dense_input_ptr, l1_out_data_ptr, l1_y_real_ptr;

#if (OPTIMIZER==SGD)
AT_L2_EXT_ADDR_TYPE l2_w_icmt_t_cache_ptr, l2_b_icmt_t_cache_ptr;
AT_L2_EXT_ADDR_TYPE l1_w_icmt_t_cache_ptr, l1_b_icmt_t_cache_ptr;
#elif (OPTIMIZER==ADAM)
AT_L2_EXT_ADDR_TYPE l2_w_m_t_cache_ptr, l2_b_m_t_cache_ptr, l2_w_v_t_cache_ptr, l2_b_v_t_cache_ptr;
AT_L2_EXT_ADDR_TYPE l1_w_m_t_cache_ptr, l1_b_m_t_cache_ptr, l1_w_v_t_cache_ptr, l1_b_v_t_cache_ptr;
#endif

#if (OPTIMIZER==ADAM)
L1_CL_MEM F16 beta1_pow = BETA1;
L1_CL_MEM F16 beta2_pow = BETA2;
#endif


static inline float fastsqrt(float x)
{
    unsigned int i = *(unsigned int*) &x;
    i += 127 << 23;
    i >>= 1;
    return *(float*)&i;
}

void ot_reset_icmt_t_cache(void)
{
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

int ot_init_chunk(void)
{
#if (OPTIMIZER==SGD)
    L1_OT_MEMORY = (AT_L1_POINTER) AT_L1_ALLOC(0, DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK + DENSE_BIASES_SIZE_BYTES / NUM_CHUNK + DENSE_OUTPUT_SIZE_BYTES / NUM_CHUNK);
#elif (OPTIMIZER==ADAM)
    L1_OT_MEMORY = (AT_L1_POINTER) AT_L1_ALLOC(0, 2 * DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK + 2 * DENSE_BIASES_SIZE_BYTES / NUM_CHUNK + DENSE_OUTPUT_SIZE_BYTES / NUM_CHUNK);
#endif
    if (L1_OT_MEMORY == NULL) return -1;

    l2_dense_weights_ptr  = (AT_L2_EXT_ADDR_TYPE)(L2_WEIGHT_ADDR);
    l2_dense_biases_ptr   = (AT_L2_EXT_ADDR_TYPE)(L2_BIAS_ADDR);
    l2_dense_input_ptr    = (AT_L2_EXT_ADDR_TYPE)(L2_DENSE_INPUT_ADDR);
    l2_out_data_ptr       = (AT_L2_EXT_ADDR_TYPE)(out_data);
    l2_y_real_ptr         = (AT_L2_EXT_ADDR_TYPE)(&y_real);
#if (OPTIMIZER==SGD)
    l2_w_icmt_t_cache_ptr = (AT_L2_EXT_ADDR_TYPE)(w_icmt_t_cache);
    l2_b_icmt_t_cache_ptr = (AT_L2_EXT_ADDR_TYPE)(b_icmt_t_cache);
#elif (OPTIMIZER==ADAM)
    l2_w_m_t_cache_ptr    = (AT_L2_EXT_ADDR_TYPE)(w_m_t_cache);
    l2_w_v_t_cache_ptr    = (AT_L2_EXT_ADDR_TYPE)(w_v_t_cache);
    l2_b_m_t_cache_ptr    = (AT_L2_EXT_ADDR_TYPE)(b_m_t_cache);
    l2_b_v_t_cache_ptr    = (AT_L2_EXT_ADDR_TYPE)(b_v_t_cache);
#endif

    l1_dense_weights_ptr  = (AT_L2_INT_ADDR_TYPE)(L1_IF_MEMORY + 0);
    l1_dense_biases_ptr   = (AT_L2_INT_ADDR_TYPE)(L1_IF_MEMORY + DENSE_WEIGHTS_SIZE_BYTES);
    l1_dense_input_ptr    = (AT_L2_INT_ADDR_TYPE)(L1_IF_MEMORY + DENSE_WEIGHTS_SIZE_BYTES + DENSE_BIASES_SIZE_BYTES);
    l1_y_real_ptr         = (AT_L2_INT_ADDR_TYPE)(L1_IF_MEMORY + DENSE_WEIGHTS_SIZE_BYTES + DENSE_BIASES_SIZE_BYTES + DENSE_INPUT_SIZE_BYTES);
#if (OPTIMIZER==SGD)
    l1_w_icmt_t_cache_ptr = (AT_L2_INT_ADDR_TYPE)(L1_OT_MEMORY + 0);
    l1_b_icmt_t_cache_ptr = (AT_L2_INT_ADDR_TYPE)(L1_OT_MEMORY + DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK);
    l1_out_data_ptr       = (AT_L2_INT_ADDR_TYPE)(L1_OT_MEMORY + DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK + DENSE_BIASES_SIZE_BYTES / NUM_CHUNK);
#elif (OPTIMIZER==ADAM)
    l1_w_m_t_cache_ptr    = (AT_L2_INT_ADDR_TYPE)(L1_OT_MEMORY + 0);
    l1_w_v_t_cache_ptr    = (AT_L2_INT_ADDR_TYPE)(L1_OT_MEMORY + DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK);
    l1_b_m_t_cache_ptr    = (AT_L2_INT_ADDR_TYPE)(L1_OT_MEMORY + 2 * DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK);
    l1_b_v_t_cache_ptr    = (AT_L2_INT_ADDR_TYPE)(L1_OT_MEMORY + 2 * DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK + DENSE_BIASES_SIZE_BYTES / NUM_CHUNK);
    l1_out_data_ptr       = (AT_L2_INT_ADDR_TYPE)(L1_OT_MEMORY + 2 * DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK + 2 * DENSE_BIASES_SIZE_BYTES / NUM_CHUNK);
#endif

#if (OPTIMIZER==ADAM)
    beta1_pow = BETA1;
    beta2_pow = BETA2;
#endif

    ot_reset_icmt_t_cache();

    return 0;
}

void ot_clean_chunk(void)
{
#if (OPTIMIZER==SGD)
    if (L1_OT_MEMORY != NULL)
        AT_L1_FREE(0, L1_OT_MEMORY, DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK + DENSE_BIASES_SIZE_BYTES / NUM_CHUNK + DENSE_OUTPUT_SIZE_BYTES / NUM_CHUNK);
#elif (OPTIMIZER==ADAM)
    if (L1_OT_MEMORY != NULL)
        AT_L1_FREE(0, L1_OT_MEMORY, 2 * DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK + 2 * DENSE_BIASES_SIZE_BYTES / NUM_CHUNK + DENSE_OUTPUT_SIZE_BYTES / NUM_CHUNK);
#endif
}

void ot_update_core_chunk(unsigned int s_start, unsigned int s_end)
{
#if (OPTIMIZER==SGD)
    for (unsigned int s_global=s_start; s_global<s_end; s_global++){
        unsigned int s_local = s_global % (DENSE_OUTPUT_SIZE / NUM_CHUNK);
        for (unsigned int t_=0; t_<DENSE_INPUT_SIZE; t_++){
            unsigned int i_global = s_global * DENSE_INPUT_SIZE + t_;
            unsigned int i_local = s_local * DENSE_INPUT_SIZE + t_;
            ((F16*)l1_w_icmt_t_cache_ptr)[i_local] = MOMENTUM * ((F16*)l1_w_icmt_t_cache_ptr)[i_local] + (((F16*)l1_dense_input_ptr)[t_] * (((F16*)l1_out_data_ptr)[s_local] - ((((unsigned int)(l1_y_real_ptr[0])) == s_global) ? (F16)1.f : (F16)0.f)));
            ((F16*)l1_dense_weights_ptr)[i_global] -= LR * ((F16*)l1_w_icmt_t_cache_ptr)[i_local];
        } 
    }
    for (unsigned int s_global=s_start; s_global<s_end; s_global++){
        unsigned int s_local = s_global % (DENSE_OUTPUT_SIZE / NUM_CHUNK);
        ((F16*)l1_b_icmt_t_cache_ptr)[s_local] = MOMENTUM * ((F16*)l1_b_icmt_t_cache_ptr)[s_local] + ((((F16*)l1_out_data_ptr)[s_local] - ((((unsigned int)(l1_y_real_ptr[0])) == s_global) ? (F16)1.f : (F16)0.f)));
        ((F16*)l1_dense_biases_ptr)[s_global]  -= LR * ((F16*)l1_b_icmt_t_cache_ptr)[s_local];
    }
#elif (OPTIMIZER==ADAM)
    for (unsigned int s_global=s_start; s_global<s_end; s_global++){
        unsigned int s_local = s_global % (DENSE_OUTPUT_SIZE / NUM_CHUNK);
        for (unsigned int t_=0; t_<DENSE_INPUT_SIZE; t_++){
            unsigned int i_global = s_global * DENSE_INPUT_SIZE + t_;
            unsigned int i_local = s_local * DENSE_INPUT_SIZE + t_;
            F16 g_t = (((F16*)l1_dense_input_ptr)[t_] * (((F16*)l1_out_data_ptr)[s_local] - ((((unsigned int)(l1_y_real_ptr[0])) == s_global) ? (F16)1.f : (F16)0.f)));
            ((F16*)l1_w_m_t_cache_ptr)[i_local] = BETA1 * ((F16*)l1_w_m_t_cache_ptr)[i_local] + ((F16)1.0f - BETA1) * g_t;
            ((F16*)l1_w_v_t_cache_ptr)[i_local] = BETA2 * ((F16*)l1_w_v_t_cache_ptr)[i_local] + ((F16)1.0f - BETA2) * (g_t * g_t);
            F16 m_t_h = ((F16*)l1_w_m_t_cache_ptr)[i_local] / ((F16)1.0f - beta1_pow);
            F16 v_t_h = ((F16*)l1_w_v_t_cache_ptr)[i_local] / ((F16)1.0f - beta2_pow);
            ((F16*)l1_dense_weights_ptr)[i_global] -= LR * m_t_h / ((F16)fastsqrt((float)v_t_h) + EPS);
        } 
    }
    for (unsigned int s_global=s_start; s_global<s_end; s_global++){
        unsigned int s_local = s_global % (DENSE_OUTPUT_SIZE / NUM_CHUNK);
        F16 g_t = (((F16*)l1_out_data_ptr)[s_local] - ((((unsigned int)(l1_y_real_ptr[0])) == s_global) ? (F16)1.f : (F16)0.f));
        ((F16*)l1_b_m_t_cache_ptr)[s_local] = BETA1 * ((F16*)l1_b_m_t_cache_ptr)[s_local] + ((F16)1.0f - BETA1) * g_t;
        ((F16*)l1_b_v_t_cache_ptr)[s_local] = BETA2 * ((F16*)l1_b_v_t_cache_ptr)[s_local] + ((F16)1.0f - BETA2) * (g_t * g_t);
        F16 m_t_h = ((F16*)l1_b_m_t_cache_ptr)[s_local] / ((F16)1.0f - beta1_pow);
        F16 v_t_h = ((F16*)l1_b_v_t_cache_ptr)[s_local] / ((F16)1.0f - beta2_pow);
        ((F16*)l1_dense_biases_ptr)[s_global] -= LR * m_t_h / ((F16)fastsqrt((float)v_t_h) + EPS);
        //printf("m_t=%f, v_t=%f, BETA2=%f, beta2_pow=%f, demu=%f\n", m_t_h, v_t_h, BETA2, beta2_pow, ((F16)1.0f - beta2_pow));
    }
#endif
}

void ot_update_chunk(void)
{
    if (ot_flag){
        /* copy dense weights, dense biases, dense_input, y_real (full) into l1_mem */
        AT_L2_EVENT _DmaR_Evt1, *DmaR_Evt1 = &_DmaR_Evt1;
        AT_L2_COPY        (0, l2_dense_weights_ptr,  l1_dense_weights_ptr,  DENSE_WEIGHTS_SIZE_BYTES, 0, DmaR_Evt1);
        AT_L2_COPY_MERGED (0, l2_dense_biases_ptr,   l1_dense_biases_ptr,   DENSE_BIASES_SIZE_BYTES,  0, 0);
        AT_L2_COPY_MERGED (0, l2_dense_input_ptr,    l1_dense_input_ptr,    DENSE_INPUT_SIZE_BYTES,   0, 0);
        AT_L2_COPY_MERGED (0, l2_y_real_ptr,         l1_y_real_ptr,         sizeof(y_real),           0, 0);
        AT_L2_WAIT        (0, DmaR_Evt1);
        
        for (unsigned int i_chunk=0;  i_chunk<NUM_CHUNK; i_chunk++){
            /* copy w_icmt_t_cahce, b_icmt_t_cache, out_data (chunk) to l1_mem */
            AT_L2_EVENT _DmaR_Evt2, *DmaR_Evt2 = &_DmaR_Evt2;
            #if (OPTIMIZER==SGD)
            AT_L2_COPY        (0, l2_w_icmt_t_cache_ptr + i_chunk * (DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK), l1_w_icmt_t_cache_ptr, DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK,  0, DmaR_Evt2);
            AT_L2_COPY_MERGED (0, l2_b_icmt_t_cache_ptr + i_chunk * (DENSE_BIASES_SIZE_BYTES  / NUM_CHUNK), l1_b_icmt_t_cache_ptr, DENSE_BIASES_SIZE_BYTES  / NUM_CHUNK,  0, 0);
            AT_L2_COPY_MERGED (0, l2_out_data_ptr       + i_chunk * (DENSE_OUTPUT_SIZE_BYTES  / NUM_CHUNK), l1_out_data_ptr,       DENSE_OUTPUT_SIZE_BYTES  / NUM_CHUNK,  0, 0);
            AT_L2_WAIT        (0, DmaR_Evt2);
            #elif (OPTIMIZER==ADAM)
            AT_L2_COPY        (0, l2_w_m_t_cache_ptr    + i_chunk * (DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK), l1_w_m_t_cache_ptr,    DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK,  0, DmaR_Evt2);
            AT_L2_COPY_MERGED (0, l2_w_v_t_cache_ptr    + i_chunk * (DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK), l1_w_v_t_cache_ptr,    DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK,  0, 0);
            AT_L2_COPY_MERGED (0, l2_b_m_t_cache_ptr    + i_chunk * (DENSE_BIASES_SIZE_BYTES  / NUM_CHUNK), l1_b_m_t_cache_ptr,    DENSE_BIASES_SIZE_BYTES  / NUM_CHUNK,  0, 0);
            AT_L2_COPY_MERGED (0, l2_b_v_t_cache_ptr    + i_chunk * (DENSE_BIASES_SIZE_BYTES  / NUM_CHUNK), l1_b_v_t_cache_ptr,    DENSE_BIASES_SIZE_BYTES  / NUM_CHUNK,  0, 0);
            AT_L2_COPY_MERGED (0, l2_out_data_ptr       + i_chunk * (DENSE_OUTPUT_SIZE_BYTES  / NUM_CHUNK), l1_out_data_ptr,       DENSE_OUTPUT_SIZE_BYTES  / NUM_CHUNK,  0, 0);
            AT_L2_WAIT        (0, DmaR_Evt2);
            #endif

            /* update */
            ot_update_core_chunk(i_chunk * (DENSE_OUTPUT_SIZE / NUM_CHUNK), (i_chunk + 1) * (DENSE_OUTPUT_SIZE / NUM_CHUNK));

            /* write w_icmt_t_cahce, b_icmt_t_cache (chunk) back to l2_mem */
            AT_L2_EVENT _DmaW_Evt2, *DmaW_Evt2 = &_DmaW_Evt2;
            #if (OPTIMIZER==SGD)
            AT_L2_COPY        (0, l2_w_icmt_t_cache_ptr + i_chunk * (DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK), l1_w_icmt_t_cache_ptr, DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK, 1, DmaW_Evt2);
            AT_L2_COPY_MERGED (0, l2_b_icmt_t_cache_ptr + i_chunk * (DENSE_BIASES_SIZE_BYTES  / NUM_CHUNK), l1_b_icmt_t_cache_ptr, DENSE_BIASES_SIZE_BYTES  / NUM_CHUNK, 1, 0);
            AT_L2_WAIT        (0, DmaW_Evt2);
            #elif (OPTIMIZER==ADAM)
            AT_L2_COPY        (0, l2_w_m_t_cache_ptr    + i_chunk * (DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK), l1_w_m_t_cache_ptr,    DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK, 1, DmaW_Evt2);
            AT_L2_COPY_MERGED (0, l2_w_v_t_cache_ptr    + i_chunk * (DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK), l1_w_v_t_cache_ptr,    DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK, 1, 0);
            AT_L2_COPY_MERGED (0, l2_b_m_t_cache_ptr    + i_chunk * (DENSE_BIASES_SIZE_BYTES  / NUM_CHUNK), l1_b_m_t_cache_ptr,    DENSE_BIASES_SIZE_BYTES  / NUM_CHUNK, 1, 0);
            AT_L2_COPY_MERGED (0, l2_b_v_t_cache_ptr    + i_chunk * (DENSE_BIASES_SIZE_BYTES  / NUM_CHUNK), l1_b_v_t_cache_ptr,    DENSE_BIASES_SIZE_BYTES  / NUM_CHUNK, 1, 0);
            AT_L2_WAIT        (0, DmaW_Evt2);
            #endif
        }

        /* write dense weigths, dense biases (full) back to l2_mem */
        AT_L2_EVENT _DmaW_Evt1, *DmaW_Evt1 = &_DmaW_Evt1;
        AT_L2_COPY        (0, l2_dense_weights_ptr,  l1_dense_weights_ptr,  DENSE_WEIGHTS_SIZE_BYTES, 1, DmaW_Evt1);
        AT_L2_COPY_MERGED (0, l2_dense_biases_ptr,   l1_dense_biases_ptr,   DENSE_BIASES_SIZE_BYTES,  1, 0);
        AT_L2_WAIT        (0, DmaW_Evt1);

        #if (OPTIMIZER==ADAM)
        beta1_pow *= BETA1;
        beta2_pow *= BETA2;
        #endif
    }
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

void KerParOtUpdate_fp16(KerOtUpdate_fp16_T *Arg)
{
    unsigned int       N          = Arg->N;
    unsigned int       i_chunk    = Arg->i_chunk;
    unsigned int       CoreId     = gap_coreid();
    unsigned int       ChunkCell  = ChunkSize(N);
    unsigned int       First      = CoreId * ChunkCell + i_chunk * (DENSE_OUTPUT_SIZE / NUM_CHUNK);
    unsigned int       Last       = Min(First+ChunkCell, N + i_chunk * (DENSE_OUTPUT_SIZE / NUM_CHUNK));

    ot_update_core_chunk(First, Last);
    gap_waitbarrier(0);
}

void ot_update_chunk_parallel(void)
{
    if (ot_flag){
        /* copy dense weights, dense biases, dense_input, y_real (full) into l1_mem */
        AT_L2_EVENT _DmaR_Evt1, *DmaR_Evt1 = &_DmaR_Evt1;
        AT_L2_COPY        (0, l2_dense_weights_ptr,  l1_dense_weights_ptr,  DENSE_WEIGHTS_SIZE_BYTES, 0, DmaR_Evt1);
        AT_L2_COPY_MERGED (0, l2_dense_biases_ptr,   l1_dense_biases_ptr,   DENSE_BIASES_SIZE_BYTES,  0, 0);
        AT_L2_COPY_MERGED (0, l2_dense_input_ptr,    l1_dense_input_ptr,    DENSE_INPUT_SIZE_BYTES,   0, 0);
        AT_L2_COPY_MERGED (0, l2_y_real_ptr,         l1_y_real_ptr,         sizeof(y_real),           0, 0);
        AT_L2_WAIT        (0, DmaR_Evt1);
        
        for (unsigned int i_chunk=0;  i_chunk<NUM_CHUNK; i_chunk++){
            /* copy w_icmt_t_cahce, b_icmt_t_cache, out_data (chunk) to l1_mem */
            AT_L2_EVENT _DmaR_Evt2, *DmaR_Evt2 = &_DmaR_Evt2;
            #if (OPTIMIZER==SGD)
            AT_L2_COPY        (0, l2_w_icmt_t_cache_ptr + i_chunk * (DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK), l1_w_icmt_t_cache_ptr, DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK,  0, DmaR_Evt2);
            AT_L2_COPY_MERGED (0, l2_b_icmt_t_cache_ptr + i_chunk * (DENSE_BIASES_SIZE_BYTES  / NUM_CHUNK), l1_b_icmt_t_cache_ptr, DENSE_BIASES_SIZE_BYTES  / NUM_CHUNK,  0, 0);
            AT_L2_COPY_MERGED (0, l2_out_data_ptr       + i_chunk * (DENSE_OUTPUT_SIZE_BYTES  / NUM_CHUNK), l1_out_data_ptr,       DENSE_OUTPUT_SIZE_BYTES  / NUM_CHUNK,  0, 0);
            AT_L2_WAIT        (0, DmaR_Evt2);
            #elif (OPTIMIZER==ADAM)
            AT_L2_COPY        (0, l2_w_m_t_cache_ptr    + i_chunk * (DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK), l1_w_m_t_cache_ptr,    DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK,  0, DmaR_Evt2);
            AT_L2_COPY_MERGED (0, l2_w_v_t_cache_ptr    + i_chunk * (DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK), l1_w_v_t_cache_ptr,    DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK,  0, 0);
            AT_L2_COPY_MERGED (0, l2_b_m_t_cache_ptr    + i_chunk * (DENSE_BIASES_SIZE_BYTES  / NUM_CHUNK), l1_b_m_t_cache_ptr,    DENSE_BIASES_SIZE_BYTES  / NUM_CHUNK,  0, 0);
            AT_L2_COPY_MERGED (0, l2_b_v_t_cache_ptr    + i_chunk * (DENSE_BIASES_SIZE_BYTES  / NUM_CHUNK), l1_b_v_t_cache_ptr,    DENSE_BIASES_SIZE_BYTES  / NUM_CHUNK,  0, 0);
            AT_L2_COPY_MERGED (0, l2_out_data_ptr       + i_chunk * (DENSE_OUTPUT_SIZE_BYTES  / NUM_CHUNK), l1_out_data_ptr,       DENSE_OUTPUT_SIZE_BYTES  / NUM_CHUNK,  0, 0);
            AT_L2_WAIT        (0, DmaR_Evt2);
            #endif

            /* update */
            KerOtUpdate_fp16_T S_KerArg0, *KerArg0 = &S_KerArg0;
            KerArg0->N          = (DENSE_OUTPUT_SIZE / NUM_CHUNK);
            KerArg0->i_chunk    = i_chunk;

            AT_FORK(gap_ncore(), (void *) KerParOtUpdate_fp16, (void *) KerArg0);
            __CALL(KerParOtUpdate_fp16, KerArg0);

            /* write w_icmt_t_cahce, b_icmt_t_cache (chunk) back to l2_mem */
            AT_L2_EVENT _DmaW_Evt2, *DmaW_Evt2 = &_DmaW_Evt2;
            #if (OPTIMIZER==SGD)
            AT_L2_COPY        (0, l2_w_icmt_t_cache_ptr + i_chunk * (DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK), l1_w_icmt_t_cache_ptr, DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK, 1, DmaW_Evt2);
            AT_L2_COPY_MERGED (0, l2_b_icmt_t_cache_ptr + i_chunk * (DENSE_BIASES_SIZE_BYTES  / NUM_CHUNK), l1_b_icmt_t_cache_ptr, DENSE_BIASES_SIZE_BYTES  / NUM_CHUNK, 1, 0);
            AT_L2_WAIT        (0, DmaW_Evt2);
            #elif (OPTIMIZER==ADAM)
            AT_L2_COPY        (0, l2_w_m_t_cache_ptr    + i_chunk * (DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK), l1_w_m_t_cache_ptr,    DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK, 1, DmaW_Evt2);
            AT_L2_COPY_MERGED (0, l2_w_v_t_cache_ptr    + i_chunk * (DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK), l1_w_v_t_cache_ptr,    DENSE_WEIGHTS_SIZE_BYTES / NUM_CHUNK, 1, 0);
            AT_L2_COPY_MERGED (0, l2_b_m_t_cache_ptr    + i_chunk * (DENSE_BIASES_SIZE_BYTES  / NUM_CHUNK), l1_b_m_t_cache_ptr,    DENSE_BIASES_SIZE_BYTES  / NUM_CHUNK, 1, 0);
            AT_L2_COPY_MERGED (0, l2_b_v_t_cache_ptr    + i_chunk * (DENSE_BIASES_SIZE_BYTES  / NUM_CHUNK), l1_b_v_t_cache_ptr,    DENSE_BIASES_SIZE_BYTES  / NUM_CHUNK, 1, 0);
            AT_L2_WAIT        (0, DmaW_Evt2);
            #endif
        }

        /* write dense weigths, dense biases (full) back to l2_mem */
        AT_L2_EVENT _DmaW_Evt1, *DmaW_Evt1 = &_DmaW_Evt1;
        AT_L2_COPY        (0, l2_dense_weights_ptr,  l1_dense_weights_ptr,  DENSE_WEIGHTS_SIZE_BYTES, 1, DmaW_Evt1);
        AT_L2_COPY_MERGED (0, l2_dense_biases_ptr,   l1_dense_biases_ptr,   DENSE_BIASES_SIZE_BYTES,  1, 0);
        AT_L2_WAIT        (0, DmaW_Evt1);

        #if (OPTIMIZER==ADAM)
        beta1_pow *= BETA1;
        beta2_pow *= BETA2;
        #endif
    }
}

