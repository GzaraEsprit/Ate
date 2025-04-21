CC = gcc
CFLAGS = -Wall
LIBS = -lSDL -lSDL_image -lSDL_ttf

all: quiz

quiz: main.o enigme.o
	$(CC) $(CFLAGS) -o quiz main.o enigme.o $(LIBS)

main.o: main.c enigme.h
	$(CC) $(CFLAGS) -c main.c

enigme.o: enigme.c enigme.h
	$(CC) $(CFLAGS) -c enigme.c

clean:
	rm -f *.o quiz
