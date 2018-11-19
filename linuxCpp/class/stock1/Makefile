all : stock1.o usestock1.o
	g++ stock1.o usestock1.o -o a.out
stock00.o: stock1.cpp stock1.h
	g++ -c stock1.cpp stock1.h  
usestock0.o: usestock1.cpp stock1.h
	g++ -c usestock1.cpp stock1.h 

clean:
	rm *.o *.out 

