/**
  ******************************************************************************
  * @file    combination.c
  * @author  AST Embedded Analytics Research Platform
  * @date    Wed Aug 23 19:26:33 2023
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


#include "combination.h"
#include "combination_data.h"

#include "ai_platform.h"
#include "ai_platform_interface.h"
#include "ai_math_helpers.h"

#include "core_common.h"
#include "core_convert.h"

#include "layers.h"



#undef AI_NET_OBJ_INSTANCE
#define AI_NET_OBJ_INSTANCE g_combination
 
#undef AI_COMBINATION_MODEL_SIGNATURE
#define AI_COMBINATION_MODEL_SIGNATURE     "a5b7797c08ba0ee11336b34b05b16124"

#ifndef AI_TOOLS_REVISION_ID
#define AI_TOOLS_REVISION_ID     ""
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME   "Wed Aug 23 19:26:33 2023"

#undef AI_TOOLS_COMPILE_TIME
#define AI_TOOLS_COMPILE_TIME    __DATE__ " " __TIME__

#undef AI_COMBINATION_N_BATCHES
#define AI_COMBINATION_N_BATCHES         (1)

static ai_ptr g_combination_activations_map[1] = AI_C_ARRAY_INIT;
static ai_ptr g_combination_weights_map[22] = AI_C_ARRAY_INIT;



/**  Array declarations section  **********************************************/
/* Array#0 */
AI_ARRAY_OBJ_DECLARE(
  input_4_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)
/* Array#1 */
AI_ARRAY_OBJ_DECLARE(
  input_12_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12288, AI_STATIC)
/* Array#2 */
AI_ARRAY_OBJ_DECLARE(
  input_12_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)
/* Array#3 */
AI_ARRAY_OBJ_DECLARE(
  input_20_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12288, AI_STATIC)
/* Array#4 */
AI_ARRAY_OBJ_DECLARE(
  input_20_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)
/* Array#5 */
AI_ARRAY_OBJ_DECLARE(
  onnxAdd_127_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12288, AI_STATIC)
/* Array#6 */
AI_ARRAY_OBJ_DECLARE(
  onnxAdd_127_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)
/* Array#7 */
AI_ARRAY_OBJ_DECLARE(
  input_36_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12288, AI_STATIC)
/* Array#8 */
AI_ARRAY_OBJ_DECLARE(
  input_36_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)
/* Array#9 */
AI_ARRAY_OBJ_DECLARE(
  input_44_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12288, AI_STATIC)
/* Array#10 */
AI_ARRAY_OBJ_DECLARE(
  input_44_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)
/* Array#11 */
AI_ARRAY_OBJ_DECLARE(
  onnxAdd_136_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12288, AI_STATIC)
/* Array#12 */
AI_ARRAY_OBJ_DECLARE(
  onnxAdd_136_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)
/* Array#13 */
AI_ARRAY_OBJ_DECLARE(
  input_60_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12288, AI_STATIC)
/* Array#14 */
AI_ARRAY_OBJ_DECLARE(
  input_60_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)
/* Array#15 */
AI_ARRAY_OBJ_DECLARE(
  input_68_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12288, AI_STATIC)
/* Array#16 */
AI_ARRAY_OBJ_DECLARE(
  input_68_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)
/* Array#17 */
AI_ARRAY_OBJ_DECLARE(
  onnxAdd_145_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12288, AI_STATIC)
/* Array#18 */
AI_ARRAY_OBJ_DECLARE(
  onnxAdd_145_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)
/* Array#19 */
AI_ARRAY_OBJ_DECLARE(
  input_80_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 30720, AI_STATIC)
/* Array#20 */
AI_ARRAY_OBJ_DECLARE(
  input_80_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12, AI_STATIC)
/* Array#21 */
AI_ARRAY_OBJ_DECLARE(
  modelInput_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 280, AI_STATIC)
/* Array#22 */
AI_ARRAY_OBJ_DECLARE(
  input_4_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2560, AI_STATIC)
/* Array#23 */
AI_ARRAY_OBJ_DECLARE(
  onnxConv_75_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2560, AI_STATIC)
/* Array#24 */
AI_ARRAY_OBJ_DECLARE(
  input_12_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2560, AI_STATIC)
/* Array#25 */
AI_ARRAY_OBJ_DECLARE(
  onnxConv_78_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2560, AI_STATIC)
/* Array#26 */
AI_ARRAY_OBJ_DECLARE(
  input_20_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2560, AI_STATIC)
/* Array#27 */
AI_ARRAY_OBJ_DECLARE(
  onnxConv_81_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2560, AI_STATIC)
/* Array#28 */
AI_ARRAY_OBJ_DECLARE(
  onnxAdd_127_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2560, AI_STATIC)
/* Array#29 */
AI_ARRAY_OBJ_DECLARE(
  onnxRelu_84_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2560, AI_STATIC)
/* Array#30 */
AI_ARRAY_OBJ_DECLARE(
  input_28_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2560, AI_STATIC)
/* Array#31 */
AI_ARRAY_OBJ_DECLARE(
  input_36_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2560, AI_STATIC)
