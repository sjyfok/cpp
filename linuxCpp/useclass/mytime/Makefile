all: mytime0.o usetime0.o
	g++ mytime0.o usetime0.o -o a.out
mytime0.o: mytime0.cpp mytime0.h
	g++ -c mytime0.cpp mytime0.h
usetime0.o: usetime0.cpp mytime0.h
	g++ -c usetime0.cpp mytime0.h

clean:
	rm  *.o *.out *.gch
