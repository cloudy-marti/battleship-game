# création de l'exécutable 'game'

Game : *.o
		gcc game.o functions.o -o Game

game.o: game.c turnManager.c
		gcc -c game.c -o game.o

board.o: board.c typedefs.h
		gcc -c board.c -o board.o

playerManagerV2.o: playerManagerV2.c unitManager.h
		gcc -c playerManagerV2.c -o playerManagerV2.o

unitManager.o: unitManager.c typedefs.h playerManagerV2.h
		gcc -c unitManager.c -o unitManager.o

turnManager.o: turnManager.c playerManagerV2.h unitManager.h board.h
		gcc -c turnManager.c -o turnManager.o

# suppression des fichiers temporaires

clean:
		rm -rf *.o