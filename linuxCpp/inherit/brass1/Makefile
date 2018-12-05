all : usebrass.o brass.o
	g++ usebrass.o brass.o -o a.out
usebrass.o: usebrass.cpp brass.h
	g++ -c usebrass.cpp brass.h  
brass.o: brass.cpp brass.h
	g++ -c brass.cpp brass.h 

clean:
	rm *.o *.out *.gch

