all: mytime1.o usetime1.o
	g++ mytime1.o usetime1.o -o a.out
mytime1.o: mytime1.cpp mytime1.h
	g++ -c mytime1.cpp mytime1.h
usetime1.o: usetime1.cpp mytime1.h
	g++ -c usetime1.cpp mytime1.h

clean:
	rm  *.o *.out *.gch
