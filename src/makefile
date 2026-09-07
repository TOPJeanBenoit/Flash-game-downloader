CFLAGS = 
#-Wall -g


all: analyseXML.o  download.o makeFolder.o
	gcc $(CFLAGS) main.c analyseXML/analyseXML.o download/download.o makeFolder/makeFolder.o -o main.exe -lcurl -luv `pkg-config --cflags --libs glib-2.0`

analyseXML.o: analyseXML/analyseXML.c
	make -C analyseXML

download.o: download/download.c
	make -C download download.o

makeFolder.o: makeFolder/makeFolder.c
	make -C makeFolder makeFolder.o
	
clean:
	rm -f *.o *.exe