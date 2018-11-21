all: mytime3.o usetime3.o
	g++ mytime3.o usetime3.o -o a.out
mytime3.o: mytime3.cpp mytime3.h
	g++ -c mytime3.cpp mytime3.h
usetime3.o: usetime3.cpp mytime3.h
	g++ -c usetime3.cpp mytime3.h

clean:
	rm  *.o *.out *.gch
