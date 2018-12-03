all : bank.o queue.o
	g++ bank.o queue.o -o a.out
bank.o: bank.cpp queue.h
	g++ -c bank.cpp queue.h  
queue.o: queue.cpp queue.h
	g++ -c queue.cpp queue.h 

clean:
	rm *.o *.out *.gch

