# LU Decomposition
COL380: Assignment 1 

### Pthread Implementation:
How to Run?

1. run `./run.sh`
2. Currently number of threads and dimentions of the matrix are hardcoded in `pthread.cpp`, will change it later.
3. Set `VERIFY` to `1` to check the correctness. The norm should be very small. Dont check for large matrices, since its $O(n^3)$
4. Benchmarking only the LU decomposition part, not the initialization and verification part. (Used `timer.cpp`)
5. Compiled using `-O3` flag enabled. 

TODO:

1. Further optimizations. Better memory layout, remove false sharing etc. Cache friendly code. 