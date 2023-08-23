/*
 * online_learning.c
 *
 *  Created on: Aug 18, 2023
 *      Author: kangpx
 */

#include "online_training.h"

extern ai_handle combination;
extern float *out_data;
extern float y_real;
u_observer_ctx i_u_observer_ctx;
AI_ALIGNED(32) float in_dense[OT_CLASSIFIER_IN_SIZE];
AI_ALIGNED(4) uint8_t ot_wb_cache[OT_CLASSIFIER_DATA_WEIGHT_SIZE_BYTES + OT_CLASSIFIER_DATA_BIAS_SIZE_BYTES];
AI_ALIGNED(4) uint8_t ot_wb_icmt_t_cache[OT_CLASSIFIER_DATA_WEIGHT_SIZE_BYTES + OT_CLASSIFIER_DATA_BIAS_SIZE_BYTES];
float ot_lr;
float ot_momentum;

void ot_cache_weights(void){
	ai_observer_node node_info;
	node_info.c_idx = OT_CLASSIFIER_C_ID; /* index of the critical node */
	if (ai_platform_observer_node_info(combination, &node_info)) {
		ai_tensor_list *tl;
		tl = GET_TENSOR_LIST_WEIGTHS(node_info.tensors);
		uintptr_t dst_addr = (uintptr_t) &ot_wb_cache[0];
		AI_FOR_EACH_TENSOR_LIST_DO(i, t, tl){
			// Retrieve the @/size of the data
			const uintptr_t src_addr = (uintptr_t) AI_TENSOR_ARRAY_GET_DATA_ADDR(t);
			const ai_size sz = AI_TENSOR_ARRAY_BYTE_SIZE(t);
			// Copy the data tensor in the SW cache
			memcpy(dst_addr, src_addr, sz);
			// set the new effective address
			AI_TENSOR_ARRAY_UPDATE_DATA_ADDR(t, dst_addr);
			dst_addr += OT_ALIGN_UP(sz, 4);
		}
	}
}

ai_observer_node_cb ot_observer_cb(const ai_handle cookie, const ai_u32 flags, const ai_observer_node *node) {
	ai_tensor_list *tl;
	ai_observer_node node_info;
	node_info.c_idx = OT_PRE_CLASSIFIER_C_ID;
	if (node->c_idx == OT_PRE_CLASSIFIER_C_ID) {
		ai_platform_observer_node_info(combination, &node_info);
		tl = GET_TENSOR_LIST_OUT(node_info.tensors);
		AI_FOR_EACH_TENSOR_LIST_DO(i, t, tl){
			float *tmp = (float*) AI_TENSOR_ARRAY_GET_DATA_ADDR(t);
			for (uint32_t k = 0; k < OT_CLASSIFIER_IN_SIZE; k++)
				((float*) in_dense)[k] = tmp[k];
		}
	}
	return 0;
}

void ot_init(float ot_lr_, float ot_momentum_){
	// load the weights of classifier into software cache
	ot_cache_weights();
	// register call-back for observer
	ai_platform_observer_register(combination, ot_observer_cb, &i_u_observer_ctx, AI_OBSERVER_POST_EVT);
	// reset the ot_icmt_t_cache to all zeros
	ot_reset_icmt_t_cache();
	// set the learning rate and momentum
	ot_lr = ot_lr_;
	ot_momentum = ot_momentum_;
}

void ot_update_w(uint32_t s_, uint32_t t_) {
	uint32_t w_idx = s_ * OT_CLASSIFIER_IN_SIZE + t_;
	((float*) ot_wb_icmt_t_cache)[w_idx] = ot_momentum * ((float*) ot_wb_icmt_t_cache)[w_idx] + OT_W_GRADIENT(s_, t_);
	((float*) ot_wb_cache)[w_idx] -= ot_lr * ((float*) ot_wb_icmt_t_cache)[w_idx];
}

void ot_update_b(uint32_t s_) {
	uint32_t b_idx = OT_CLASSIFIER_DATA_WEIGHT_SIZE + s_;
	((float*) ot_wb_icmt_t_cache)[b_idx] = ot_momentum * ((float*) ot_wb_icmt_t_cache)[b_idx] + OT_B_GRADIENT(s_);
	((float*) ot_wb_cache)[b_idx] -= ot_lr * ((float*) ot_wb_icmt_t_cache)[b_idx];
}

void ot_update(void) {
	for (uint32_t s_ = 0; s_ < OT_CLASSIFIER_OUT_SIZE; s_++) {
		for (uint32_t t_ = 0; t_ < OT_CLASSIFIER_IN_SIZE; t_++){
			ot_update_w(s_, t_);
		}
		ot_update_b(s_);
	}
}

void ot_reset_icmt_t_cache(void) {
	memset(ot_wb_icmt_t_cache, 0, sizeof(ot_wb_icmt_t_cache));
}