/* Array#32 */
AI_ARRAY_OBJ_DECLARE(
  onnxConv_88_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2560, AI_STATIC)
/* Array#33 */
AI_ARRAY_OBJ_DECLARE(
  input_44_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2560, AI_STATIC)
/* Array#34 */
AI_ARRAY_OBJ_DECLARE(
  onnxConv_91_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2560, AI_STATIC)
/* Array#35 */
AI_ARRAY_OBJ_DECLARE(
  onnxAdd_136_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2560, AI_STATIC)
/* Array#36 */
AI_ARRAY_OBJ_DECLARE(
  onnxRelu_94_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2560, AI_STATIC)
/* Array#37 */
AI_ARRAY_OBJ_DECLARE(
  input_52_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2560, AI_STATIC)
/* Array#38 */
AI_ARRAY_OBJ_DECLARE(
  input_60_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2560, AI_STATIC)
/* Array#39 */
AI_ARRAY_OBJ_DECLARE(
  onnxConv_98_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2560, AI_STATIC)
/* Array#40 */
AI_ARRAY_OBJ_DECLARE(
  input_68_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2560, AI_STATIC)
/* Array#41 */
AI_ARRAY_OBJ_DECLARE(
  onnxConv_101_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2560, AI_STATIC)
/* Array#42 */
AI_ARRAY_OBJ_DECLARE(
  onnxAdd_145_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2560, AI_STATIC)
/* Array#43 */
AI_ARRAY_OBJ_DECLARE(
  onnxRelu_104_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2560, AI_STATIC)
/* Array#44 */
AI_ARRAY_OBJ_DECLARE(
  input_76_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2560, AI_STATIC)
/* Array#45 */
AI_ARRAY_OBJ_DECLARE(
  input_80_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12, AI_STATIC)
/* Array#46 */
AI_ARRAY_OBJ_DECLARE(
  modelOutput_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 12, AI_STATIC)
/* Array#47 */
AI_ARRAY_OBJ_DECLARE(
  input_4_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1344, AI_STATIC)
/**  Tensor declarations section  *********************************************/
/* Tensor #0 */
AI_TENSOR_OBJ_DECLARE(
  input_4_bias, AI_STATIC,
  0, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &input_4_bias_array, NULL)

/* Tensor #1 */
AI_TENSOR_OBJ_DECLARE(
  input_12_weights, AI_STATIC,
  1, 0x0,
  AI_SHAPE_INIT(4, 64, 1, 3, 64), AI_STRIDE_INIT(4, 4, 256, 16384, 16384),
  1, &input_12_weights_array, NULL)

/* Tensor #2 */
AI_TENSOR_OBJ_DECLARE(
  input_12_bias, AI_STATIC,
  2, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &input_12_bias_array, NULL)

/* Tensor #3 */
AI_TENSOR_OBJ_DECLARE(
  input_20_weights, AI_STATIC,
  3, 0x0,
  AI_SHAPE_INIT(4, 64, 1, 3, 64), AI_STRIDE_INIT(4, 4, 256, 16384, 16384),
  1, &input_20_weights_array, NULL)

/* Tensor #4 */
AI_TENSOR_OBJ_DECLARE(
  input_20_bias, AI_STATIC,
  4, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &input_20_bias_array, NULL)

/* Tensor #5 */
AI_TENSOR_OBJ_DECLARE(
  onnxAdd_127_weights, AI_STATIC,
  5, 0x0,
  AI_SHAPE_INIT(4, 64, 1, 3, 64), AI_STRIDE_INIT(4, 4, 256, 16384, 16384),
  1, &onnxAdd_127_weights_array, NULL)

/* Tensor #6 */
AI_TENSOR_OBJ_DECLARE(
  onnxAdd_127_bias, AI_STATIC,
  6, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &onnxAdd_127_bias_array, NULL)

/* Tensor #7 */
AI_TENSOR_OBJ_DECLARE(
  input_36_weights, AI_STATIC,
  7, 0x0,
  AI_SHAPE_INIT(4, 64, 1, 3, 64), AI_STRIDE_INIT(4, 4, 256, 16384, 16384),
  1, &input_36_weights_array, NULL)

/* Tensor #8 */
AI_TENSOR_OBJ_DECLARE(
  input_36_bias, AI_STATIC,
  8, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &input_36_bias_array, NULL)

/* Tensor #9 */
AI_TENSOR_OBJ_DECLARE(
  input_44_weights, AI_STATIC,
  9, 0x0,
  AI_SHAPE_INIT(4, 64, 1, 3, 64), AI_STRIDE_INIT(4, 4, 256, 16384, 16384),
  1, &input_44_weights_array, NULL)

/* Tensor #10 */
AI_TENSOR_OBJ_DECLARE(
  input_44_bias, AI_STATIC,
  10, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &input_44_bias_array, NULL)

/* Tensor #11 */
AI_TENSOR_OBJ_DECLARE(
  onnxAdd_136_weights, AI_STATIC,
  11, 0x0,
  AI_SHAPE_INIT(4, 64, 1, 3, 64), AI_STRIDE_INIT(4, 4, 256, 16384, 16384),
  1, &onnxAdd_136_weights_array, NULL)

