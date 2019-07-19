---
layout: default
<!--<center> $$ \tag {}$$ </center> -->
---

## <center> On Policy to Off Policy</center>
> 当agent直接与environment进行交互获取action，reward时为On Policy，而当agent使用的trajectory是由另一个agent
> 产生的，这个时候即为Off Policy。在算法上，On Policy的样本生成后仅能使用一次，因为模型的参数会被环境依赖。而Off Policy
> 不存在该问题，因而可以多次使用另一个模型(policy)生成的样本来训练并使得参数收敛，相对来看能够省去大量样本生成过程。

### importance sampling以及存在的问题与应对
当从一个分布$$p(x)$$中采样样本$$x^i$$时，可表述为如下。

而当我们拿不到该分布时，可以使用其他分布来描述，这就是Off Policy产生的数学基础，

该表示方法采样中因为引入了系数，则即使存在相同的期望，但他们的方差并不相同，因而无论是后面的TRPO还是PPOs都设法去消除该转换带来的Variant差异,
如下证明了差异的对比


## <center> PPO, TRPO, PPO2 </center>

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

