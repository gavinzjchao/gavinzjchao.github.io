---
layout: default
<!--<center> $$ \tag {}$$ </center> -->
---

## <center> Policy Gradient </center>

> policy gradient目标是使得policy($$\pi$$)的长期期望收益最大化即 maximum long-term expected reward,
> 训练中样本为state，probability action， action，其中state可以是flattern图像，或其他特征，probability action为$$\pi$$网络
> 拟合函数输出的softmax结果， action为样本生成中获得的实际值。

定义一个trajectory为一组(state, action)集合，即
<center>  $$ trajectory\  \tau = \{s_1, a_1, s_2, a_2, ... s_n, a_n\} $$</center>

则在给定的policy下获取一种trajectory的概率，表示为：
<center> $$ \rho_\theta(\tau) = p(s_1)p_\theta(a_1|s_1)p(s_2|s_1, a_1, \pi)...p(a_n|s_n)p(s_n+1|s_n, a_n, \pi) $$ </center>

因为我们关注的是长期期望收益最大化，因而reward定义如下：
<center> $$ R(\tau) = \sum_{t = 1}^{T} r_t $$ </center>

进而得到目标函数定义，其中采用期望收益最大化不易计算，因而一般采用采样来近似表示期望收益:
<center> $$ \bar{R(\tau)} = \sum_{\tau}R(\tau)  p_\theta(\tau)$$ </center>

对reward的梯度有:

  $$ \bigtriangledown \bar{R(\tau)} = \bigtriangledown \sum_{\tau} R(\tau) p_\theta(\tau) \\
		= \sum_{\tau} R(\tau) p_\theta(\tau) \frac{\bigtriangledown p_\theta(\tau)}{p_\theta(\tau)} \\
		= E_\theta~p_\theta(\tau) [\sum_{\tau} R(\tau) \bigtriangledown log p_\theta(\tau)]
	$$

其中，因为对数的导数等于该数的导数, 又因为期望等于发生该事件的概率乘以该事件，因而
可以将多出的$$ p_\theta(\tau) $$引入到期望表达式内。

又根据一次trajectory发生概率的表达式求对数有如下：

<center> $$ \bigtriangledown p_\theta(\tau) = \bigtriangledown log p(s_1) + \sum_{t = 1}^{T} \bigtriangledown log p_\theta(a_t|s_t) + \sum_{t=1}^{T} \bigtriangledown  log p(s_{t+1}|s_t, a_t, \pi) $$ </center>

消除与$$\theta$$无关的常数项，仅剩下中间的项，同时对期望的梯度无法表示，因而可以采用采样的方式来生成多个episode进而求平均值获取最终结果，如下：

<center> $$ \bigtriangledown \bar{R(\tau)} =  \frac{1}{N} \sum_{n = 1}^{N} \sum_{t = 1}^{T_n} R(\tau^n) \bigtriangledown log p_\theta(a_t|s_t) $$ </center>


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