/* Tensor #12 */
AI_TENSOR_OBJ_DECLARE(
  onnxAdd_136_bias, AI_STATIC,
  12, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &onnxAdd_136_bias_array, NULL)

/* Tensor #13 */
AI_TENSOR_OBJ_DECLARE(
  input_60_weights, AI_STATIC,
  13, 0x0,
  AI_SHAPE_INIT(4, 64, 1, 3, 64), AI_STRIDE_INIT(4, 4, 256, 16384, 16384),
  1, &input_60_weights_array, NULL)

/* Tensor #14 */
AI_TENSOR_OBJ_DECLARE(
  input_60_bias, AI_STATIC,
  14, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &input_60_bias_array, NULL)

/* Tensor #15 */
AI_TENSOR_OBJ_DECLARE(
  input_68_weights, AI_STATIC,
  15, 0x0,
  AI_SHAPE_INIT(4, 64, 1, 3, 64), AI_STRIDE_INIT(4, 4, 256, 16384, 16384),
  1, &input_68_weights_array, NULL)

/* Tensor #16 */
AI_TENSOR_OBJ_DECLARE(
  input_68_bias, AI_STATIC,
  16, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &input_68_bias_array, NULL)

/* Tensor #17 */
AI_TENSOR_OBJ_DECLARE(
  onnxAdd_145_weights, AI_STATIC,
  17, 0x0,
  AI_SHAPE_INIT(4, 64, 1, 3, 64), AI_STRIDE_INIT(4, 4, 256, 16384, 16384),
  1, &onnxAdd_145_weights_array, NULL)

/* Tensor #18 */
AI_TENSOR_OBJ_DECLARE(
  onnxAdd_145_bias, AI_STATIC,
  18, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &onnxAdd_145_bias_array, NULL)

/* Tensor #19 */
AI_TENSOR_OBJ_DECLARE(
  input_80_weights, AI_STATIC,
  19, 0x0,
  AI_SHAPE_INIT(4, 2560, 12, 1, 1), AI_STRIDE_INIT(4, 4, 10240, 122880, 122880),
  1, &input_80_weights_array, NULL)

/* Tensor #20 */
AI_TENSOR_OBJ_DECLARE(
  input_80_bias, AI_STATIC,
  20, 0x0,
  AI_SHAPE_INIT(4, 1, 12, 1, 1), AI_STRIDE_INIT(4, 4, 4, 48, 48),
  1, &input_80_bias_array, NULL)

/* Tensor #21 */
AI_TENSOR_OBJ_DECLARE(
  modelInput_output, AI_STATIC,
  21, 0x0,
  AI_SHAPE_INIT(4, 1, 7, 1, 40), AI_STRIDE_INIT(4, 4, 4, 28, 28),
  1, &modelInput_output_array, NULL)

/* Tensor #22 */
AI_TENSOR_OBJ_DECLARE(
  input_4_output, AI_STATIC,
  22, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 40), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &input_4_output_array, NULL)

/* Tensor #23 */
AI_TENSOR_OBJ_DECLARE(
  onnxConv_75_output, AI_STATIC,
  23, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 40), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &onnxConv_75_output_array, NULL)

/* Tensor #24 */
AI_TENSOR_OBJ_DECLARE(
  input_12_output, AI_STATIC,
  24, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 40), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &input_12_output_array, NULL)

/* Tensor #25 */
AI_TENSOR_OBJ_DECLARE(
  onnxConv_78_output, AI_STATIC,
  25, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 40), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &onnxConv_78_output_array, NULL)

/* Tensor #26 */
AI_TENSOR_OBJ_DECLARE(
  input_20_output, AI_STATIC,
  26, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 40), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &input_20_output_array, NULL)

/* Tensor #27 */
AI_TENSOR_OBJ_DECLARE(
  onnxConv_81_output, AI_STATIC,
  27, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 40), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &onnxConv_81_output_array, NULL)

/* Tensor #28 */
AI_TENSOR_OBJ_DECLARE(
  onnxAdd_127_output, AI_STATIC,
  28, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 40), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &onnxAdd_127_output_array, NULL)

/* Tensor #29 */
AI_TENSOR_OBJ_DECLARE(
  onnxRelu_84_output, AI_STATIC,
  29, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 40), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &onnxRelu_84_output_array, NULL)

/* Tensor #30 */
AI_TENSOR_OBJ_DECLARE(
  input_28_output, AI_STATIC,
  30, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 40), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &input_28_output_array, NULL)

/* Tensor #31 */
AI_TENSOR_OBJ_DECLARE(
  input_36_output, AI_STATIC,
  31, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 40), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &input_36_output_array, NULL)

/* Tensor #32 */
AI_TENSOR_OBJ_DECLARE(
  onnxConv_88_output, AI_STATIC,
  32, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 40), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &onnxConv_88_output_array, NULL)

/* Tensor #33 */
AI_TENSOR_OBJ_DECLARE(
  input_44_output, AI_STATIC,
  33, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 40), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &input_44_output_array, NULL)

