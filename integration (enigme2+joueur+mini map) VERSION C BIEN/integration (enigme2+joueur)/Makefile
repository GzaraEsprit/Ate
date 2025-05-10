# Nom de l'exécutable
EXEC = jeu

# Compilateur
CC = gcc

# Drapeaux de compilation
CFLAGS = -Wall -g -I/usr/include/SDL

# Bibliothèques SDL
LDLIBS = -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -lSDL_gfx -lm

# Fichiers sources
SRCS = main.c common.c enigme.c joueur.c minimap.c

# Fichiers objets
OBJS = $(SRCS:.c=.o)

# Fichiers en-têtes
HEADERS = common.h enigme.h joueur.h minimap.h

# Règle par défaut
all: $(EXEC)

# Règle pour l'exécutable
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(LDLIBS)

# Règle pour les fichiers objets
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Dépendances spécifiques
main.o: main.c joueur.h
common.o: common.c common.h
enigme.o: enigme.c enigme.h joueur.h
joueur.o: joueur.c joueur.h common.h
minimap.o: minimap.c minimap.h joueur.h

# Nettoyage
clean:
	rm -f $(OBJS) $(EXEC)

# Nettoyage complet
mrproper: clean
	rm -f *~

.PHONY: all clean mrproper
