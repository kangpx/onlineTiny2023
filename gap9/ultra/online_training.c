#include "CNN_BasicKernels_fp16.h"
#include "online_training.h"

extern char *Ultra_L1_Memory;
extern char *Ultra_L2_Memory;
extern char *Ultra_L2_Memory_Dyn;
L1_CL_MEM AT_L1_POINTER Ot_L1_Memory = NULL;

unsigned char ot_flag;
unsigned char y_real;

L2_MEM F16 in_data[INPUT_DATA_SIZE]           = {(F16)0};
L2_MEM F16 out_data[DENSE_OUTPUT_SIZE]        = {(F16)0};

// L2_MEM F16 dense_input[DENSE_INPUT_SIZE]      = {(F16)0};

L2_MEM F16 w_icmt_t_cache[DENSE_WEIGHTS_SIZE] = {(F16)0};
L2_MEM F16 b_icmt_t_cache[DENSE_BIASES_SIZE]  = {(F16)0};

AT_L2_EXT_ADDR_TYPE l2_dense_weights_ptr, l2_dense_biases_ptr, l2_dense_input_ptr, l2_out_data_ptr, l2_y_real_ptr, l2_w_icmt_t_cache_ptr, l2_b_icmt_t_cache_ptr;
AT_L2_INT_ADDR_TYPE l1_dense_weights_ptr, l1_dense_biases_ptr, l1_out_data_ptr, l1_y_real_ptr, l1_w_icmt_t_cache_ptr, l1_b_icmt_t_cache_ptr, l1_dense_input_ptr;


void ot_reset_icmt_t_cache(void)
{
    for (unsigned int i=0; i<DENSE_WEIGHTS_SIZE; i++)
        ((F16*)w_icmt_t_cache)[i] = (F16)0;

    for (unsigned int i=0; i<DENSE_BIASES_SIZE; i++)
        ((F16*)b_icmt_t_cache)[i] = (F16)0;
}

void ot_init(void)
{
    Ot_L1_Memory = (AT_L1_POINTER) AT_L1_ALLOC(0, DENSE_WEIGHTS_SIZE_BYTES + DENSE_BIASES_SIZE_BYTES + DENSE_INPUT_SIZE_BYTES);
    if (Ot_L1_Memory == 0) return AT_L1_OPEN_ERROR;

    l2_dense_weights_ptr  = (AT_L2_EXT_ADDR_TYPE)(Ultra_L2_Memory + 221184);
    l2_dense_biases_ptr   = (AT_L2_EXT_ADDR_TYPE)(Ultra_L2_Memory + 259200);
    // l2_dense_input_ptr    = (AT_L2_EXT_ADDR_TYPE)(dense_input);
    l2_dense_input_ptr    = (AT_L2_EXT_ADDR_TYPE)(Ultra_L2_Memory_Dyn+2432);
    l2_out_data_ptr       = (AT_L2_EXT_ADDR_TYPE)(out_data);
    l2_y_real_ptr         = (AT_L2_EXT_ADDR_TYPE)(&y_real);
    l2_w_icmt_t_cache_ptr = (AT_L2_EXT_ADDR_TYPE)(w_icmt_t_cache);
    l2_b_icmt_t_cache_ptr = (AT_L2_EXT_ADDR_TYPE)(b_icmt_t_cache);

    l1_dense_weights_ptr  = (AT_L2_INT_ADDR_TYPE)(Ultra_L1_Memory + 0);
    l1_dense_biases_ptr   = (AT_L2_INT_ADDR_TYPE)(Ultra_L1_Memory + DENSE_WEIGHTS_SIZE_BYTES);
    l1_out_data_ptr       = (AT_L2_INT_ADDR_TYPE)(Ultra_L1_Memory + DENSE_WEIGHTS_SIZE_BYTES + DENSE_BIASES_SIZE_BYTES);
    l1_y_real_ptr         = (AT_L2_INT_ADDR_TYPE)(Ultra_L1_Memory + DENSE_WEIGHTS_SIZE_BYTES + DENSE_BIASES_SIZE_BYTES + DENSE_OUTPUT_SIZE_BYTES);
    l1_w_icmt_t_cache_ptr = (AT_L2_INT_ADDR_TYPE)(Ot_L1_Memory + 0);
    l1_b_icmt_t_cache_ptr = (AT_L2_INT_ADDR_TYPE)(Ot_L1_Memory + DENSE_WEIGHTS_SIZE_BYTES);
    l1_dense_input_ptr    = (AT_L2_INT_ADDR_TYPE)(Ot_L1_Memory + DENSE_WEIGHTS_SIZE_BYTES + DENSE_BIASES_SIZE_BYTES);

    ot_reset_icmt_t_cache();
}

void ot_clean(void)
{
    if (Ot_L1_Memory != NULL){
        AT_L1_FREE(0, Ot_L1_Memory, DENSE_WEIGHTS_SIZE_BYTES + DENSE_BIASES_SIZE_BYTES + DENSE_INPUT_SIZE_BYTES);
    }
}

void ot_retrieve_dense_input(AT_L2_INT_ADDR_TYPE l1_mem_src_ptr)
{
    if (ot_flag){
        AT_L2_EVENT _DmaW_Evt1, *DmaW_Evt1 = &_DmaW_Evt1;
        AT_L2_COPY(0, l2_dense_input_ptr, l1_mem_src_ptr, DENSE_INPUT_SIZE_BYTES, 1, DmaW_Evt1);
        AT_L2_WAIT(0, DmaW_Evt1);
    }
}

