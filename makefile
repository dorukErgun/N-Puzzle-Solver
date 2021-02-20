
171044057 : HW4.o
	g++ -o 171044057 HW4.o

HW3.o : HW4.cpp
	g++ -c -std=c++11 -Wall HW4.cpp
clean:
	rm *.o 171044057
