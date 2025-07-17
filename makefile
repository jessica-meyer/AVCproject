project3: project3.o
	c++ -o project3 project3.o -le101
project3.o: project3.cpp
	c++ -c project3.cpp
