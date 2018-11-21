all: mytime2.o usetime2.o
	g++ mytime2.o usetime2.o -o a.out
mytime2.o: mytime2.cpp mytime2.h
	g++ -c mytime2.cpp mytime2.h
usetime2.o: usetime2.cpp mytime2.h
	g++ -c usetime2.cpp mytime2.h

clean:
	rm  *.o *.out *.gch
