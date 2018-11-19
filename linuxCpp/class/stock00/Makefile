all : stock00.o usestock0.o
	g++ stock00.o usestock0.o -o a.out
stock00.o: stock00.cpp stock00.h
	g++ -c stock00.cpp stock00.h  
usestock0.o: usestock0.cpp stock00.h
	g++ -c usestock0.cpp stock00.h 

clean:
	rm *.o *.out
