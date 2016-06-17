Solution taken from [this comments](https://apps.topcoder.com/forums/?module=Thread&threadID=680416&mc=26&view=threaded#1262672):

* inv(1) = 1
* inv(x) = -(P / x) * inv(P % x) for x > 1

Results for 1.000.000.007:

Measurement | Value
------------|------
MAX | 50
AVG | 21

