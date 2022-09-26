# VSB
Cardinality estimation is the task of obtaining the number of distinct items in a
data stream, which plays an important role in many application domains, such as 
traffic monitoring, recommendation system and query optimization in database.
However, when dealing with high-speed data streams, it remains a significant challenge
to estimate cardinality considering record/query overhead and memory-efficiency.
This repository introduces an online cardinality estimator, called Virtual Self-adaptive
Bitmap (VSB). VSB automatically adapts its sampling probabaility to different stream sizes
by logically adding virtual bits.

we compare VSB to existing cardinality estimators including LogLog, HyperLogLog,
HyperLogLog++, HyperLogLog-Tailcut, FM, MRB, and SMB.


## File
- LL/. the implementation of LL estimator
- HLL/. the implementation of HLL estimator
- hllp_card/. the implementation of hll++ estimator
- MRB/. the implementation of MRB estimator
- SMB/. the implementation of SMB estimator
- VSA/. the implementation of VSB estimator
- PCSA/. the implementation of PCSA (also called FM) estimator

Note that we don't released HyperLogLog-Tailcut code due to the copyright. You can download it from (https://www.dropbox.com/s/l0eaexhzvi34x9u/HLLPlus.zip),
or send email to the author of original paper (Better with fewer bits: Improving the performance of cardinality estimation of large data streams)

## Data
we provide a test case in Data folder whose actual cardinality is 1000,000.

## Requirement
Ensure g++ and make are installed. Our experimental platform is equipped with Ubuntu 16, g++ 5.4 and make 4.1

## Compile and Run
```
$cd demo
$make clean
$make
$./main.out
```
The result (estimate value, record throughput and query throughput) of above estimators would show.
