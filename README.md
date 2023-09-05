# onlineTiny2023
 
## Python
3.9.12
## PyTorch
1.12.0
## Datasets
- Gym https://www.kaggle.com/datasets/zhaxidelebsz/10-gym-exercises-with-615-abstracted-features
- QVAR from PBL
- Ultra https://github.com/kangpx/40khz-ultrasonicDHGR-onlineSemi
## Saved Models
The model topology is from [1] and shown in the following figure:
<p align="center"><img width="310" alt="Screenshot 2023-08-20 at 22 27 59" src="https://github.com/kangpx/onlineTiny2023/assets/118830544/ab6f4c5d-2c19-4714-888c-034a19d46240"></p>

The three datasets' pre-trained models of each fold (leave-one-user-out) formatted in .pt and .onnx are stored under the the directory `saved_models`. For .pt models, backbone and classifier are stored seperately. For .onnx models, the backbone and classifier are combined before being saved.
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
#### Gym Dataset
lr=0.002, momentum=0.9, 1 epoch of online training using user samples.
<p align="center"><img width="863" alt="Screenshot 2023-08-23 at 19 58 17" src="https://github.com/kangpx/onlineTiny2023/assets/118830544/e41b74af-2212-4159-9569-d79270648dd5"></p>

#### QVAR Dataset
lr=0.002, momentum=0.5, 5 epoches of online training using user samples.
<p align="center"><img width="863" alt="Screenshot 2023-08-23 at 20 27 15" src="https://github.com/kangpx/onlineTiny2023/assets/118830544/077569be-8c37-4887-893c-585bc67d0032"></p>


#### Ultra Dataset
lr=0.002, momentum=0.5, 1 epoch of online training using user samples.
<p align="center"><img width="847" alt="Screenshot 2023-08-22 at 21 55 58" src="https://github.com/kangpx/onlineTiny2023/assets/118830544/2be303bc-6cd8-48c8-b6cb-9e4c71a786ed"></p>

## Online Training on GAP9
### Work Flow
<p align="center"><img width="677" alt="ot_on_gap9" src="https://github.com/kangpx/onlineTiny2023/assets/118830544/93ca3f87-3fc4-4f4e-9495-4ffb69de4c11"></p>
The work flow is quite similar to that on STM32, except that:

1. The triplet is transferred to GVSOC through bridge funtion that reads files from host PC;
2. The newly introduced buffers for online-training should be first transferred from L2- to L1-Memory through DMA before the clusters could process the update, and that the updated buffers should be transferred back to L2-Memory after the process;
3. Instead of allocating an independent place for the dense input buffer as in the STM32 projects, the dense input buffer is part of the activation buffer in L2-Memory;
4. Input and output buffers are independently allocated instead of being part of the activation buffer as in the STM32 projects.

### Project
The project for ultra dataset is uploaded (`gap9/ultra`).

#### Online Training Engine
Source code of the engine can be found in 
- `gap9/ultra/online_training.h`
- `gap9/ultra/online_training.c`

APIs:
- ot_init()
> void ot_init(void);

This function allocates a piece of dynamic L1-memory for online training, initilizes the buffer pointers and resets the w/b increment cache to all zeros. This funtion should be called after the network initialization and before online training.

- ot_update()
> void ot_update(void);

This function manages the transfer of the needed buffers between L2- and L1 memory and updates the weights/biases of the classifier. This function should be called after `ot_init()`.

- ot_clean()
> void ot_clean(void);

This function frees the dynamic L1-memory allocated in `ot_init()`.
 
#### Run the Project
To run the project:
1. Setup necessary environments:
 >cd xxx/gap_sdk_private-master && source sourceme.sh && conda activate gap
2. Run NNTool script to generate ATmodel, which should generate the file `UltraModel.c`:
 >python nntool_script_ultra.py --mode=generate_at_model --trained_model PRE_TRAINED_MODEL_PATH
3. Fix some bugs in `UltraModel.c`: add `tensors/` as prefix to each path to the tensor files, e.g., at line 135:
 change `...ConstInfo("Conv_0_weights.tensor", 1, ...` to `...ConstInfo("tensors/Conv_0_weights.tensor", 1, ...`

where `tensors` is the directory designated in the NNTool script to store the tensors, it is ignored in the generated ATModel due to some unknown reason.

4. Run AutoTiler to generate executable network on GAP9:
>make clean
>make GenUltra
>./GenUltra

5. Compile and run the code on GVSOC.
>make all run platform=gvsoc

### Performance Evaluation
#### Ultra Dataset
lr=0.002, momentum=0.5, 1 epoch of online training using user samples, full validation during pre-training. Note that fold-2 and fold-3 report the performance of the re-generated pre-trained models(`saved_models/ultra/onnx/fold_2_pre_combination_fullvalid_x.onnx` and `saved_models/ultra/onnx/fold_3_pre_combination_fullvalid_x.onnx`), and there are meltdowns associated with the old ones (`saved_models/ultra/onnx/fold_2_pre_combination_fullvalid.onnx` and `saved_models/ultra/onnx/fold_3_pre_combination_fullvalid.onnx`).
<p align="center"><img width="871" alt="Screenshot 2023-09-05 at 10 10 38" src="https://github.com/kangpx/onlineTiny2023/assets/118830544/6f29c22d-5c83-45aa-81b5-bd8407e3489e"></p>
lr=0.002, momentum=0.5, 1 epoch of online training using user samples, part validation during pre-training.
<p align="center"><img width="869" alt="Screenshot 2023-09-05 at 10 12 11" src="https://github.com/kangpx/onlineTiny2023/assets/118830544/ada79700-6b8d-4615-9cff-b04538e90e2e"></p>

## Reference
- [1] [S. Bian, X. Wang, T. Polonelli and M. Magno, "Exploring Automatic Gym Workouts Recognition Locally on Wearable Resource-Constrained Devices," 2022 IEEE 13th International Green and Sustainable Computing Conference (IGSC), Pittsburgh, PA, USA, 2022, pp. 1-6, doi: 10.1109/IGSC55832.2022.9969370.](https://ieeexplore.ieee.org/abstract/document/9969370)
