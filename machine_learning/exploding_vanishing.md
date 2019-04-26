---
layout: default
---

# <center> 梯度爆炸/消失的原因及解决方法 </center>

## 梯度消失与梯度爆炸

## 使用xavier和he initialization来解决梯度消失

xavier在参数初始化中，一般采用truncate_normal正太分布来初始化，其中均值为0，方差为:

<center> $$Var(\omega_i) = \frac{1}{fan\_in} \quad (1)$$  </center>

or

<center> $$Var(\omega_i) = \frac{1}{fan\_in + fan\_out} \quad (2)$$  </center>

其中fan_in为输入层的神经元个数, fan_out为输出层神经元个数,其中(1)多适用于tanh激活函数，(2)多使用与sigmoid函数




## mnist数据集中xavier和normal的比较
