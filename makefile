
# 'make', 'make all'

CC = gcc
CFLAGS  = -Wall

all: argsxorstr xorstr verA verB verC

argsxorstr:  argsxorstr.o mystrlib.o
	$(CC) $(CFLAGS) -o argsxorstr argsxorstr.o mystrlib.o

argsxorstr.o:  argsxorstr.c mystrlib.h
	$(CC) $(CFLAGS) -c argsxorstr.c

xorstr:  xorstr.o mystrlib.o
	$(CC) $(CFLAGS) -o xorstr xorstr.o mystrlib.o

xorstr.o:  xorstr.c mystrlib.h
	$(CC) $(CFLAGS) -c xorstr.c

mystrlib.o:  mystrlib.c mystrlib.h 
	$(CC) $(CFLAGS) -c mystrlib.c
verA: verA.o mystrlib.o
	$(CC) $(CFLAGS) -o verA verA.o mystrlib.o 

verA.o: verA.c mystrlib.h
	$(CC) $(CFLAGS) -c verA.c

verB: verB.o mystrlib.o
	$(CC) $(CFLAGS) -o verB verB.o mystrlib.o

verB.o: verB.c mystrlib.h
	$(CC) $(CFLAGS) -c verB.c

verC: verC.o mystrlib.o
	$(CC) $(CFLAGS) -o verC verC.o mystrlib.o

verC.o: verC.c mystrlib.h
	$(CC) $(CFLAGS) -c verC.c
clean: 
	rm -f argsxorstr xorstr verA verB verC *.o

