---
layout: default
<!--<center> $$ \tag {}$$ </center> -->
---

## <center> 批正则化原理 </center>


## <center> 实际Batch Normalization正确落地姿势 </center>

 在工业产品中使用bn层，并不如tf所展现的那样简介。需要注意两个问题
 1. 确保在执行optimizer更新梯度前执行均值/方差的滑动窗口更新
 2. 在部署线上服务时，要主动将均值与方差全部保存下来，确保拿到正确的均值方差

参考resnet给出的bn层使用方法
 '''python
 def _build_graph(self):
	 ...
	 _extra_train_ops = []
	 ...
   # 此处在执行中使用tf.group强制生产依赖，确保在执行apply_op的同时能够执行滑动窗口的更新
	 train_ops = [apply_op] + _extra_train_ops
	 train_op = tf.group(*train_ops)

 def _batch_norm(self, name, x):
  """Batch normalization."""
  with tf.variable_scope(name):
    params_shape = [x.get_shape()[-1]]

    # beta: scale, gamma: shape
    beta = tf.get_variable(
        'beta', params_shape, tf.float32,
        initializer=tf.constant_initializer(0.0, tf.float32))
    gamma = tf.get_variable(
        'gamma', params_shape, tf.float32,
        initializer=tf.constant_initializer(1.0, tf.float32))

    if self.mode == 'train':
      mean, variance = tf.nn.moments(x, [0, 1, 2], name='moments')

      # 这里因为每一个nueron都会对应一个mu和sigma，所以shape为输入的shape
      # 这里均值初始化为0，方差初始化为1，且设置二者trainable=False
      moving_mean = tf.get_variable(
          'moving_mean', params_shape, tf.float32,
          initializer=tf.constant_initializer(0.0, tf.float32),
          trainable=False)
      moving_variance = tf.get_variable(
          'moving_variance', params_shape, tf.float32,
          initializer=tf.constant_initializer(1.0, tf.float32),
          trainable=False)

      self._extra_train_ops.append(moving_averages.assign_moving_average(
          moving_mean, mean, 0.9))
      self._extra_train_ops.append(moving_averages.assign_moving_average(
          moving_variance, variance, 0.9))
    else:
      mean = tf.get_variable(
          'moving_mean', params_shape, tf.float32,
          initializer=tf.constant_initializer(0.0, tf.float32),
          trainable=False)
      variance = tf.get_variable(
          'moving_variance', params_shape, tf.float32,
          initializer=tf.constant_initializer(1.0, tf.float32),
          trainable=False)
      tf.summary.histogram(mean.op.name, mean)
      tf.summary.histogram(variance.op.name, variance)
    # epsilon used to be 1e-5. Maybe 0.001 solves NaN problem in deeper net.
    y = tf.nn.batch_normalization(
        x, mean, variance, beta, gamma, 0.001)
    y.set_shape(x.get_shape())
    return y
 '''

 参考mnist使用bn层的一个case
 ''' python
		conv1 = tf.layers.conv2d(image, filters=32, kernel_size=[3, 3], strides=[1, 1], padding='same',
                             activation=tf.nn.relu,
                             kernel_initializer=tf.truncated_normal_initializer(stddev=0.1),
                             name='conv1')
    bn1 = tf.layers.batch_normalization(conv1, training=phase, name='bn1')
    pool1 = tf.layers.max_pooling2d(bn1, pool_size=[2, 2], strides=[2, 2], padding='same', name='pool1')
    conv2 = tf.layers.conv2d(pool1, filters=64, kernel_size=[3, 3], strides=[1, 1], padding='same',
                             activation=tf.nn.relu,
                             kernel_initializer=tf.truncated_normal_initializer(stddev=0.1),
                             name='conv2')
    bn2 = tf.layers.batch_normalization(conv2, training=phase, name='bn2')
    pool2 = tf.layers.max_pooling2d(bn2, pool_size=[2, 2], strides=[2, 2], padding='same', name='pool2')
		....
    # 在执行前，先建立control_dependices
		update_ops = tf.get_collection(tf.GraphKeys.UPDATE_OPS)
	  with tf.control_dependencies(update_ops):
        grads = opt.compute_gradients(cross_entropy)
        train_op = opt.apply_gradients(grads, global_step=global_step)

		# 保存时采用主动保存
    var_list = tf.trainable_variables()
    if global_step is not None:
        var_list.append(global_step)
    g_list = tf.global_variables()
    bn_moving_vars = [g for g in g_list if 'moving_mean' in g.name]
    bn_moving_vars += [g for g in g_list if 'moving_variance' in g.name]
    var_list += bn_moving_vars
    saver = tf.train.Saver(var_list=var_list,max_to_keep=5)

    # save all variables
    # saver = tf.train.Saver(max_to_keep=5)

 '''

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
