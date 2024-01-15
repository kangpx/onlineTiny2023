/**
  ******************************************************************************
  * @file    combination_data.h
  * @author  AST Embedded Analytics Research Platform
  * @date    Thu Jan  4 15:06:25 2024
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */

#ifndef COMBINATION_DATA_H
#define COMBINATION_DATA_H
#pragma once

#include "combination_config.h"
#include "combination_data_params.h"

AI_DEPRECATED
#define AI_COMBINATION_DATA_ACTIVATIONS(ptr_)  \
  ai_combination_data_activations_buffer_get(AI_HANDLE_PTR(ptr_))

AI_DEPRECATED
#define AI_COMBINATION_DATA_WEIGHTS(ptr_)  \
  ai_combination_data_weights_buffer_get(AI_HANDLE_PTR(ptr_))


AI_API_DECLARE_BEGIN


extern const ai_u64 s_combination_input_36_bias_array_u64[16];
extern const ai_u64 s_combination_input_44_weights_array_u64[1536];
extern const ai_u64 s_combination_input_44_bias_array_u64[16];
extern const ai_u64 s_combination_onnxAdd_127_weights_array_u64[1536];
extern const ai_u64 s_combination_onnxAdd_127_bias_array_u64[16];
extern const ai_u64 s_combination_input_60_weights_array_u64[1536];
extern const ai_u64 s_combination_input_60_bias_array_u64[16];
extern const ai_u64 s_combination_input_68_weights_array_u64[1536];
extern const ai_u64 s_combination_input_68_bias_array_u64[16];
extern const ai_u64 s_combination_onnxAdd_136_weights_array_u64[1536];
extern const ai_u64 s_combination_onnxAdd_136_bias_array_u64[16];
extern const ai_u64 s_combination_input_80_weights_array_u64[6400];
extern const ai_u64 s_combination_input_80_bias_array_u64[5];
extern const ai_u64 s_combination_input_4_weights_array_u64[432];
extern const ai_u64 s_combination_input_4_bias_array_u64[16];
extern const ai_u64 s_combination_input_12_weights_array_u64[1536];
extern const ai_u64 s_combination_input_12_bias_array_u64[16];
extern const ai_u64 s_combination_input_20_weights_array_u64[1536];
extern const ai_u64 s_combination_input_20_bias_array_u64[16];
extern const ai_u64 s_combination_onnxAdd_118_weights_array_u64[1536];
extern const ai_u64 s_combination_onnxAdd_118_bias_array_u64[16];
extern const ai_u64 s_combination_input_36_weights_array_u64[1536];



/*!
 * @brief Get network activations buffer initialized struct.
 * @ingroup combination_data
 * @param[in] ptr a pointer to the activations array storage area
 * @return an ai_buffer initialized struct
 */
AI_DEPRECATED
AI_API_ENTRY
ai_buffer ai_combination_data_activations_buffer_get(const ai_handle ptr);

/*!
 * @brief Get network weights buffer initialized struct.
 * @ingroup combination_data
 * @param[in] ptr a pointer to the weights array storage area
 * @return an ai_buffer initialized struct
 */
AI_DEPRECATED
AI_API_ENTRY
ai_buffer ai_combination_data_weights_buffer_get(const ai_handle ptr);

/*!
 * @brief Get network weights array pointer as a handle ptr.
 * @ingroup combination_data
 * @return a ai_handle pointer to the weights array
 */
AI_DEPRECATED
AI_API_ENTRY
ai_handle ai_combination_data_weights_get(void);


/*!
 * @brief Get network params configuration data structure.
 * @ingroup combination_data
 * @return true if a valid configuration is present, false otherwise
 */
AI_API_ENTRY
ai_bool ai_combination_data_params_get(ai_network_params* params);


AI_API_DECLARE_END

#endif /* COMBINATION_DATA_H */

