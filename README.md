# LU Decomposition
COL380: Assignment 1 

### Pthread Implementation [ COMPLETED ]:
How to Run?

> `chmod +x run.sh`

1. run `./run.sh`
2. In `time.txt` number of threads vs time taken (in sec) will be printed for 8000 X 8000 matrix. Change the dimentions in `run.sh` file.
3. Set `VERIFY` to `1` to check the correctness. The norm should be very small. Dont check for large matrices, since its $O(n^3)$
4. Benchmarking only the LU decomposition part, not the initialization and verification part. (Used `timer.cpp`)
5. Compiled using `-O3` flag enabled. 

TODO:

1. Make report for pthread part and plot graphs. Do whatever is asked in webpage. 