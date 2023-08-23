/**
  ******************************************************************************
  * @file    combination_data.c
  * @author  AST Embedded Analytics Research Platform
  * @date    Wed Aug 23 14:12:33 2023
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */
#include "combination_data.h"
#include "ai_platform_interface.h"

AI_API_DECLARE_BEGIN
ai_buffer g_combination_data_map_activations[AI_COMBINATION_DATA_ACTIVATIONS_COUNT] = {
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 22016, 1, 1),
    22016, NULL, NULL),    /* heap_overlay_pool */
  };
ai_buffer g_combination_data_map_weights[AI_COMBINATION_DATA_WEIGHTS_COUNT] = {
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 256, 1, 1),
    256, NULL, s_combination_input_4_bias_array_u64),   /* input_4_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 49152, 1, 1),
    49152, NULL, s_combination_input_12_weights_array_u64),   /* input_12_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 256, 1, 1),
    256, NULL, s_combination_input_12_bias_array_u64),   /* input_12_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 49152, 1, 1),
    49152, NULL, s_combination_input_20_weights_array_u64),   /* input_20_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 256, 1, 1),
    256, NULL, s_combination_input_20_bias_array_u64),   /* input_20_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 49152, 1, 1),
    49152, NULL, s_combination_onnxAdd_127_weights_array_u64),   /* onnxAdd_127_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 256, 1, 1),
    256, NULL, s_combination_onnxAdd_127_bias_array_u64),   /* onnxAdd_127_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 49152, 1, 1),
    49152, NULL, s_combination_input_36_weights_array_u64),   /* input_36_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 256, 1, 1),
    256, NULL, s_combination_input_36_bias_array_u64),   /* input_36_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 49152, 1, 1),
    49152, NULL, s_combination_input_44_weights_array_u64),   /* input_44_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 256, 1, 1),
    256, NULL, s_combination_input_44_bias_array_u64),   /* input_44_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 49152, 1, 1),
    49152, NULL, s_combination_onnxAdd_136_weights_array_u64),   /* onnxAdd_136_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 256, 1, 1),
    256, NULL, s_combination_onnxAdd_136_bias_array_u64),   /* onnxAdd_136_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 49152, 1, 1),
    49152, NULL, s_combination_input_60_weights_array_u64),   /* input_60_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 256, 1, 1),
    256, NULL, s_combination_input_60_bias_array_u64),   /* input_60_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 49152, 1, 1),
    49152, NULL, s_combination_input_68_weights_array_u64),   /* input_68_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 256, 1, 1),
    256, NULL, s_combination_input_68_bias_array_u64),   /* input_68_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 49152, 1, 1),
    49152, NULL, s_combination_onnxAdd_145_weights_array_u64),   /* onnxAdd_145_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 256, 1, 1),
    256, NULL, s_combination_onnxAdd_145_bias_array_u64),   /* onnxAdd_145_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 102400, 1, 1),
    102400, NULL, s_combination_input_80_weights_array_u64),   /* input_80_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 40, 1, 1),
    40, NULL, s_combination_input_80_bias_array_u64),   /* input_80_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 6912, 1, 1),
    6912, NULL, s_combination_input_4_weights_array_u64),   /* input_4_weights_array */
  };


/*!
 * @brief Get network activations buffer initialized struct.
 * @ingroup combination_data
 * @param[in] ptr a pointer to the activations array storage area
 * @return an ai_buffer initialized struct
 */
AI_DEPRECATED
AI_API_ENTRY
ai_buffer ai_combination_data_activations_buffer_get(const ai_handle ptr)
{
  ai_buffer buf = AI_BUFFER_INIT(
    AI_FLAG_NONE, AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, AI_COMBINATION_DATA_ACTIVATIONS_SIZE, 1, AI_COMBINATION_DATA_ACTIVATIONS_COUNT),
    AI_COMBINATION_DATA_ACTIVATIONS_SIZE,
    NULL, ptr);
  return buf;
}

/*!
 * @brief Get network weights buffer initialized struct.
 * @ingroup combination_data
 * @param[in] ptr a pointer to the weights array storage area
 * @return an ai_buffer initialized struct
 */
AI_DEPRECATED
AI_API_ENTRY
ai_buffer ai_combination_data_weights_buffer_get(const ai_handle ptr)
{
  ai_buffer buf = AI_BUFFER_INIT(
    AI_FLAG_NONE, AI_BUFFER_FORMAT_U8|AI_BUFFER_FMT_FLAG_CONST,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, AI_COMBINATION_DATA_WEIGHTS_SIZE, 1, AI_COMBINATION_DATA_WEIGHTS_COUNT),
    AI_COMBINATION_DATA_WEIGHTS_SIZE,
    NULL, ptr);
  return buf;
}


/*!
 * @brief Get network weights array pointer as a handle ptr.
 * @ingroup combination_data
 * @return a ai_handle pointer to the weights array
 */
AI_DEPRECATED
AI_API_ENTRY
ai_handle ai_combination_data_weights_get(void)
{
  return AI_HANDLE_PTR(g_combination_weights_table);

}


/*!
 * @brief Get network params configuration data structure.
 * @ingroup combination_data
 * @return true if a valid configuration is present, false otherwise
 */
AI_API_ENTRY
ai_bool ai_combination_data_params_get(ai_network_params* params)
{
  if (!params) return false;
  
  const ai_buffer_array map_activations = 
    AI_BUFFER_ARRAY_OBJ_INIT(AI_FLAG_NONE, AI_COMBINATION_DATA_ACTIVATIONS_COUNT, g_combination_data_map_activations);
  
  const ai_buffer_array map_weights = 
    AI_BUFFER_ARRAY_OBJ_INIT(AI_FLAG_NONE, AI_COMBINATION_DATA_WEIGHTS_COUNT, g_combination_data_map_weights);

  return ai_platform_bind_network_params(params, &map_weights, &map_activations);
}


AI_API_DECLARE_END
