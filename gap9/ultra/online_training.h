#ifndef __ONLINETRAINING_H__
#define __ONLINETRAINING_H__

#include "UltraKernels.h"

#define OT_ENABLE                (1)
#define OT_DISABLE               (0)
#define DATA_FORMAT              F16
#define INPUT_DATA_SIZE          (45*19*1)
#define INPUT_DATA_SIZE_BYTES    (INPUT_DATA_SIZE*sizeof(DATA_FORMAT))
#define DENSE_INPUT_SIZE         (64*19)
#define DENSE_INPUT_SIZE_BYTES   (DENSE_INPUT_SIZE*sizeof(DATA_FORMAT))
#define DENSE_OUTPUT_SIZE        (8)
#define DENSE_OUTPUT_SIZE_BYTES  (DENSE_OUTPUT_SIZE*sizeof(DATA_FORMAT))
#define DENSE_WEIGHTS_SIZE       (DENSE_INPUT_SIZE*DENSE_OUTPUT_SIZE)
#define DENSE_WEIGHTS_SIZE_BYTES (DENSE_WEIGHTS_SIZE*sizeof(DATA_FORMAT))
#define DENSE_BIASES_SIZE        (DENSE_OUTPUT_SIZE)
#define DENSE_BIASES_SIZE_BYTES  (DENSE_BIASES_SIZE*sizeof(DATA_FORMAT))
#define LR                       ((F16)0.002)
#define MOMENTUM                 ((F16)0.5)

void ot_reset_icmt_t_cache(void);

void ot_init(void);

void ot_clean(void);

void ot_retrieve_dense_input(AT_L2_INT_ADDR_TYPE l1_mem_src_ptr);

void ot_update_core(void);

void ot_update(void);

#endif
