---
layout: default
<!--<center> $$ \tag {}$$ </center> -->
---

## <center> 批正则化原理 </center>

### CIS问题

### bn基本原理
批正则化定义如下:

<center> $$ y = \gamma \frac{x - \mu}{\sqrt{\sigma^2 + \epsilon}} + \beta \tag {1}$$ </center>

其中$$\mu$$为当前batch基于**每一列**的均值，$$\sigma$$为基于**每一列**的标准差，即：

<center> $$ \mu = \frac{1}{n} \sum_{i=1}^{n} x_i \tag {2}$$ </center>

<center> $$ \sigma^2 = \frac{1}{n} \sum_{i=1}^{n} (x_i - \mu)^2\tag {3}$$ </center>

其中$$\gamma$$和$$\beta$$为trainable=True即在训练中会基于梯度回传来更新，而$$\mu$$, $$\sigma$$为计算结果，一般
在实际使用中分为训练阶段和服务阶段，训练阶段通过moving_average来更新这两个值，而服务阶段需要保存该两个值
确保能够拿到训练样本的累积平均均值和方差，一般服务时mini-batch也不同，出于性能考虑，一般多为1

### bn梯度计算与更新


## <center> 实际Batch Normalization正确落地姿势 </center>

 在工业产品中使用bn层，并不如tf所展现的那样简介。需要注意两个问题
 1. 确保在执行optimizer更新梯度前执行均值/方差的滑动窗口更新
 2. 在部署线上服务时，要主动将均值与方差全部保存下来，确保拿到正确的均值方差

参考resnet给出的bn层使用方法
```python
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
```

 参考mnist使用bn层的一个case
 ```python
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
```
