all : stacker.o stack.o
	g++ stacker.o stack.o -o a.out
stacker.o: stacker.cpp stack.h
	g++ -c stacker.cpp stack.h  
stack.o: stack.cpp stack.h
	g++ -c stack.cpp stack.h 

clean:
	rm *.o *.out *.gch

