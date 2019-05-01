---
layout: default
<!--<center> $$ \tag {}$$ </center> -->
---

## <center> 梯度消失或爆炸的原因和调优方 </center>


## <center> 使用Xavier/He Initialization减缓梯度消失问题 </center>

### 原理与证明

> In xavier we need the variance of the
> outputs of each layer to be equal to the variance of its inputs, and we also need the
> gradients to have equal variance before and after flowing through a layer in the
> reverse direction

xavier在参数初始化中，一般采用truncate_normal正太分布来初始化，其中均值为0，方差为:

<center> $$Var(\omega_i) = \frac{1}{fan\_in} \tag {1}$$  </center>

或者：

<center> $$Var(\omega_i) = \frac{2}{fan\_in + fan\_out} \tag {2}$$  </center>

或者：

<center> $$Var(\omega_i) = \frac{2}{fan\_in} \tag {3}$$ </center>

其中fan_in为输入层的神经元个数, fan_out为输出层神经元个数,其中(1)多适用于tanh激活函数，(2)多使用于sigmoid函数 (3)
多用于relu激活函数. 
证明如下, 令网络的input层有n个节点，则有:

<center>  $$Y = \omega_1\,x_1 + \omega_2\,x_2 + ... + \omega_n\,x_n \tag {3} $$</center>

又根据方差计算公式，可知:

<center> $$Var(XY) = E[X^2]Var(Y) + E[Y^2]Var(X) + Var(X)Var(Y)  \tag {4}$$ </center>

假定输入的所有节点的mean = 0，则有$$E[X^2] = E[Y^2] = 0$$化简后得：

<center> $$Var(\omega_i x_i) = Var(\omega_i)Var(x_i) \tag {5}$$ </center>

又已知方差的和等于和的方差，且假定输入节点服从独立同分布i.i.d，则有：

<center> $$ Var(\sum_{i=1}^{n} X_i) = \sum_{i=1}^{n} Var(X_i) \tag {6}$$ </center>

联合(5), (6)可以得到：

<center> $$ Var(Y) = nVar(\omega)Var(x) \tag {7}$$ </center>

如果希望Var(Y) = Var(X), 那么有：

<center> $$ Var(\omega) = \frac{1}{n} = \frac{1}{fan\_in} \tag {8}$$ </center>


### xavier 实现

```python
import numpy as np
import tensorflow as tf

np.random.seed(42)

input_size = 128
output_size = 64

#xavier with normal distribution
mu = 0.
sigma = np.sqrt(2. / (input_size + output_size)) 
w = sigma * np.random.randn(input_size, output_size) + mu

# tensorflow usage
tf.contrib.layers.variance_scaling_initializer(factor=1.0, mode='FAN_AVG', uniform=False, seed=None, dtype=tf.float32)
```

## mnist数据集中xavier和normal的比较
