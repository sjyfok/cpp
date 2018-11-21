all: stone1.o stonewt1.o
	g++ stonewt1.o stone1.o -o a.out
stonewt1.o: stonewt1.cpp stonewt1.h
	g++ -c stonewt1.cpp stonewt1.h
stone1.o: stonewt1.cpp stonewt1.h
	g++ -c stone1.cpp stonewt1.h

clean:
	rm  *.o *.out *.gch