/* Tensor #34 */
AI_TENSOR_OBJ_DECLARE(
  onnxConv_91_output, AI_STATIC,
  34, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 40), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &onnxConv_91_output_array, NULL)

/* Tensor #35 */
AI_TENSOR_OBJ_DECLARE(
  onnxAdd_136_output, AI_STATIC,
  35, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 40), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &onnxAdd_136_output_array, NULL)

/* Tensor #36 */
AI_TENSOR_OBJ_DECLARE(
  onnxRelu_94_output, AI_STATIC,
  36, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 40), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &onnxRelu_94_output_array, NULL)

/* Tensor #37 */
AI_TENSOR_OBJ_DECLARE(
  input_52_output, AI_STATIC,
  37, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 40), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &input_52_output_array, NULL)

/* Tensor #38 */
AI_TENSOR_OBJ_DECLARE(
  input_60_output, AI_STATIC,
  38, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 40), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &input_60_output_array, NULL)

/* Tensor #39 */
AI_TENSOR_OBJ_DECLARE(
  onnxConv_98_output, AI_STATIC,
  39, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 40), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &onnxConv_98_output_array, NULL)

/* Tensor #40 */
AI_TENSOR_OBJ_DECLARE(
  input_68_output, AI_STATIC,
  40, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 40), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &input_68_output_array, NULL)

/* Tensor #41 */
AI_TENSOR_OBJ_DECLARE(
  onnxConv_101_output, AI_STATIC,
  41, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 40), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &onnxConv_101_output_array, NULL)

/* Tensor #42 */
AI_TENSOR_OBJ_DECLARE(
  onnxAdd_145_output, AI_STATIC,
  42, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 40), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &onnxAdd_145_output_array, NULL)

/* Tensor #43 */
AI_TENSOR_OBJ_DECLARE(
  onnxRelu_104_output, AI_STATIC,
  43, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 40), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &onnxRelu_104_output_array, NULL)

/* Tensor #44 */
AI_TENSOR_OBJ_DECLARE(
  input_76_output, AI_STATIC,
  44, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 40), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &input_76_output_array, NULL)

/* Tensor #45 */
AI_TENSOR_OBJ_DECLARE(
  input_76_output0, AI_STATIC,
  45, 0x0,
  AI_SHAPE_INIT(4, 1, 2560, 1, 1), AI_STRIDE_INIT(4, 4, 4, 10240, 10240),
  1, &input_76_output_array, NULL)

/* Tensor #46 */
AI_TENSOR_OBJ_DECLARE(
  input_80_output, AI_STATIC,
  46, 0x0,
  AI_SHAPE_INIT(4, 1, 12, 1, 1), AI_STRIDE_INIT(4, 4, 4, 48, 48),
  1, &input_80_output_array, NULL)

/* Tensor #47 */
AI_TENSOR_OBJ_DECLARE(
  modelOutput_output, AI_STATIC,
  47, 0x0,
  AI_SHAPE_INIT(4, 1, 12, 1, 1), AI_STRIDE_INIT(4, 4, 4, 48, 48),
  1, &modelOutput_output_array, NULL)

/* Tensor #48 */
AI_TENSOR_OBJ_DECLARE(
  input_4_weights, AI_STATIC,
  48, 0x0,
  AI_SHAPE_INIT(4, 7, 1, 3, 64), AI_STRIDE_INIT(4, 4, 28, 1792, 1792),
  1, &input_4_weights_array, NULL)



/**  Layer declarations section  **********************************************/


