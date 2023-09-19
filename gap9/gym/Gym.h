#ifndef __Gym_H__
#define __Gym_H__

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

#define FOLD 1

#define _PATH(prefix, core, suffix) prefix"/fold_"#core"/"suffix
#define _TEST_SAMPLE_DIR(fold) _PATH("/home/kangpx/onlineTiny2023/datasets/incu_datasets/gym/c_input", fold, "test")
#define _INCU_SAMPLE_DIR(fold) _PATH("/home/kangpx/onlineTiny2023/datasets/incu_datasets/gym/c_input", fold, "incu")
#define TEST_SAMPLE_DIR _TEST_SAMPLE_DIR(FOLD)
#define INCU_SAMPLE_DIR _INCU_SAMPLE_DIR(FOLD)

#if FOLD == 1
#define N_TEST_SAMPLE (2299)
#define N_INCU_SAMPLE (1533)
#elif FOLD == 2
#define N_TEST_SAMPLE (2880)
#define N_INCU_SAMPLE (1921)
#elif FOLD == 3
#define N_TEST_SAMPLE (2412)
#define N_INCU_SAMPLE (1609)
#elif FOLD == 4
#define N_TEST_SAMPLE (2519)
#define N_INCU_SAMPLE (1680)
#elif FOLD == 5
#define N_TEST_SAMPLE (2385)
#define N_INCU_SAMPLE (1591)
#elif FOLD == 6
#define N_TEST_SAMPLE (2739)
#define N_INCU_SAMPLE (1827)
#elif FOLD == 7
#define N_TEST_SAMPLE (2518)
#define N_INCU_SAMPLE (1679)
#elif FOLD == 8
#define N_TEST_SAMPLE (2265)
#define N_INCU_SAMPLE (1510)
#elif FOLD == 9
#define N_TEST_SAMPLE (2152)
#define N_INCU_SAMPLE (1435)
#elif FOLD == 10
#define N_TEST_SAMPLE (2216)
#define N_INCU_SAMPLE (1478)
#endif

extern AT_HYPERFLASH_EXT_ADDR_TYPE Gym_L3_Flash;

#endif
