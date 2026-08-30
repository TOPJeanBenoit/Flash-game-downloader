all: makeFolder.o
	gcc main_makefolder.c makeFolder.o -o main_makefolder.exe -luv


makeFolder.o: makeFolder.c
	gcc makeFolder.c -c -luv

clean:
	rm -f *.o *.exe
