all : file1.o file2.o
	g++ file1.o file2.o -o a.out
file1.o: file1.cpp coordin.h
	g++ -c file1.cpp coordin.h  
file2.o: file2.cpp coordin.h
	g++ -c file2.cpp coordin.h 

clean:
	rm *.o *.out
