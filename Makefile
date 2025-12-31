CC = gcc
CFLAGS = -Wall -I.

# Target utama
main: main.o data_manager.o scheduler.o
	$(CC) -o solusi_mbg main.o data_manager.o scheduler.o -lm

# Aturan kompilasi
main.o: main.c structure.h
	$(CC) $(CFLAGS) -c main.c

data_manager.o: data_manager.c data_manager.h structure.h
	$(CC) $(CFLAGS) -c data_manager.c

scheduler.o: scheduler.c scheduler.h structure.h
	$(CC) $(CFLAGS) -c scheduler.c

# Bersihkan file
clean:
	rm -f *.o solusi_mbg