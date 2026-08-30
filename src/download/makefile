all:download.o
	gcc main_download.c download.o -o main_download.exe -lcurl

download.o:download.c
	gcc download.c -c -lcurl
	
clean:
	rm -f *.o *.exe
