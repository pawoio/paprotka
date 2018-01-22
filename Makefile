CC = gcc
CFLAGS = -Wall -m64 

all: main.o fern.o
	$(CC) $(CFLAGS) -o output2 main.o fern.o -lGL -lglut

fern.o: fern.s
	nasm -f elf64 -o fern.o  fern.s

main.o: main.c 
	$(CC) $(CFLAGS) -c -o main.o main.c

clean:
	rm -f *.o

