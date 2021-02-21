
prog : n_puzzle_solver.o
	g++ -o prog n_puzzle_solver.o

prog.o : n_puzzle_solver.cpp
	g++ -c -std=c++11 -Wall n_puzzle_solver.cpp
clean:
	rm *.o prog
