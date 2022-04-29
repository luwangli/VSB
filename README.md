# VSB
Cardinality estimation is the task of obtaining the number of distinct items in a
data stream, which plays an important role in many application domains, such as 
traffic monitoring, recommendation system and query optimization in database.
However, when dealing with high-speed data streams, it remains a significant challenge
to estimate cardinality considering record/query overhead and memory-efficiency.
This repository introduces an online cardinality estimator, called Virtual Self-adaptive
Bitmap (VSB). VSB automatically adapts its sampling probabaility to different stream sizes
by logically adding virtual bits.
