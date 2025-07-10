import numpy as np
import Orange
from Orange.data import Domain, ContinuousVariable

val = 0
for i in range(in_data.n_rows):
    print(val)
    val += in_data[i].x[0]*in_object[0].x[i]
out_data = Orange.data.Table.from_numpy(Domain([ContinuousVariable("linear_regression_eval")]), X=np.array([[val]]))