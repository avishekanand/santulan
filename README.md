Santulan
========

This is an implementation for a simple load balancing algorithm for multi-choice allocation problems called Local Search Allocation (LSA). LSA finds applications in finding perfect matchings in a special class of sparse random bipartite graphs, orientation of random hyper- graphs, load balancing and hashing.

We implement LSA in the context of cuckoo hashing and explore possible applications where there is a requirement of high frequency insertions into a hash table.

Description
===========

Cuckoo hashing is a collision-resolution scheme of values of hash functions in a table, with worst-case constant lookup time. It is based on the observation that if multiple hash functions are used (instead of one), then the hash table has a better space utilization while still preserving constant lookup times. The basic idea is to use k hash functions instead of only one. This provides k possible locations in the hash table for each key. In one of the commonly used variants of the algorithm, the hash table is split into two smaller tables of equal size, and each hash function provides an index into one of these two tables.


This implementation of LSA is based on Cuckoo hashing. It essentially provides a collision resolution strategy for multiple-choice scenarios very common in Cuckoo Hashing. The most common implementations of cuckoo hashing depend on random walks or breadth first search procedures for finding a feasible allocation. LSA is a simple and novel algorithm which runs in linear time with high probability for finding an allocation. This has been proved to perform appreciably better than random walks. 

For more theoretical description we refer the interested reader to the original research manuscript:

>**"Balls into Bins made Faster"**
> by *Megha Khosla*
>
> In: Proceedings of the 21st Annual *European Symposium on Algorithms (ESA '13)*, p. 601-612.




