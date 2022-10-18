This zip includes:
+ Source code of our 2 streaming algorithms, greedy and SGr.
+ Facebook and Sensor dataset (in "data" folder) for testing the algorithms.

Since estimating F in influence maximization is very time consuming, our code uses OpenMP for parallelization (https://en.wikipedia.org/wiki/OpenMP).

To build our code, run:
	g++ -std=c++11 *.cpp -o ksub -DIL_STD -fopenmp -g

After building, to run our code, run:
	./ksub 
		-V  n_node
		-f  data file
		-st start
		-en end
		-l  limit
		-a  algorithm 0:dfs, 1:bfs, 2:ids, 3:UCS, 4:bestFS, 5:hillClimb, 6:Astar


We conducted experiments on a Linux machine with 2.3Ghz Xeon 18 core processor and 256Gb of RAM. With 70 threads, DStream usually terminates after 20 minutes, RStream is 2 hours.