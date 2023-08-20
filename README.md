# onlineTiny2023
 
## Python
3.9.12
## PyTorch
1.12.0
## Datasets
- Gym https://www.kaggle.com/datasets/zhaxidelebsz/10-gym-exercises-with-615-abstracted-features
- QVAR from PBL
- Ultra https://github.com/kangpx/40khz-ultrasonicDHGR-onlineSemi
## Saved models
The three datasets' pre-trained models of each fold (leave-one-user-out) formatted in .pt and .onnx are stored under the the directory `saved_models`. For .pt models, backbone and classifier are stored seperately. For .onnx models, the backbone and classifier are combined before being saved.
## Online Training on STM32 Nucleo-F756ZG
### X-CUBE-AI
MacArm 8.1.0
### Work Flow
<p align="center"><img src="https://github.com/kangpx/onlineTiny2023/assets/118830544/2e0a23cd-2673-4225-b93e-e99a41908b83" width="60%"></p>

1. PC transmits a triplet ($x(\tau)$, $y(\tau)$, $\text{flag}(\tau)$) to MCU through UART, where $x(\tau)$ is the input data, $y(\tau)$ is the input label and $\text{flag}(\tau)$ is the trigger signal for online training;
2. X-CUBE-AI's inference engine performs the inference, during which the input to the last fully connected layer (classifier) is retrieved by a registered callback of platform observer and dumped into the dense input buffer, while the inference output (i.e., the output of the softmax layer) is dumped into the output buffer;
3. If online training is triggered ($\text{flag}(\tau)$==1) in this round, the implemented online training engine traverses the weights/biases of the classifier, for each weight/bias:
 - the gradient is calculated based on $y_t$ and the corresponding values in the dense input buffer and output buffer;
 $$g_w(\tau,s,t)\leftarrow\frac{\partial L}{\partial w(\tau, s, t)}=x(\tau,t)\left(\text{softmax}(\tau, s)-\mathbb{I}(y(\tau)=s)\right)$$
 $$g_b(\tau,s)\leftarrow\frac{\partial L}{\partial b(\tau, s)}=\text{softmax}(\tau, s)-\mathbb{I}(y(\tau)=s)$$
 - the gradient is used to update the corresponding element in the weight increments buffer, which stores the momentum-based exponential moving average of the gradients;
 $$\boldsymbol{i}_w(\tau)\leftarrow\mu \boldsymbol{i}_w(\tau-1)+\boldsymbol{g}_w(\tau)$$
 $$\boldsymbol{i}_b(\tau)\leftarrow\mu \boldsymbol{i}_b(\tau-1)+\boldsymbol{g}_b(\tau)$$
 - the weight/bias is updated by subtracting the product of the learning rate and the increment;
 $$\boldsymbol{w}(\tau)\leftarrow\boldsymbol{w}(\tau-1)-\gamma \boldsymbol{i}_w(\tau)$$
 $$\boldsymbol{b}(\tau)\leftarrow\boldsymbol{b}(\tau-1)-\gamma \boldsymbol{i}_b(\tau)$$
($\mu$ and $\gamma$ are momentum and learning rate, respectively.)
4. MCU transmits the predicted label to PC.
### STM32 project
The uploaded project is for ultra dataset. 
#### Online training engine
Source code of the engine can be found in 
- `onlineTiny2023/stm32_nucleo_f756zg/nucleo-f756zg-ai_ultra/Core/Inc/online_training.h`
- `onlineTiny2023/stm32_nucleo_f756zg/nucleo-f756zg-ai_ultra/Core/Src/online_training.c`

The APIs include:
- ot_init()
> void ot_init(float ot_lr_, float ot_momentum_);

This function copies the weights of the classifier into SRAM, registers the callback function that retrieves the input to the dense layer and initializes the increments buffer, learning rate and momentum, which should be called after network initialization and before inference. `ot_lr_` parameter is the designated learning rate and `ot_momentum_` is the designated momentum.
- ot_update()
> void ot_update(void);

This function updates all the weights and biases of the classifier, which should be called after inference.

