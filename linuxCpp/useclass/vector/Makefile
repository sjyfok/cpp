all: vector.o randwalk.o
	g++ vector.o randwalk.o -o a.out
vector.o: vector.cpp vector.h
	g++ -c vector.cpp vector.h
randwalk.o: randwalk.cpp vector.h
	g++ -c randwalk.cpp vector.h

clean:
	rm  *.o *.out *.gch
