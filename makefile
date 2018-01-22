CC = gcc
CFLAGS = -Wall -m64

all: main.o BarnsleyFern.o
	$(CC) $(CFLAGS) -o paprotka main.o BarnsleyFern.o `allegro-config --shared`

BarnsleyFern.o: BarnsleyFern.s
	nasm -f elf64 -o BarnsleyFern.o BarnsleyFern.s

main.o: main.c 
	$(CC) $(CFLAGS) -c -o main.o main.c

clean:
	rm -f *.o

