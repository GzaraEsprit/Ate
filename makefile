CC = gcc
CFLAGS = -Wall
LDFLAGS = -lSDL -lSDL_image

SRC = main.c game.c minimap.c
OBJ = $(SRC:.c=.o)
EXEC = game

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