AI_TENSOR_CHAIN_OBJ_DECLARE(
  modelOutput_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &input_80_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &modelOutput_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  modelOutput_layer, 32,
  NL_TYPE, 0x0, NULL,
  nl, forward_sm,
  &modelOutput_chain,
  NULL, &modelOutput_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  input_80_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &input_76_output0),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &input_80_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &input_80_weights, &input_80_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  input_80_layer, 31,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense,
  &input_80_chain,
  NULL, &modelOutput_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  input_76_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &onnxRelu_104_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &input_76_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  input_76_layer, 23,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &input_76_chain,
  NULL, &input_80_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  onnxRelu_104_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &onnxAdd_145_output, &input_52_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &onnxRelu_104_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  onnxRelu_104_layer, 22,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &onnxRelu_104_chain,
  NULL, &input_76_layer, AI_STATIC, 
  .operation = ai_sum_f32, 
  .buffer_operation = ai_sum_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  onnxAdd_145_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &onnxConv_101_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &onnxAdd_145_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &onnxAdd_145_weights, &onnxAdd_145_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  onnxAdd_145_layer, 21,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &onnxAdd_145_chain,
  NULL, &onnxRelu_104_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 0, 1, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  onnxConv_101_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &input_68_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &onnxConv_101_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  onnxConv_101_layer, 20,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &onnxConv_101_chain,
  NULL, &onnxAdd_145_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  input_68_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &onnxConv_98_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &input_68_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &input_68_weights, &input_68_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  input_68_layer, 19,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &input_68_chain,
  NULL, &onnxConv_101_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 0, 1, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  onnxConv_98_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &input_60_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &onnxConv_98_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  onnxConv_98_layer, 18,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &onnxConv_98_chain,
  NULL, &input_68_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  input_60_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &input_52_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &input_60_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &input_60_weights, &input_60_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  input_60_layer, 17,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &input_60_chain,
  NULL, &onnxConv_98_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 0, 1, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  input_52_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &onnxRelu_94_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &input_52_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  input_52_layer, 16,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &input_52_chain,
  NULL, &input_60_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  onnxRelu_94_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &onnxAdd_136_output, &input_28_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &onnxRelu_94_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  onnxRelu_94_layer, 15,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &onnxRelu_94_chain,
  NULL, &input_52_layer, AI_STATIC, 
  .operation = ai_sum_f32, 
  .buffer_operation = ai_sum_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  onnxAdd_136_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &onnxConv_91_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &onnxAdd_136_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &onnxAdd_136_weights, &onnxAdd_136_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  onnxAdd_136_layer, 14,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &onnxAdd_136_chain,
  NULL, &onnxRelu_94_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 0, 1, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  onnxConv_91_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &input_44_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &onnxConv_91_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  onnxConv_91_layer, 13,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &onnxConv_91_chain,
  NULL, &onnxAdd_136_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  input_44_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &onnxConv_88_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &input_44_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &input_44_weights, &input_44_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  input_44_layer, 12,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &input_44_chain,
  NULL, &onnxConv_91_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 0, 1, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  onnxConv_88_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &input_36_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &onnxConv_88_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  onnxConv_88_layer, 11,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &onnxConv_88_chain,
  NULL, &input_44_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  input_36_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &input_28_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &input_36_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &input_36_weights, &input_36_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  input_36_layer, 10,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &input_36_chain,
  NULL, &onnxConv_88_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 0, 1, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  input_28_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &onnxRelu_84_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &input_28_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  input_28_layer, 9,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &input_28_chain,
  NULL, &input_36_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  onnxRelu_84_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &onnxAdd_127_output, &onnxConv_75_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &onnxRelu_84_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  onnxRelu_84_layer, 8,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &onnxRelu_84_chain,
  NULL, &input_28_layer, AI_STATIC, 
  .operation = ai_sum_f32, 
  .buffer_operation = ai_sum_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  onnxAdd_127_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &onnxConv_81_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &onnxAdd_127_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &onnxAdd_127_weights, &onnxAdd_127_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  onnxAdd_127_layer, 7,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &onnxAdd_127_chain,
  NULL, &onnxRelu_84_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 0, 1, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  onnxConv_81_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &input_20_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &onnxConv_81_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  onnxConv_81_layer, 6,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &onnxConv_81_chain,
  NULL, &onnxAdd_127_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  input_20_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &onnxConv_78_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &input_20_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &input_20_weights, &input_20_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  input_20_layer, 5,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &input_20_chain,
  NULL, &onnxConv_81_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 0, 1, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  onnxConv_78_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &input_12_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &onnxConv_78_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  onnxConv_78_layer, 4,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &onnxConv_78_chain,
  NULL, &input_20_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  input_12_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &onnxConv_75_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &input_12_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &input_12_weights, &input_12_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  input_12_layer, 3,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &input_12_chain,
  NULL, &onnxConv_78_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 0, 1, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  onnxConv_75_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &input_4_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &onnxConv_75_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  onnxConv_75_layer, 2,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &onnxConv_75_chain,
  NULL, &input_12_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  input_4_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &modelInput_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &input_4_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &input_4_weights, &input_4_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  input_4_layer, 1,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &input_4_chain,
  NULL, &onnxConv_75_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 0, 1, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)


#if (AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 573232, 1, 1),
    573232, NULL, NULL),
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 22016, 1, 1),
    22016, NULL, NULL),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_COMBINATION_IN_NUM, &modelInput_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_COMBINATION_OUT_NUM, &modelOutput_output),
  &input_4_layer, 0, NULL)

#else

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 22,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 573232, 1, 1),
      573232, NULL, NULL)
  ),
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 1,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 22016, 1, 1),
      22016, NULL, NULL)
  ),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_COMBINATION_IN_NUM, &modelInput_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_COMBINATION_OUT_NUM, &modelOutput_output),
  &input_4_layer, 0, NULL)

#endif	/*(AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)*/


