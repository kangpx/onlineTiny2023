/* PMSIS includes. */
#include "pmsis.h"

/* Autotiler includes. */
#include "Gap.h"
#include "Gym.h"
#include "GymKernels.h"

#if defined(ENABLE_BRIDGE)
#include "gaplib/ImgIO.h"
#endif  /* USE_BRIDGE */

/* Online Training includes. */
#include "online_training.h"


/* extern global variables */
AT_HYPERFLASH_EXT_ADDR_TYPE Gym_L3_Flash = 0;
extern unsigned char ot_flag;
extern unsigned char y_real;
extern F16 in_data[INPUT_DATA_SIZE];
extern F16 out_data[DENSE_OUTPUT_SIZE];

/* global variables */
char sample_path[100];
unsigned char y_pred;
unsigned char y_test_real[N_TEST_SAMPLE];
unsigned char y_test_pred[N_TEST_SAMPLE];

/* function prototypes */
static void inference(void *);
static void readXYfromFloat32File(char *fileName, unsigned int xSize, unsigned int ySize, void *xBuffer, void *yBuffer);
static void fetch_input(char *sample_src_, unsigned int sample_idx_);
static void triplet_init(char *sample_src_, unsigned int sample_idx_, unsigned int ot_flag_);
static float accuracy_score(unsigned int);


int main(void)
{
    printf("\n\n\t *** PMSIS Mnist Test ***\n\n");
    printf("entering main controller.\n");
    //------------------------------------------------------------------//
    //                           check bridge                           //
    //------------------------------------------------------------------//
    #if !defined(ENABLE_BRIDGE)
        printf("ERROR: bridge not enabled, abort.\n");
        return -1;
    #endif 
    printf("bridge checked.\n");

    //------------------------------------------------------------------//
    //                    configure and open cluster                    //
    //------------------------------------------------------------------//
    struct pi_device cluster_dev;
    struct pi_cluster_conf cl_conf;
    struct pi_cluster_task cl_task;

    pi_cluster_conf_init(&cl_conf);
    cl_conf.id = 0;
    cl_conf.cc_stack_size = STACK_SIZE;
    //cl_conf.icache_conf = PI_CLUSTER_MASTER_CORE_ICACHE_ENABLE | PI_CLUSTER_ICACHE_PREFETCH_ENABLE | PI_CLUSTER_ICACHE_ENABLE;

    pi_open_from_conf(&cluster_dev, (void *) &cl_conf);
    if (pi_cluster_open(&cluster_dev))
    {
        printf("ERROR: cluster open failed.\n");
        pmsis_exit(-7);
    }
    printf("cluster opened.\n");

    //------------------------------------------------------------------//
    //                         construct model                          //
    //------------------------------------------------------------------//
    int ConstructorErr = GymCNN_Construct();
    if (ConstructorErr)
    {
        printf("ERROR: graph constructor exited with error: %s\n", GetAtErrorName(ConstructorErr));
        pmsis_exit(-6);
    }
    printf("nn constructed.\n");

    //------------------------------------------------------------------//
    //                       online training init                       //
    //------------------------------------------------------------------//
     if (ot_init_chunk() < 0){
         printf("L1 memory init error during ot_init_chunk.\n");
         pmsis_exit(-6);
    }
    printf("online training initialized.\n");

    // ------------------------------------------------------------------//
    //                               test                               //
    // ------------------------------------------------------------------//
    for (unsigned int sample_idx = 0; sample_idx < N_TEST_SAMPLE; sample_idx++){
        y_test_real[sample_idx] = 0xfe;
        y_test_pred[sample_idx] = 0xff;
    }
    for (unsigned int sample_idx = 0; sample_idx < N_TEST_SAMPLE; sample_idx++){
        triplet_init(TEST_SAMPLE_DIR, sample_idx, OT_DISABLE);
        y_test_real[sample_idx] = y_real;

        pi_cluster_send_task_to_cl(&cluster_dev, pi_cluster_task(&cl_task, inference, &y_pred));
        y_test_pred[sample_idx] = y_pred;

        printf("TEST--idx = %lu/%lu, y_real/y_pred = %lu/%lu, accuracy=%f\n", sample_idx+1, N_TEST_SAMPLE, y_real, y_pred, accuracy_score(sample_idx+1));
    }
    printf("Accuracy: %f\n", accuracy_score(N_TEST_SAMPLE));

    //------------------------------------------------------------------//
    //                         online training                          //
    //------------------------------------------------------------------//
    for (unsigned int epoch = 0; epoch < 1; epoch++)
        for (unsigned int sample_idx = 0; sample_idx < N_INCU_SAMPLE; sample_idx++){
            triplet_init(INCU_SAMPLE_DIR, sample_idx, OT_ENABLE);

            pi_cluster_send_task_to_cl(&cluster_dev, pi_cluster_task(&cl_task, inference, &y_pred));

            pi_cluster_send_task_to_cl(&cluster_dev, pi_cluster_task(&cl_task, ot_update_chunk_parallel, NULL));

            printf("INCU--epoch=%lu/%lu, idx = %lu/%lu, y_real/y_pred = %lu/%lu\n", epoch+1, 1, sample_idx+1, N_INCU_SAMPLE, y_real, y_pred);
        }

    //------------------------------------------------------------------//
    //                               test                               //
    //------------------------------------------------------------------//
    for (unsigned int sample_idx = 0; sample_idx < N_TEST_SAMPLE; sample_idx++){
        y_test_real[sample_idx] = 0xfe;
        y_test_pred[sample_idx] = 0xff;
    }
    for (unsigned int sample_idx = 0; sample_idx < N_TEST_SAMPLE; sample_idx++){
        triplet_init(TEST_SAMPLE_DIR, sample_idx, OT_DISABLE);
        y_test_real[sample_idx] = y_real;

        pi_cluster_send_task_to_cl(&cluster_dev, pi_cluster_task(&cl_task, inference, &y_pred));
        y_test_pred[sample_idx] = y_pred;

        printf("TEST--idx = %lu/%lu, y_real/y_pred = %lu/%lu, accuracy=%f\n", sample_idx + 1, N_TEST_SAMPLE, y_real, y_pred, accuracy_score(sample_idx+1));
    }
    printf("Accuracy: %f\n", accuracy_score(N_TEST_SAMPLE));

    //------------------------------------------------------------------//
    //                          destruct model                          //
    //------------------------------------------------------------------//
    GymCNN_Destruct();
    printf("nn destructed.\n");

    //------------------------------------------------------------------//
    //                          close cluster                           //
    //------------------------------------------------------------------//
    pi_cluster_close(&cluster_dev);
    printf("cluster closed.\n");

    //------------------------------------------------------------------//
    //                      online training clean                       //
    //------------------------------------------------------------------//
    ot_clean_chunk();
    printf("online training cleaned.\n");

    return 0;
}

