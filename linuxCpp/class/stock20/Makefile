all : stock20.o usestock2.o
	g++ stock20.o usestock2.o -o a.out
stock20.o: stock20.cpp stock20.h
	g++ -c stock20.cpp stock20.h  
usestock2.o: usestock2.cpp stock20.h
	g++ -c usestock2.cpp stock20.h 

clean:
	rm *.o *.out *.gch