/******************************************************************************/
AI_DECLARE_STATIC
ai_bool combination_configure_activations(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_activations_map(g_combination_activations_map, 1, params)) {
    /* Updating activations (byte) offsets */
    
    modelInput_output_array.data = AI_PTR(g_combination_activations_map[0] + 416);
    modelInput_output_array.data_start = AI_PTR(g_combination_activations_map[0] + 416);
    
    input_4_output_array.data = AI_PTR(g_combination_activations_map[0] + 1536);
    input_4_output_array.data_start = AI_PTR(g_combination_activations_map[0] + 1536);
    
    onnxConv_75_output_array.data = AI_PTR(g_combination_activations_map[0] + 11776);
    onnxConv_75_output_array.data_start = AI_PTR(g_combination_activations_map[0] + 11776);
    
    input_12_output_array.data = AI_PTR(g_combination_activations_map[0] + 1536);
    input_12_output_array.data_start = AI_PTR(g_combination_activations_map[0] + 1536);
    
    onnxConv_78_output_array.data = AI_PTR(g_combination_activations_map[0] + 1536);
    onnxConv_78_output_array.data_start = AI_PTR(g_combination_activations_map[0] + 1536);
    
    input_20_output_array.data = AI_PTR(g_combination_activations_map[0] + 768);
    input_20_output_array.data_start = AI_PTR(g_combination_activations_map[0] + 768);
    
    onnxConv_81_output_array.data = AI_PTR(g_combination_activations_map[0] + 768);
    onnxConv_81_output_array.data_start = AI_PTR(g_combination_activations_map[0] + 768);
    
    onnxAdd_127_output_array.data = AI_PTR(g_combination_activations_map[0] + 0);
    onnxAdd_127_output_array.data_start = AI_PTR(g_combination_activations_map[0] + 0);
    
    onnxRelu_84_output_array.data = AI_PTR(g_combination_activations_map[0] + 0);
    onnxRelu_84_output_array.data_start = AI_PTR(g_combination_activations_map[0] + 0);
    
    input_28_output_array.data = AI_PTR(g_combination_activations_map[0] + 11776);
    input_28_output_array.data_start = AI_PTR(g_combination_activations_map[0] + 11776);
    
    input_36_output_array.data = AI_PTR(g_combination_activations_map[0] + 1536);
    input_36_output_array.data_start = AI_PTR(g_combination_activations_map[0] + 1536);
    
    onnxConv_88_output_array.data = AI_PTR(g_combination_activations_map[0] + 1536);
    onnxConv_88_output_array.data_start = AI_PTR(g_combination_activations_map[0] + 1536);
    
    input_44_output_array.data = AI_PTR(g_combination_activations_map[0] + 768);
    input_44_output_array.data_start = AI_PTR(g_combination_activations_map[0] + 768);
    
    onnxConv_91_output_array.data = AI_PTR(g_combination_activations_map[0] + 768);
    onnxConv_91_output_array.data_start = AI_PTR(g_combination_activations_map[0] + 768);
    
    onnxAdd_136_output_array.data = AI_PTR(g_combination_activations_map[0] + 0);
    onnxAdd_136_output_array.data_start = AI_PTR(g_combination_activations_map[0] + 0);
    
    onnxRelu_94_output_array.data = AI_PTR(g_combination_activations_map[0] + 0);
    onnxRelu_94_output_array.data_start = AI_PTR(g_combination_activations_map[0] + 0);
    
    input_52_output_array.data = AI_PTR(g_combination_activations_map[0] + 11776);
    input_52_output_array.data_start = AI_PTR(g_combination_activations_map[0] + 11776);
    
    input_60_output_array.data = AI_PTR(g_combination_activations_map[0] + 1536);
    input_60_output_array.data_start = AI_PTR(g_combination_activations_map[0] + 1536);
    
    onnxConv_98_output_array.data = AI_PTR(g_combination_activations_map[0] + 1536);
    onnxConv_98_output_array.data_start = AI_PTR(g_combination_activations_map[0] + 1536);
    
    input_68_output_array.data = AI_PTR(g_combination_activations_map[0] + 768);
    input_68_output_array.data_start = AI_PTR(g_combination_activations_map[0] + 768);
    
    onnxConv_101_output_array.data = AI_PTR(g_combination_activations_map[0] + 768);
    onnxConv_101_output_array.data_start = AI_PTR(g_combination_activations_map[0] + 768);
    
    onnxAdd_145_output_array.data = AI_PTR(g_combination_activations_map[0] + 0);
    onnxAdd_145_output_array.data_start = AI_PTR(g_combination_activations_map[0] + 0);
    
    onnxRelu_104_output_array.data = AI_PTR(g_combination_activations_map[0] + 0);
    onnxRelu_104_output_array.data_start = AI_PTR(g_combination_activations_map[0] + 0);
    
    input_76_output_array.data = AI_PTR(g_combination_activations_map[0] + 10240);
    input_76_output_array.data_start = AI_PTR(g_combination_activations_map[0] + 10240);
    
    input_80_output_array.data = AI_PTR(g_combination_activations_map[0] + 0);
    input_80_output_array.data_start = AI_PTR(g_combination_activations_map[0] + 0);
    
    modelOutput_output_array.data = AI_PTR(g_combination_activations_map[0] + 48);
    modelOutput_output_array.data_start = AI_PTR(g_combination_activations_map[0] + 48);
    
    return true;
  }
  AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_ACTIVATIONS);
  return false;
}



