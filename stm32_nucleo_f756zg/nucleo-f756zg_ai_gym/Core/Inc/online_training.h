/*
 * online_learning.h
 *
 *  Created on: Aug 18, 2023
 *      Author: kangpx
 */

#ifndef INC_ONLINE_TRAINING_H_
#define INC_ONLINE_TRAINING_H_

#include <string.h>
#include "ai_platform.h"
#include "ai_platform_interface.h"
#include "core_common.h"
#include "core_private.h"

typedef struct u_observer_ctx {
	uint64_t ts;
	uint32_t n_events;
} u_observer_ctx;


#define OT_CLASSIFIER_IN_SIZE (32*40)
#define OT_CLASSIFIER_OUT_SIZE (12)
#define OT_CLASSIFIER_IN_SIZE_BYTES (OT_CLASSIFIER_IN_SIZE*4)
#define OT_CLASSIFIER_OUT_SIZE_BYTES (OT_CLASSIFIER_OUT_SIZE*4)
#define OT_PRE_CLASSIFIER_C_ID (22)
#define OT_CLASSIFIER_C_ID (23)
#define OT_CLASSIFIER_DATA_WEIGHT_SIZE (OT_CLASSIFIER_IN_SIZE*OT_CLASSIFIER_OUT_SIZE)
#define OT_CLASSIFIER_DATA_BIAS_SIZE (OT_CLASSIFIER_OUT_SIZE)
#define OT_CLASSIFIER_DATA_WEIGHT_SIZE_BYTES (OT_CLASSIFIER_DATA_WEIGHT_SIZE*4)
#define OT_CLASSIFIER_DATA_BIAS_SIZE_BYTES (OT_CLASSIFIER_DATA_BIAS_SIZE*4)

#define OT_ALIGN_UP(num, align) (((num) + ((align) - 1)) & ~((align) - 1))
#define OT_W_GRADIENT(s_,t_) (((float*)in_dense)[t_] * (((float*)out_data)[s_] - ((((uint32_t)y_real) == s_) ? 1.0f : 0.0f)))
#define OT_B_GRADIENT(s_)  (((float*)out_data)[s_] - ((((uint32_t)y_real) == s_) ? 1.0f : 0.0f))

/*
 * @brief cache the weights/biases of classifier into software cache
*/
void ot_cache_weights(void);

/*
 * @brief callback function to retrieve the input to classifier
*/
ai_observer_node_cb ot_observer_cb(const ai_handle, const ai_u32, const ai_observer_node*);

/*
 * @brief cache the weights of classifier to software cache and register the observer callback
*/
void ot_init(float ot_lr_, float ot_momentum_);

/*
 * @brief update the value of the t_th weight in the s_th group
 * @param s_: the group index of the weight whose value is to be updated
 * @param t_: the within group index of the weight whose value is to be updated
 */
void ot_update_w(uint32_t s_, uint32_t t_);

/*
 * @brief update the value of the s-th bias
 * @param s_: the index of the bias whose value is to be updated
 */
void ot_update_b(uint32_t s_);

/*
 * @brief update the weights & biases
 */
void ot_update(void);

/*
 * @brief reset _wb_icmt_t_cache
 */
void ot_reset_icmt_t_cache(void);

#endif /* INC_ONLINE_TRAINING_H_ */