static void inference(void *arg)
{
    GymCNN(in_data, out_data);
    unsigned char *digit = (unsigned char *)arg;
    *digit = 0;
    F16 highest = *out_data;
    for (unsigned char i=1; i<DENSE_OUTPUT_SIZE; i++)
    {
        if (highest < out_data[i])
        {
            highest = out_data[i];
            *digit = i;
        }
    }
}

static void readXYfromFloat32File(char *fileName, unsigned int xSize, unsigned int ySize, void *xBuffer, void *yBuffer)
{
    switch_file_t File = (switch_file_t) 0;
    switch_fs_t fs;
    __FS_INIT(fs);
    File = __OPEN_READ(fs, fileName);
    if (File == 0){
        printf("Failed to open file, %s\n", fileName);
    }
    F16 *pXBuffer = (F16 *)xBuffer;
    unsigned char *pYBuffer = (unsigned char *)yBuffer;
    unsigned char *inputBuf = (unsigned char *)__ALLOC_L2((xSize + ySize) * 4); // x4 because of float32
    if (inputBuf == NULL){
        printf("Malloc failed when loading data\n");
        return -1;
    }
    
    __SEEK(File, 0); 

    unsigned int remainBytes = (xSize + ySize) * 4;
    unsigned char *pInputBuf = inputBuf;
    while(remainBytes > 0){
        __int_ssize_t len = __READ(File, pInputBuf, remainBytes);
        if (!len) return 1;
        remainBytes -= len;
        pInputBuf += len;
    }

    for (int i=0; i<xSize; i++)
        ((F16 *)pXBuffer)[i] = (F16)(((float *)inputBuf)[i]);
    for (int i=0; i<ySize; i++)
        ((unsigned char *)pYBuffer)[i] = (unsigned char)(((float *)inputBuf)[xSize+i]);
    __FREE_L2(inputBuf, (xSize+ySize)*4);
    __CLOSE(File);
    __FS_DEINIT(fs);
}

static void fetch_input(char *sample_src_, unsigned int sample_idx_)
{
    for (int i=0; i<sizeof(sample_path); i++)
        sample_path[i] = 0;
    sprintf(sample_path, "%s/%lu.input", sample_src_, sample_idx_);
    printf("input_path=%s ", sample_path);
    readXYfromFloat32File(sample_path, INPUT_DATA_SIZE, 1, in_data, &y_real);
}

static void triplet_init(char *sample_src_, unsigned int sample_idx_, unsigned int ot_flag_)
{
    fetch_input(sample_src_, sample_idx_);
    ot_flag = ot_flag_;
}

static float accuracy_score(unsigned int n_sample)
{
    unsigned int correct_cnt = 0;
    for (unsigned int i=0; i<n_sample; i++)
        if (y_test_pred[i] == y_test_real[i])
            correct_cnt += 1;
    return ((float)correct_cnt) / ((float)n_sample);
}

