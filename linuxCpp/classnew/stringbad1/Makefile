all : vegnews.o stringbad.o
	g++ vegnews.o stringbad.o -o a.out
vegnews.o: vegnews.cpp stringbad.h
	g++ -c vegnews.cpp stringbad.h  
stringbad.o: stringbad.cpp stringbad.h
	g++ -c stringbad.cpp stringbad.h 

clean:
	rm *.o *.out *.gch

