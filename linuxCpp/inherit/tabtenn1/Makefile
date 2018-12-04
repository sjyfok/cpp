all : usett.o tabtenn.o
	g++ usett.o tabtenn.o -o a.out
usett.o: usett.cpp tabtenn.h
	g++ -c usett.cpp tabtenn.h  
tabtenn.o: tabtenn.cpp tabtenn.h
	g++ -c tabtenn.cpp tabtenn.h 

clean:
	rm *.o *.out *.gch

