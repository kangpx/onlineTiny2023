#ifndef __QVAR_H__
#define __QVAR_H__

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

#define FOLD 20

#define _PATH(prefix, core, suffix) prefix"/fold_"#core"/"suffix
#define _TEST_SAMPLE_DIR(fold) _PATH("/home/kangpx/onlineTiny2023/datasets/incu_datasets/qvar/c_input", fold, "test")
#define _INCU_SAMPLE_DIR(fold) _PATH("/home/kangpx/onlineTiny2023/datasets/incu_datasets/qvar/c_input", fold, "incu")
#define TEST_SAMPLE_DIR _TEST_SAMPLE_DIR(FOLD)
#define INCU_SAMPLE_DIR _INCU_SAMPLE_DIR(FOLD)

#if FOLD == 1
#define N_TEST_SAMPLE (186)
#define N_INCU_SAMPLE (124)
#elif FOLD == 2
#define N_TEST_SAMPLE (175)
#define N_INCU_SAMPLE (117)
#elif FOLD == 3
#define N_TEST_SAMPLE (178)
#define N_INCU_SAMPLE (120)
#elif FOLD == 4
#define N_TEST_SAMPLE (155)
#define N_INCU_SAMPLE (104)
#elif FOLD == 5
#define N_TEST_SAMPLE (174)
#define N_INCU_SAMPLE (116)
#elif FOLD == 6
#define N_TEST_SAMPLE (180)
#define N_INCU_SAMPLE (120)
#elif FOLD == 7
#define N_TEST_SAMPLE (174)
#define N_INCU_SAMPLE (117)
#elif FOLD == 8
#define N_TEST_SAMPLE (180)
#define N_INCU_SAMPLE (120)
#elif FOLD == 9
#define N_TEST_SAMPLE (165)
#define N_INCU_SAMPLE (110)
#elif FOLD == 10
#define N_TEST_SAMPLE (169)
#define N_INCU_SAMPLE (114)
#elif FOLD == 11
#define N_TEST_SAMPLE (178)
#define N_INCU_SAMPLE (119)
#elif FOLD == 12
#define N_TEST_SAMPLE (180)
#define N_INCU_SAMPLE (120)
#elif FOLD == 13
#define N_TEST_SAMPLE (176)
#define N_INCU_SAMPLE (118)
#elif FOLD == 14
#define N_TEST_SAMPLE (175)
#define N_INCU_SAMPLE (118)
#elif FOLD == 15
#define N_TEST_SAMPLE (178)
#define N_INCU_SAMPLE (119)
#elif FOLD == 16
#define N_TEST_SAMPLE (177)
#define N_INCU_SAMPLE (119)
#elif FOLD == 17
#define N_TEST_SAMPLE (132)
#define N_INCU_SAMPLE (89)
#elif FOLD == 18
#define N_TEST_SAMPLE (178)
#define N_INCU_SAMPLE (120)
#elif FOLD == 19
#define N_TEST_SAMPLE (174)
#define N_INCU_SAMPLE (116)
#elif FOLD == 20 
#define N_TEST_SAMPLE (176)
#define N_INCU_SAMPLE (118)
#endif

extern AT_HYPERFLASH_EXT_ADDR_TYPE Qvar_L3_Flash;

#endif
