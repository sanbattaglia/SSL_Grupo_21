CC = gcc
CFLAGS = -Wall -g -Iinclude
LIBS = -lfl

all: micro

micro: parser/parser.tab.o parser/scanner.o tabla/tabla_simbolos.o main.o
	$(CC) $(CFLAGS) -o micro parser/parser.tab.o parser/scanner.o tabla/tabla_simbolos.o main.o $(LIBS)

parser/parser.tab.c parser/parser.tab.h: parser/parser.y
	bison -d parser/parser.y -o parser/parser.tab.c

parser/scanner.c: parser/scanner.l parser/parser.tab.h
	flex -o parser/scanner.c parser/scanner.l

parser/parser.tab.o: parser/parser.tab.c include/defs.h tabla/tabla_simbolos.h
	$(CC) $(CFLAGS) -c parser/parser.tab.c -o parser/parser.tab.o

parser/scanner.o: parser/scanner.c parser/parser.tab.h include/defs.h
	$(CC) $(CFLAGS) -c parser/scanner.c -o parser/scanner.o

tabla/tabla_simbolos.o: tabla/tabla_simbolos.c tabla/tabla_simbolos.h include/defs.h
	$(CC) $(CFLAGS) -c tabla/tabla_simbolos.c -o tabla/tabla_simbolos.o

main.o: main.c tabla/tabla_simbolos.h
	$(CC) $(CFLAGS) -c main.c -o main.o

clean:
	rm -f micro parser/scanner.c parser/parser.tab.c parser/parser.tab.h *.o parser/*.o tabla/*.o
