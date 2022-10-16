
To build our code, run:
	g++ -std=c++11 *.cpp -o ksub -DIL_STD -fopenmp -g

After building, to run our code, run:
	/ksub ...
	
	EX: /ksub -f test1.txt -f1 test2.txt -V 20 -a 2 -st 0 -en 12
	
		////////////////////////////////////////////
		-f  data file
		-f1  data thamsodinh
		-V  n_node
		-st start
		-en end
		-l  limit
		-a  algorithm 0:dfs, 1:bfs, 2:bestfs, 3: ids, 4: ucs, 5: Astar , 6: HillClimbing


We conducted experiments on a Linux machine with 2.3Ghz Xeon 18 core processor and 256Gb of RAM. With 70 threads, DStream usually terminates after 20 minutes, RStream is 2 hours.

