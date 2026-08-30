all: analyseXML.o
	gcc -g main_analyseXML.c analyseXML.o -o main_analyseXML.exe `pkg-config --cflags --libs glib-2.0`

analyseXML.o: analyseXML.c
	gcc `pkg-config --cflags glib-2.0` -c analyseXML.c 

clear:
	rm -f *.o main_analyseXML.exe