/******************************************************************************/
AI_DECLARE_STATIC
ai_bool combination_configure_weights(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_weights_map(g_combination_weights_map, 22, params)) {
    /* Updating weights (byte) offsets */
    
    input_4_bias_array.format |= AI_FMT_FLAG_CONST;
    input_4_bias_array.data = AI_PTR(g_combination_weights_map[0] + 0);
    input_4_bias_array.data_start = AI_PTR(g_combination_weights_map[0] + 0);
    
    input_12_weights_array.format |= AI_FMT_FLAG_CONST;
    input_12_weights_array.data = AI_PTR(g_combination_weights_map[1] + 0);
    input_12_weights_array.data_start = AI_PTR(g_combination_weights_map[1] + 0);
    
    input_12_bias_array.format |= AI_FMT_FLAG_CONST;
    input_12_bias_array.data = AI_PTR(g_combination_weights_map[2] + 0);
    input_12_bias_array.data_start = AI_PTR(g_combination_weights_map[2] + 0);
    
    input_20_weights_array.format |= AI_FMT_FLAG_CONST;
    input_20_weights_array.data = AI_PTR(g_combination_weights_map[3] + 0);
    input_20_weights_array.data_start = AI_PTR(g_combination_weights_map[3] + 0);
    
    input_20_bias_array.format |= AI_FMT_FLAG_CONST;
    input_20_bias_array.data = AI_PTR(g_combination_weights_map[4] + 0);
    input_20_bias_array.data_start = AI_PTR(g_combination_weights_map[4] + 0);
    
    onnxAdd_127_weights_array.format |= AI_FMT_FLAG_CONST;
    onnxAdd_127_weights_array.data = AI_PTR(g_combination_weights_map[5] + 0);
    onnxAdd_127_weights_array.data_start = AI_PTR(g_combination_weights_map[5] + 0);
    
    onnxAdd_127_bias_array.format |= AI_FMT_FLAG_CONST;
    onnxAdd_127_bias_array.data = AI_PTR(g_combination_weights_map[6] + 0);
    onnxAdd_127_bias_array.data_start = AI_PTR(g_combination_weights_map[6] + 0);
    
    input_36_weights_array.format |= AI_FMT_FLAG_CONST;
    input_36_weights_array.data = AI_PTR(g_combination_weights_map[7] + 0);
    input_36_weights_array.data_start = AI_PTR(g_combination_weights_map[7] + 0);
    
    input_36_bias_array.format |= AI_FMT_FLAG_CONST;
    input_36_bias_array.data = AI_PTR(g_combination_weights_map[8] + 0);
    input_36_bias_array.data_start = AI_PTR(g_combination_weights_map[8] + 0);
    
    input_44_weights_array.format |= AI_FMT_FLAG_CONST;
    input_44_weights_array.data = AI_PTR(g_combination_weights_map[9] + 0);
    input_44_weights_array.data_start = AI_PTR(g_combination_weights_map[9] + 0);
    
    input_44_bias_array.format |= AI_FMT_FLAG_CONST;
    input_44_bias_array.data = AI_PTR(g_combination_weights_map[10] + 0);
    input_44_bias_array.data_start = AI_PTR(g_combination_weights_map[10] + 0);
    
    onnxAdd_136_weights_array.format |= AI_FMT_FLAG_CONST;
    onnxAdd_136_weights_array.data = AI_PTR(g_combination_weights_map[11] + 0);
    onnxAdd_136_weights_array.data_start = AI_PTR(g_combination_weights_map[11] + 0);
    
    onnxAdd_136_bias_array.format |= AI_FMT_FLAG_CONST;
    onnxAdd_136_bias_array.data = AI_PTR(g_combination_weights_map[12] + 0);
    onnxAdd_136_bias_array.data_start = AI_PTR(g_combination_weights_map[12] + 0);
    
    input_60_weights_array.format |= AI_FMT_FLAG_CONST;
    input_60_weights_array.data = AI_PTR(g_combination_weights_map[13] + 0);
    input_60_weights_array.data_start = AI_PTR(g_combination_weights_map[13] + 0);
    
    input_60_bias_array.format |= AI_FMT_FLAG_CONST;
    input_60_bias_array.data = AI_PTR(g_combination_weights_map[14] + 0);
    input_60_bias_array.data_start = AI_PTR(g_combination_weights_map[14] + 0);
    
    input_68_weights_array.format |= AI_FMT_FLAG_CONST;
    input_68_weights_array.data = AI_PTR(g_combination_weights_map[15] + 0);
    input_68_weights_array.data_start = AI_PTR(g_combination_weights_map[15] + 0);
    
    input_68_bias_array.format |= AI_FMT_FLAG_CONST;
    input_68_bias_array.data = AI_PTR(g_combination_weights_map[16] + 0);
    input_68_bias_array.data_start = AI_PTR(g_combination_weights_map[16] + 0);
    
    onnxAdd_145_weights_array.format |= AI_FMT_FLAG_CONST;
    onnxAdd_145_weights_array.data = AI_PTR(g_combination_weights_map[17] + 0);
    onnxAdd_145_weights_array.data_start = AI_PTR(g_combination_weights_map[17] + 0);
    
    onnxAdd_145_bias_array.format |= AI_FMT_FLAG_CONST;
    onnxAdd_145_bias_array.data = AI_PTR(g_combination_weights_map[18] + 0);
    onnxAdd_145_bias_array.data_start = AI_PTR(g_combination_weights_map[18] + 0);
    
    input_80_weights_array.format |= AI_FMT_FLAG_CONST;
    input_80_weights_array.data = AI_PTR(g_combination_weights_map[19] + 0);
    input_80_weights_array.data_start = AI_PTR(g_combination_weights_map[19] + 0);
    
    input_80_bias_array.format |= AI_FMT_FLAG_CONST;
    input_80_bias_array.data = AI_PTR(g_combination_weights_map[20] + 0);
    input_80_bias_array.data_start = AI_PTR(g_combination_weights_map[20] + 0);
    
    input_4_weights_array.format |= AI_FMT_FLAG_CONST;
    input_4_weights_array.data = AI_PTR(g_combination_weights_map[21] + 0);
    input_4_weights_array.data_start = AI_PTR(g_combination_weights_map[21] + 0);
    
    return true;
  }
  AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_WEIGHTS);
  return false;
}


