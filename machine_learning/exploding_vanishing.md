---
layout: default
<!--<center> $$ \tag {}$$ </center> -->
---

# <center> 梯度爆炸/消失的原因及解决方法 </center>

## 梯度消失与梯度爆炸

## 使用xavier和he initialization来解决梯度消失

xavier在参数初始化中，一般采用truncate_normal正太分布来初始化，其中均值为0，方差为:

<center> $$Var(\omega_i) = \frac{1}{fan\_in} \tag {1}$$  </center>

或者：

<center> $$Var(\omega_i) = \frac{1}{fan\_in + fan\_out} \tag {2}$$  </center>

其中fan_in为输入层的神经元个数, fan_out为输出层神经元个数,其中(1)多适用于tanh激活函数，(2)多使用于sigmoid函数. 令网络的input层有n个节点，则有

<center>  $$Y = \omega_1\,x_1 + \omega_2\,x_2 + ... + \omega_n\,x_n \tag {3} $$</center>

又根据方差计算公式，可知:

<center> $$Var(XY) = E[X^2]Var(Y) + E[Y^2]Var(X) + Var(X)Var(Y)  \tag {4}$$ </center>

假定输入的所有节点的mean = 0，则有：

<center> $$Var(\omega_i\,x_i) = Var(\omega_i)Var(x_i) \tag {5}$$ </center>

又已知方差的和等于和的方差，且假定输入节点服从独立同分布i.i.d，则有：

<center> $$ Var(\sum_{i=1}^{n} X_i) = \sum_{i=1}^{n} Var(X_i) \tag {6}$$ </center>

可以得到：

<center> $$ Var(Y) = nVar(\omega)Var(x) \tag {7}$$ </center>

如果希望Var(Y) = 1,那么有：

<center> $$ Var(\omega) = \frac{1}{n} = \frac{1}{fan\_in} \tag {8}$$ </center>





## mnist数据集中xavier和normal的比较
