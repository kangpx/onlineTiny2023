# onlineTiny2023
## Latency and Power Measurements
### model
1. ultra: onlineTiny2023/saved_models/ultra/onnx/fold_1_pre_combination_fullvalid_b32.onnx
2. qvar: onlineTiny2023/saved_models/qvar/onnx/fold_1_pre_combination_fullvalid_b32.onnx
3. gym: onlineTiny2023/saved_models/gym/onnx/fold_1_pre_combination_fullvalid_b32_s20.onnx
### latency and power
[stm32F7, GAP9] x different operating frequency and voltage 
#### latency
1. latency per inference
2. latency per parameter update
#### power
1. energy per inference
2. power/energy efficiency?
### path of changed files
1. CNN_Defines_fp16.h: gap_sdk_private-master/tools/autotiler_v3/CNN_Defines_fp16.h
2. CNN_MatMul_Conv_fp16.c: gap_sdk_private-master/tools/autotiler_v3/CNN_MatMul_Conv_fp16.c
3. CNN_SoftMax_fp16.c: gap_sdk_private-master/tools/autotiler_v3/CNN_SoftMax_fp16.c
4. FastFloatApprox.h: gap_sdk_private-master/tools/autotiler_v3/DSP_Libraries/FastFloatApprox.h

## Python
3.9.12
## PyTorch
1.12.0
## Datasets
- Gym https://www.kaggle.com/datasets/zhaxidelebsz/10-gym-exercises-with-615-abstracted-features
- QVAR from PBL
- Ultra https://github.com/kangpx/40khz-ultrasonicDHGR-onlineSemi

For convenience, the datasets can be accessed by downloading this zip file:) https://drive.google.com/file/d/16LG2n-HL6iRwwSp0ecCHfA3dEQ5ukCyj/view?usp=sharing
## Saved Models
The model topology is from [1] and shown in the following figure:
<p align="center"><img width="310" alt="Screenshot 2023-08-20 at 22 27 59" src="https://github.com/kangpx/onlineTiny2023/assets/118830544/ab6f4c5d-2c19-4714-888c-034a19d46240"></p>

Difference from [1] is that the channel number is changed from 64 to 32.

