---
layout: default
<!--<center> $$ \tag {}$$ </center> -->
---

## <center> 机器学习评价指标  </center>

### AUC以及ROC

```python
def roc(datas, pos, neg):
    datas = sorted(datas, key = lambda x: x[0], reverse = True)

    tp = 0
    fp = 0

    roc_arr = []
    for sample in datas:
        tp += (1 if sample[1] == 1 else 0)
        fp += (1 if sample[1] == 0 else 0)
        roc_arr.append((fp/neg, tp/pos))

    return roc_arr

def auc(pctrs, labels):
    pos = np.sum(labels)
    neg = len(labels) - pos

    # roc curve
    roc_arr = roc((pctrs, labels), pos, neg)

    # area under roc curve
    area = 0.
    prev_coord = (0, 0)
    for coord in roc_arr:
        area += (coord[0] - prev_coord[0]) * coord[1]
        prev_coord = coord

    return area

```
