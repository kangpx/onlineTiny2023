#ifndef __ONLINETRAINING_H__
#define __ONLINETRAINING_H__


#if defined(OT_QVAR)
#include "QvarKernels.h"
#define INPUT_DATA_SIZE          (9*40)
#define DENSE_INPUT_SIZE         (64*40)
#define DENSE_OUTPUT_SIZE        (10)
#define NUM_CHUNK                (1)
#define LR                       ((F16)0.002f)
#define MOMENTUM                 ((F16)0.5f)
#elif defined(OT_ULTRA)
#include "UltraKernels.h"
#define INPUT_DATA_SIZE          (45*19)
#define DENSE_INPUT_SIZE         (64*19)
#define DENSE_OUTPUT_SIZE        (8)
#define NUM_CHUNK                (1)
#define LR                       ((F16)0.002f)
#define MOMENTUM                 ((F16)0.5f)
#elif defined(OT_GYM)
#include "GymKernels.h"
#define INPUT_DATA_SIZE          (7*40)
#define DENSE_INPUT_SIZE         (64*40)
#define DENSE_OUTPUT_SIZE        (12)
#define NUM_CHUNK                (2)
#define LR                       ((F16)0.002f)
#define MOMENTUM                 ((F16)0.9f)
#endif
#define OT_ENABLE                (1)
#define OT_DISABLE               (0)
#define DATA_FORMAT              F16
#define INPUT_DATA_SIZE_BYTES    (INPUT_DATA_SIZE*sizeof(DATA_FORMAT))
#define DENSE_INPUT_SIZE_BYTES   (DENSE_INPUT_SIZE*sizeof(DATA_FORMAT))
#define DENSE_OUTPUT_SIZE_BYTES  (DENSE_OUTPUT_SIZE*sizeof(DATA_FORMAT))
#define DENSE_WEIGHTS_SIZE       (DENSE_INPUT_SIZE*DENSE_OUTPUT_SIZE)
#define DENSE_WEIGHTS_SIZE_BYTES (DENSE_WEIGHTS_SIZE*sizeof(DATA_FORMAT))
#define DENSE_BIASES_SIZE        (DENSE_OUTPUT_SIZE)
#define DENSE_BIASES_SIZE_BYTES  (DENSE_BIASES_SIZE*sizeof(DATA_FORMAT))

typedef struct{
    unsigned int       N;
    unsigned int       i_chunk;
}KerOtUpdate_fp16_T;

void ot_reset_icmt_t_cache(void);

int ot_init(void);

void ot_clean(void);

void ot_update_core(void);

void ot_update(void);

int ot_init_chunk(void);

void ot_clean_chunk(void);

void ot_update_core_chunk(unsigned int, unsigned int);

void ot_update_chunk(void);

void ot_update_chunk_parallel(void);

void KerParOtUpdate_fp16(KerOtUpdate_fp16_T *);

#endif