void ot_update_core(void)
{
    for (unsigned int s_=0; s_<DENSE_OUTPUT_SIZE; s_++){
        for (unsigned int t_=0; t_<DENSE_INPUT_SIZE; t_++){
            unsigned int i_ = s_ * DENSE_INPUT_SIZE + t_;
            ((F16*)l1_w_icmt_t_cache_ptr)[i_] = MOMENTUM * ((F16*)l1_w_icmt_t_cache_ptr)[i_] + (((F16*)l1_dense_input_ptr)[t_] * (((F16*)l1_out_data_ptr)[s_] - ((((unsigned int)(l1_y_real_ptr[0])) == s_) ? (F16)1 : (F16)0)));
            ((F16*)l1_dense_weights_ptr)[i_] -= LR * ((F16*)l1_w_icmt_t_cache_ptr)[i_];
        } 
    }
    for (unsigned int s_=0; s_<DENSE_OUTPUT_SIZE; s_++){
        ((F16*)l1_b_icmt_t_cache_ptr)[s_] = MOMENTUM * ((F16*)l1_b_icmt_t_cache_ptr)[s_] + ((((F16*)l1_out_data_ptr)[s_] - ((((unsigned int)(l1_y_real_ptr[0])) == s_) ? (F16)1 : (F16)0)));
        ((F16*)l1_dense_biases_ptr)[s_]  -= LR * ((F16*)l1_b_icmt_t_cache_ptr)[s_];
    }
}

void ot_update(void)
{
    if (ot_flag){
        //------------------------------------------------------------------//
        //                             l1 to l2                             //
        //------------------------------------------------------------------//
        AT_L2_EVENT _DmaR_Evt1, _DmaR_Evt2, *DmaR_Evt1 = &_DmaR_Evt1, *DmaR_Evt2 = &_DmaR_Evt2;

        /* copy dense weights, dense biases, out_data, y_real into l1 mem */
        AT_L2_COPY        (0, l2_dense_weights_ptr,  l1_dense_weights_ptr,  DENSE_WEIGHTS_SIZE_BYTES, 0, DmaR_Evt1);
        AT_L2_COPY_MERGED (0, l2_dense_biases_ptr,   l1_dense_biases_ptr,   DENSE_BIASES_SIZE_BYTES,  0, 0);
        AT_L2_COPY_MERGED (0, l2_out_data_ptr,       l1_out_data_ptr,       DENSE_OUTPUT_SIZE_BYTES,  0, 0);
        AT_L2_COPY_MERGED (0, l2_y_real_ptr,         l1_y_real_ptr,         sizeof(y_real),           0, 0);
        AT_L2_WAIT        (0, DmaR_Evt1);
        
        // /* allocate l1_mem for w_icmt_t_cahce, b_icmt_t_cache, dense_input */
        AT_L2_COPY        (0, l2_w_icmt_t_cache_ptr, l1_w_icmt_t_cache_ptr, DENSE_WEIGHTS_SIZE_BYTES, 0, DmaR_Evt2);
        AT_L2_COPY_MERGED (0, l2_b_icmt_t_cache_ptr, l1_b_icmt_t_cache_ptr, DENSE_BIASES_SIZE_BYTES,  0, 0);
        AT_L2_COPY_MERGED (0, l2_dense_input_ptr,    l1_dense_input_ptr,    DENSE_INPUT_SIZE_BYTES,   0, 0);
        AT_L2_WAIT        (0, DmaR_Evt2);


        //------------------------------------------------------------------//
        //                              update                              //
        //------------------------------------------------------------------//
        ot_update_core();

        //------------------------------------------------------------------//
        //                             l2 to l1                             //
        //------------------------------------------------------------------//
        AT_L2_EVENT _DmaW_Evt1, _DmaW_Evt1_, _DmaW_Evt2, _DmaW_Evt2_, *DmaW_Evt1 = &_DmaW_Evt1, *DmaW_Evt1_ = &_DmaW_Evt1_, *DmaW_Evt2 = &_DmaW_Evt2, *DmaW_Evt2_ = &_DmaW_Evt2_;

        // AT_L2_COPY        (0, l2_dense_weights_ptr,  l1_dense_weights_ptr,  DENSE_WEIGHTS_SIZE_BYTES, 1, DmaW_Evt1);
        // AT_L2_COPY_MERGED (0, l2_dense_biases_ptr,   l1_dense_biases_ptr,   DENSE_BIASES_SIZE_BYTES,  1, 0);
        // AT_L2_WAIT        (0, DmaW_Evt1);
        AT_L2_COPY        (0, l2_dense_weights_ptr,  l1_dense_weights_ptr,  DENSE_WEIGHTS_SIZE_BYTES, 1, DmaW_Evt1);
        AT_L2_WAIT        (0, DmaW_Evt1);
        AT_L2_COPY        (0, l2_dense_biases_ptr,   l1_dense_biases_ptr,   DENSE_BIASES_SIZE_BYTES,  1, DmaW_Evt1_);
        AT_L2_WAIT        (0, DmaW_Evt1_);

        AT_L2_COPY        (0, l2_w_icmt_t_cache_ptr, l1_w_icmt_t_cache_ptr, DENSE_WEIGHTS_SIZE_BYTES, 1, DmaW_Evt2);
        AT_L2_WAIT        (0, DmaW_Evt2);
        AT_L2_COPY        (0, l2_b_icmt_t_cache_ptr, l1_b_icmt_t_cache_ptr, DENSE_BIASES_SIZE_BYTES,  1, DmaW_Evt2_);
        AT_L2_WAIT        (0, DmaW_Evt2_);
    }
}


