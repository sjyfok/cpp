all : sayings.o string.o
	g++ sayings.o string.o -o a.out
sayings.o: sayings.cpp string.h
	g++ -c sayings.cpp string.h  
string.o: string.cpp string.h
	g++ -c string.cpp string.h 

clean:
	rm *.o *.out *.gch