The three datasets' pre-trained models of each fold (leave-one-user-out) formatted in .pt and .onnx are stored under the the directory `saved_models`. For .pt models, backbone and classifier are stored seperately. For .onnx models, the backbone and classifier are combined before being saved.
## Online Training using PyTorch
### Gym Dataset (OUTDATED)
classwise:
![classwise_gym_partvalid](https://github.com/kangpx/onlineTiny2023/assets/118830544/4ce74734-be43-4682-97e1-79f252993459)


foldwise:
![foldwise_gym_partvalid](https://github.com/kangpx/onlineTiny2023/assets/118830544/2e5b97b7-38ef-4b8d-9401-d3c66558491f)



### QVAR Dataset (OUTDATED)
classwise:
![classwise_qvar_partvalid](https://github.com/kangpx/onlineTiny2023/assets/118830544/e0bc2537-21b5-4968-814c-6e4d48217ce5)



foldwise:
![foldwise_qvar_partvalid](https://github.com/kangpx/onlineTiny2023/assets/118830544/d13ed600-6e63-45ff-8d17-97265ba1743a)



### Ultra Dataset (OUTDATED)
classwise:
![classwise_ultrasonic_partvalid](https://github.com/kangpx/onlineTiny2023/assets/118830544/4d1a5eb7-eb81-41cc-8bb8-6bf964d112ce)


foldwise:
![foldwise_ultrasonic_partvalid](https://github.com/kangpx/onlineTiny2023/assets/118830544/b4bdee0e-5591-44f4-881b-d68377b85f97)



## Online Training on STM32 Nucleo-F756ZG
### X-CUBE-AI
MacArm 8.1.0
### Work Flow
<p align="center"><img src="https://github.com/kangpx/onlineTiny2023/assets/118830544/2e0a23cd-2673-4225-b93e-e99a41908b83" width="60%"></p>

1. PC transmits a triplet $(x(\tau)$, $y(\tau)$, $\text{flag}(\tau))$ to MCU through UART, where $x(\tau)$ is the input data, $y(\tau)$ is the input label, $\text{flag}(\tau)$ is the trigger signal for online training and $\tau$ is the current time stamp;
2. X-CUBE-AI's inference engine performs the inference, during which the input to the last fully connected layer (classifier) is retrieved by a registered callback of platform observer and dumped into the dense input buffer, while the inference output (i.e., the output of the softmax layer) is dumped into the output buffer;
3. If online training is triggered ($\text{flag}(\tau)$==1) in this round, the implemented online training engine traverses the weights/biases of the classifier, for each weight/bias:
 - the gradient is calculated based on $y(\tau)$ and the corresponding values in the dense input buffer and output buffer;
 $$g_w(\tau,s,t)\leftarrow\frac{\partial \mathcal{L}(\tau)}{\partial w(\tau, s, t)}=x(\tau,t)\left(\text{softmax}(\tau, s)-\mathbb{I}(y(\tau)=s)\right)$$
 $$g_b(\tau,s)\leftarrow\frac{\partial \mathcal{L}(\tau)}{\partial b(\tau, s)}=\text{softmax}(\tau, s)-\mathbb{I}(y(\tau)=s)$$
 - the gradient is used to update the corresponding element in the weight increments buffer, which stores the momentum-based exponential moving average of the gradients;
 $$\boldsymbol{i}_w(\tau)\leftarrow\mu \boldsymbol{i}_w(\tau-1)+\boldsymbol{g}_w(\tau)$$
 $$\boldsymbol{i}_b(\tau)\leftarrow\mu \boldsymbol{i}_b(\tau-1)+\boldsymbol{g}_b(\tau)$$
 - the weight/bias is updated by subtracting the product of the learning rate and the increment;
 $$\boldsymbol{w}(\tau)\leftarrow\boldsymbol{w}(\tau-1)-\gamma \boldsymbol{i}_w(\tau)$$
 $$\boldsymbol{b}(\tau)\leftarrow\boldsymbol{b}(\tau-1)-\gamma \boldsymbol{i}_b(\tau)$$
($s$ and $t$ are the group index and the within-group index of the weights, while $\mu$ and $\gamma$ are the momentum and learning rate)
4. MCU transmits the predicted label to PC.
### STM32 Project
The STM32 project for each of the three datasets can be found under `stm32_nucleo_f756zg` directory.
#### Online Training Engine
Source code of the engine can be found in 
- `stm32_nucleo_f756zg/nucleo-f756zg-ai_xxx/Core/Inc/online_training.h`
- `stm32_nucleo_f756zg/nucleo-f756zg-ai_xxx/Core/Src/online_training.c`

The macro definitions for `OT_CLASSIFIER_IN_SIZE` and `OT_CLASSIFIER_OUT_SIZE` are different in the three projects, as the size of the samples and the number of classes to be classified are different in the three datasests.

APIs:
- ot_init()
> void ot_init(float ot_lr_, float ot_momentum_);

This function copies the weights of the classifier into SRAM, registers the callback function that retrieves the input to the dense layer and initializes the increments buffer, learning rate and momentum, which should be called after network initialization and before inference. `ot_lr_` parameter is the designated learning rate and `ot_momentum_` is the designated momentum.
- ot_update()
> void ot_update(void);

This function updates all the weights and biases of the classifier, which should be called after inference.
### Performance Evaluation
Random seed is used to ensure that both the dataset splitting and the input order of the online training data are the same for the on-MCU method and the PyTorch-based method. The following shows the results of online training when the valid-online training (nonuser) splitting is **not** applied, which means that full validation datasets are used during offline trainings.
#### Gym Dataset (OUTDATED)
lr=0.002, momentum=0.9, 1 epoch of online training using user samples.
<p align="center"><img width="863" alt="Screenshot 2023-08-23 at 19 58 17" src="https://github.com/kangpx/onlineTiny2023/assets/118830544/e41b74af-2212-4159-9569-d79270648dd5"></p>

#### QVAR Dataset (OUTDATED)
lr=0.002, momentum=0.5, 5 epoches of online training using user samples.
<p align="center"><img width="863" alt="Screenshot 2023-08-23 at 20 27 15" src="https://github.com/kangpx/onlineTiny2023/assets/118830544/077569be-8c37-4887-893c-585bc67d0032"></p>


#### Ultra Dataset (OUTDATED)
lr=0.002, momentum=0.5, 1 epoch of online training using user samples.
<p align="center"><img width="847" alt="Screenshot 2023-08-22 at 21 55 58" src="https://github.com/kangpx/onlineTiny2023/assets/118830544/2be303bc-6cd8-48c8-b6cb-9e4c71a786ed"></p>

## Online Training on GAP9
### Work Flow
<p align="center"><img width="645" alt="Screenshot 2023-09-19 at 15 36 38" src="https://github.com/kangpx/onlineTiny2023/assets/118830544/e1d7a862-ea06-4c45-a1ae-9cb1e05c4f53"></p>

The work flow is quite similar to that on STM32, except that:

1. The triplet is transferred to GVSOC through bridge funtion that reads files from host PC;
2. The newly introduced buffers for online-training should be first transferred from L2- to L1-Memory through DMA before the clusters could process the update, and that the updated buffers should be transferred back to L2-Memory after the process;
3. Instead of allocating an independent place for the dense input buffer as in the STM32 projects, the dense input buffer is part of the activation buffer in L2-Memory;
4. Input and output buffers are independently allocated instead of being part of the activation buffer as in the STM32 projects.

### Project
The three datasets' projects are uploaded and can be found under (`gap9`).

#### Online Training Engine
Source code of the engine can be found in 
- `gap9/xxx/online_training.h`
- `gap9/xxx/online_training.c`

APIs:
- ot_init_chunk()
> int ot_init_chunk(void);

This function allocates a piece of dynamic L1-memory for online training, initilizes the buffer pointers and resets the w/b increment cache to all zeros. Returns -1 if failed to allocate L1-memory otherwise 0. This funtion should be called after the network initialization and before online training.

- ot_clean_chunk()
> void ot_clean_chunk(void);

This function frees the dynamic L1-memory allocated in `ot_init_chunk()`.

- ot_update_chunk_parallel()
> void ot_update_chunk(void);

Update funtion for the case where multi-clusters are used and the w/b icrement caches & output buffers are transferred between L2- and L1-memory and updated in chunks.

**"chunk" here means that w/b increment buffers and output buffers in L2-memory can be divided into equal-length chunks, which are transferred to L1-memory and updated one by one during online training. Default chunk number is 1 for all the three datastes.**

#### Run the Project
To run the project (taking ultra project as example):
1. Setup necessary environments:
 >cd xxx/gap_sdk_private-master && source sourceme.sh && conda activate gap
2. Run NNTool script to generate ATmodel, which should generate the file `UltraModel.c`:
 >python nntool_script_ultra.py --mode=generate_at_model --trained_model PRE_TRAINED_MODEL_PATH_OF_FOLD_X
3. Specify the value of current fold in Ultra.h:
"#define FOLD X" at line 22
4. Cmake build to generate C-kernels, compile and run the code:
>cmake -B build

>cmake --build build --target run

5. Clean up.
>rm -rf build

>rm *.tensor

### Performance Evaluation
#### Ultra Dataset
lr=0.002, momentum=0.5, 1 epoch of online training using user samples, full validation during pre-training. 

fastexp with underflow check:
<p align="center"><img width="472" alt="Screenshot 2023-12-16 at 17 28 36" src="https://github.com/kangpx/onlineTiny2023/assets/118830544/f020572b-7395-43db-a475-111ef5de7ca7"></p>


#### Qvar Dataset
lr=0.002, momentum=0.5, 5 epoches of online training using user samples, full validation during pre-training.

fastexp with underflow check:
<p align="center"><img width="464" alt="Screenshot 2023-12-16 at 17 29 04" src="https://github.com/kangpx/onlineTiny2023/assets/118830544/6e1afc1b-4f46-4405-8f06-a0fb028d6860"></p>


#### Gym Dataset
lr=0.002, momentum=0.9, 1 epoch of online training using user samples, full validation during pre-training.
<p align="center"><img width="467" alt="Screenshot 2023-12-15 at 15 09 16" src="https://github.com/kangpx/onlineTiny2023/assets/118830544/a0dcc5f1-f9f1-4742-9594-29e4b04260bb"></p>



## Reference
- [1] [S. Bian, X. Wang, T. Polonelli and M. Magno, "Exploring Automatic Gym Workouts Recognition Locally on Wearable Resource-Constrained Devices," 2022 IEEE 13th International Green and Sustainable Computing Conference (IGSC), Pittsburgh, PA, USA, 2022, pp. 1-6, doi: 10.1109/IGSC55832.2022.9969370.](https://ieeexplore.ieee.org/abstract/document/9969370)
