# onlineTiny2023
 
## Python
3.9.12
## PyTorch
1.12.0
## Datasets
- Gym https://www.kaggle.com/datasets/zhaxidelebsz/10-gym-exercises-with-615-abstracted-features
- QVAR from PBL
- Ultra https://github.com/kangpx/40khz-ultrasonicDHGR-onlineSemi
## Online training on STM32 nucleo-f756zg
### X-CUBE-AI
MacArm 8.1.0
### Working flow
![ot_on_nucleo-f756zg](https://github.com/kangpx/onlineTiny2023/assets/118830544/2e0a23cd-2673-4225-b93e-e99a41908b83)
1. PC transmits a triplet ($x_t$, $y_t$, $\text{flag}_t$) to MCU through UART, where $x_t$ is the input data, $y_t$ is the input label and $\text{flag}_t$ is the trigger signal for online training;
2. X-CUBE-AI's inference engine performs the inference, during which the input to the last fully connected layer (classifier) is retrieved by a registered callback of platform observer and dumped into the dense input buffer, while the inference output (i.e., the output of the softmax layer) is dumped into the output buffer;
3. If online training is triggered ($\text{flag}_t$==1) in this round, the implemented online training engine traverses the weights/biases of the classifier, for each weight/bias:
 - the gradient is calculated based on &y_t& and the corresponding values in the dense input buffer and output buffer;

$$
\frac{\partial L}{\partial \omega_{s}^{t}} = x^t\left(\frac{e^{\boldsymbol{\omega}_s\cdot \boldsymbol{x}+b_{s}}}{\sum\limits_{i=1}^{C}{e^{\boldsymbol{\omega}_i\cdot\boldsymbol{x}+b_{i}}}}-I_{\{y=s\}}\right)
=x^t\left(\text{softmax}(\boldsymbol{W}\boldsymbol{x}+\boldsymbol{b})_s-I_{\{y=s\}}\right)
$$

$$
\omega_{s}^{t}(\tau+1)=\omega_{s}^{t}(\tau)-\eta\frac{\partial L}{\partial \omega_{s}^{t}}=\omega_{s}^{t}(\tau)-\eta x^t\left(\text{softmax}(\boldsymbol{W}\boldsymbol{x}+\boldsymbol{b})_s-I_{\{y=s\}}\right)
$$

 - the gradient is used to update the corresponding element in the weight increments buffer, which stores the momentum-based exponential moving average of the gradients;
 - the weight/bias is updated by subtracting the product of the learning rate and the increment;
4. MCU transmits the predicted label to PC.
