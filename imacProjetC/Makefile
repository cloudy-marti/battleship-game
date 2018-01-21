
./a.out : makeFileProject.o board.o 
    gcc makeFileProject.o board.o

mainFileProject.o : mainFileProject.c board.c
    gcc -c mainFileProject.o 
    
board.o : board.c

mon_executable: exemple.o main.o
gcc -o mon_executable exemple.o main.o
exemple.o: exemple.c
gcc -o exemple.o -c exemple.c -Wall -O
main.o: main.c exemple.h
gcc -o main.o -c main.c -Wall -O

all: mon_executable
mon_executable: exemple.o main.o
gcc -o mon_executable exemple.o main.o
exemple.o: exemple.c
gcc -o exemple.o -c exemple.c -Wall -O
main.o: main.c exemple.h
gcc -o main.o -c main.c -Wall -O
clean:
rm -f *.o core
mrproper: clean
rm -f mon_executable


hello: hello.o main.o
	gcc -o hello hello.o main.o

hello.o: hello.c
	gcc -o hello.o -c hello.c -W -Wall

main.o: main.c hello.h
	gcc -o main.o -c main.c -W -Wall