/**  PUBLIC APIs SECTION  *****************************************************/


AI_DEPRECATED
AI_API_ENTRY
ai_bool ai_combination_get_info(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_COMBINATION_MODEL_NAME,
      .model_signature   = AI_COMBINATION_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 4542272,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .params            = AI_STRUCT_INIT,
      .activations       = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x0,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}


AI_API_ENTRY
ai_bool ai_combination_get_report(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_COMBINATION_MODEL_NAME,
      .model_signature   = AI_COMBINATION_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 4542272,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .map_signature     = AI_MAGIC_SIGNATURE,
      .map_weights       = AI_STRUCT_INIT,
      .map_activations   = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x0,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}

AI_API_ENTRY
ai_error ai_combination_get_error(ai_handle network)
{
  return ai_platform_network_get_error(network);
}

AI_API_ENTRY
ai_error ai_combination_create(
  ai_handle* network, const ai_buffer* network_config)
{
  return ai_platform_network_create(
    network, network_config, 
    &AI_NET_OBJ_INSTANCE,
    AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR, AI_TOOLS_API_VERSION_MICRO);
}

AI_API_ENTRY
ai_error ai_combination_create_and_init(
  ai_handle* network, const ai_handle activations[], const ai_handle weights[])
{
    ai_error err;
    ai_network_params params;

    err = ai_combination_create(network, AI_COMBINATION_DATA_CONFIG);
    if (err.type != AI_ERROR_NONE)
        return err;
    if (ai_combination_data_params_get(&params) != true) {
        err = ai_combination_get_error(*network);
        return err;
    }
#if defined(AI_COMBINATION_DATA_ACTIVATIONS_COUNT)
    if (activations) {
        /* set the addresses of the activations buffers */
        for (int idx=0;idx<params.map_activations.size;idx++)
            AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_activations, idx, activations[idx]);
    }
#endif
#if defined(AI_COMBINATION_DATA_WEIGHTS_COUNT)
    if (weights) {
        /* set the addresses of the weight buffers */
        for (int idx=0;idx<params.map_weights.size;idx++)
            AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_weights, idx, weights[idx]);
    }
#endif
    if (ai_combination_init(*network, &params) != true) {
        err = ai_combination_get_error(*network);
    }
    return err;
}

AI_API_ENTRY
ai_buffer* ai_combination_inputs_get(ai_handle network, ai_u16 *n_buffer)
{
  if (network == AI_HANDLE_NULL) {
    network = (ai_handle)&AI_NET_OBJ_INSTANCE;
    ((ai_network *)network)->magic = AI_MAGIC_CONTEXT_TOKEN;
  }
  return ai_platform_inputs_get(network, n_buffer);
}

AI_API_ENTRY
ai_buffer* ai_combination_outputs_get(ai_handle network, ai_u16 *n_buffer)
{
  if (network == AI_HANDLE_NULL) {
    network = (ai_handle)&AI_NET_OBJ_INSTANCE;
    ((ai_network *)network)->magic = AI_MAGIC_CONTEXT_TOKEN;
  }
  return ai_platform_outputs_get(network, n_buffer);
}

AI_API_ENTRY
ai_handle ai_combination_destroy(ai_handle network)
{
  return ai_platform_network_destroy(network);
}

AI_API_ENTRY
ai_bool ai_combination_init(
  ai_handle network, const ai_network_params* params)
{
  ai_network* net_ctx = ai_platform_network_init(network, params);
  if (!net_ctx) return false;

  ai_bool ok = true;
  ok &= combination_configure_weights(net_ctx, params);
  ok &= combination_configure_activations(net_ctx, params);

  ok &= ai_platform_network_post_init(network);

  return ok;
}


AI_API_ENTRY
ai_i32 ai_combination_run(
  ai_handle network, const ai_buffer* input, ai_buffer* output)
{
  return ai_platform_network_process(network, input, output);
}

AI_API_ENTRY
ai_i32 ai_combination_forward(ai_handle network, const ai_buffer* input)
{
  return ai_platform_network_process(network, input, NULL);
}



#undef AI_COMBINATION_MODEL_SIGNATURE
#undef AI_NET_OBJ_INSTANCE
#undef AI_TOOLS_DATE_TIME
#undef AI_TOOLS_COMPILE_TIME

