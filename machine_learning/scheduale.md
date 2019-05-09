---
layout: default
<!--<center> $$ \tag {}$$ </center> -->
---

## <center> DNN/RNN/CNN/DQN原理，模型调优，超参调节，特征工程汇总 </center>

### DNN/RNN/CNN/DQN原理
1. naive DNN, RNN, CNN
2. DQN
3. bp, bptt
4. gradient exploding or vanishing
5. LSTM(bidirection, deep), GRU
6. W&D, Youtube Matching, DCN, DIN, ESMM, DIEN, DeepFM, XDeepFM
7. LeNet, ResNet, Inception, AlexNet, ...
8. W2V, FastText, Seq2Seq


### 模型调优
- initialization
	- truncate normal
	- xavier
	- he initialization

- normalization
	- batch normalization
	- layer normalization

- regularization
	- L1 or L2 regularization
	- elastic(L1 and L2) regularization

- clip values
	- gradient clip (by norm, by global, by value...)
	- weight clip

- activation
	- sigmoid
	- relu or relu6
	- parameterize relu or leaky relu
	- elu
	- dice
	- swish

- optimizition
	- naive sgd
	- momentum or nesterov
	- rmsprop or adam or nadam
	- TGD or RDA or FOBOS or FTRL

- tricks
	- dropout
	- early stop
	- learning rate decay

- metrics
	- AUC, GroupAUC
	- F1 
	- ND..

### 超参调节

### 特征工程
- embedding
	- average/max/sum pooling
	- hierarchical pooling
	- cnn/causal for nlp
	- attention or DIN
