#ifndef __ONLINETRAINING_H__
#define __ONLINETRAINING_H__


#if defined(OT_QVAR)
#include "QvarKernels.h"
#define IN_C                     (9)
#define IN_W                     (40)
#define BOUT_C                   (32)
#define BOUT_W                   (40)
#define INPUT_DATA_SIZE          (IN_C*IN_W)
#define DENSE_INPUT_SIZE         (BOUT_C*BOUT_W)
#define DENSE_OUTPUT_SIZE        (10)
#define NUM_CHUNK                (1)
#define SGD                      (0)
#define ADAM                     (1)
#define OPTIMIZER                SGD
#if (OPTIMIZER==SGD)
#define LR                       ((F16)0.002f)
#define MOMENTUM                 ((F16)0.5f)
#elif (OPTIMIZER==ADAM)
#define LR                       ((F16)0.001f)
#define BETA1                    ((F16)0.9f)
#define BETA2                    ((F16)0.99f)
#define EPS                      ((F16)0.00000001f)
#endif

#elif defined(OT_ULTRA)
#include "UltraKernels.h"
#define IN_C                     (45)
#define IN_W                     (19)
#define BOUT_C                   (32)
#define BOUT_W                   (19)
#define INPUT_DATA_SIZE          (IN_C*IN_W)
#define DENSE_INPUT_SIZE         (BOUT_C*BOUT_W)
#define DENSE_OUTPUT_SIZE        (8)
#define NUM_CHUNK                (1)
#define SGD                      (0)
#define ADAM                     (1)
#define OPTIMIZER                SGD 
#if (OPTIMIZER==SGD)
#define LR                       ((F16)0.002f)
#define MOMENTUM                 ((F16)0.5f)
#elif (OPTIMIZER==ADAM)
#define LR                       ((F16)0.002f)
#define BETA1                    ((F16)0.9f)
#define BETA2                    ((F16)0.99f)
#define EPS                      ((F16)0.00000001f)
#endif

#elif defined(OT_GYM)
#include "GymKernels.h"
#define IN_C                     (7)
#define IN_W                     (40)
#define BOUT_C                   (32)
#define BOUT_W                   (40)
#define INPUT_DATA_SIZE          (IN_C*IN_W)
#define DENSE_INPUT_SIZE         (BOUT_C*BOUT_W)
#define DENSE_OUTPUT_SIZE        (12)
#define NUM_CHUNK                (1)
#define SGD                      (0)
#define ADAM                     (1)
#define OPTIMIZER                SGD
#if (OPTIMIZER==SGD)
#define LR                       ((F16)0.002f)
#define MOMENTUM                 ((F16)0.9f)
#elif (OPTIMIZER==ADAM)
#define LR                       ((F16)0.002f)
#define BETA1                    ((F16)0.9f)
#define BETA2                    ((F16)0.99f)
#define EPS                      ((F16)0.00000001f)
#endif
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
    unsigned int * __restrict__  y_ptr;
    F16 *__restrict__ w_ptr;
    F16 *__restrict__ b_ptr;
    F16 *__restrict__ i_ptr;
    F16 *__restrict__ o_ptr;
#if (OPTIMIZER == SGD)
    F16 *__restrict__ w_icmt_ptr;
    F16 *__restrict__ b_icmt_ptr;
#elif (OPTIMIZER == ADAM)
    F16 *__restrict__ w_m_icmt_ptr;
    F16 *__restrict__ w_v_icmt_ptr;
    F16 *__restrict__ b_m_icmt_ptr;
    F16 *__restrict__ b_v_icmt_ptr;
#endif
}KerOtUpdate_fp16_T;

void ot_reset_icmt_t_cache(void);

int ot_init_chunk(void);

void ot_clean_chunk(void);

void ot_update_chunk_parallel(void);

void KerParOtUpdate_fp16(KerOtUpdate_fp16_T *);

#endif
