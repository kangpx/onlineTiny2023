#ifndef __ultra_H__
#define __ultra_H__

#define __PREFIX(x) ultra ## x
// Include basic GAP builtins defined in the Autotiler
#include "Gap.h"

#ifdef __EMUL__
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/param.h>
#include <string.h>
#endif

/* Variables used */
#ifndef STACK_SIZE
#define STACK_SIZE 1024
#endif

#define TEST_SAMPLE_DIR "/home/kangpx/onlineTiny2023/datasets/incu_datasets/ultra/c_input/fold_2/test"
#define INCU_SAMPLE_DIR "/home/kangpx/onlineTiny2023/datasets/incu_datasets/ultra/c_input/fold_2/incu"
#define N_TEST_SAMPLE (480)
#define N_INCU_SAMPLE (320)

extern AT_HYPERFLASH_EXT_ADDR_TYPE Ultra_L3_Flash;
#endif
