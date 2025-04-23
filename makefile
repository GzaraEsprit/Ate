game:main.o personnage.o
	gcc main.o personnage.o -o game -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf  -g
main.o:main.c 
	gcc -c main.c -g
personnage.o:personnage.c 
	gcc -c personnage.c -g 



	
