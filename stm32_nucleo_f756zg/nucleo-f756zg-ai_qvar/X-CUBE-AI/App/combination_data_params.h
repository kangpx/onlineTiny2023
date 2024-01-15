/**
  ******************************************************************************
  * @file    combination_data_params.h
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

#ifndef COMBINATION_DATA_PARAMS_H
#define COMBINATION_DATA_PARAMS_H
#pragma once

#include "ai_platform.h"

/*
#define AI_COMBINATION_DATA_WEIGHTS_PARAMS \
  (AI_HANDLE_PTR(&ai_combination_data_weights_params[1]))
*/

#define AI_COMBINATION_DATA_CONFIG               (NULL)


#define AI_COMBINATION_DATA_ACTIVATIONS_SIZES \
  { 11008, }
#define AI_COMBINATION_DATA_ACTIVATIONS_SIZE     (11008)
#define AI_COMBINATION_DATA_ACTIVATIONS_COUNT    (1)
#define AI_COMBINATION_DATA_ACTIVATION_1_SIZE    (11008)



#define AI_COMBINATION_DATA_WEIGHTS_SIZES \
  { 128, 12288, 128, 12288, 128, 12288, 128, 12288, 128, 12288, 128, 51200, 40, 3456, 128, 12288, 128, 12288, 128, 12288, 128, 12288, }
#define AI_COMBINATION_DATA_WEIGHTS_SIZE         (166568)
#define AI_COMBINATION_DATA_WEIGHTS_COUNT        (22)
#define AI_COMBINATION_DATA_WEIGHT_1_SIZE        (128)
#define AI_COMBINATION_DATA_WEIGHT_2_SIZE        (12288)
#define AI_COMBINATION_DATA_WEIGHT_3_SIZE        (128)
#define AI_COMBINATION_DATA_WEIGHT_4_SIZE        (12288)
#define AI_COMBINATION_DATA_WEIGHT_5_SIZE        (128)
#define AI_COMBINATION_DATA_WEIGHT_6_SIZE        (12288)
#define AI_COMBINATION_DATA_WEIGHT_7_SIZE        (128)
#define AI_COMBINATION_DATA_WEIGHT_8_SIZE        (12288)
#define AI_COMBINATION_DATA_WEIGHT_9_SIZE        (128)
#define AI_COMBINATION_DATA_WEIGHT_10_SIZE        (12288)
#define AI_COMBINATION_DATA_WEIGHT_11_SIZE        (128)
#define AI_COMBINATION_DATA_WEIGHT_12_SIZE        (51200)
#define AI_COMBINATION_DATA_WEIGHT_13_SIZE        (40)
#define AI_COMBINATION_DATA_WEIGHT_14_SIZE        (3456)
#define AI_COMBINATION_DATA_WEIGHT_15_SIZE        (128)
#define AI_COMBINATION_DATA_WEIGHT_16_SIZE        (12288)
#define AI_COMBINATION_DATA_WEIGHT_17_SIZE        (128)
#define AI_COMBINATION_DATA_WEIGHT_18_SIZE        (12288)
#define AI_COMBINATION_DATA_WEIGHT_19_SIZE        (128)
#define AI_COMBINATION_DATA_WEIGHT_20_SIZE        (12288)
#define AI_COMBINATION_DATA_WEIGHT_21_SIZE        (128)
#define AI_COMBINATION_DATA_WEIGHT_22_SIZE        (12288)



#define AI_COMBINATION_DATA_ACTIVATIONS_TABLE_GET() \
  (&g_combination_activations_table[1])

extern ai_handle g_combination_activations_table[1 + 2];



#define AI_COMBINATION_DATA_WEIGHTS_TABLE_GET() \
  (&g_combination_weights_table[1])

extern ai_handle g_combination_weights_table[22 + 2];


#endif    /* COMBINATION_DATA_PARAMS_H */
