all: stonewt.o stone.o
	g++ stonewt.o stone.o -o a.out
stonewt.o: stonewt.cpp stonewt.h
	g++ -c stonewt.cpp stonewt.h
stone.o: stone.cpp stonewt.h
	g++ -c stone.cpp stonewt.h

clean:
	rm  *.o *.out *.gch
