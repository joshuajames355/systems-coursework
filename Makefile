gameoflife: gameoflife.c libgol.so
	gcc -c -Wall -Wextra -pedantic -std=c11 gameoflife.c -I lib -o gol.o
	gcc gol.o -L . -l:libgol.so -o gol

libgol.so:	gol.c gol.h 
	gcc -fPIC -c -Wall -Wextra -pedantic -std=c11 gol.c -o libgol.o
	gcc -shared libgol.o -o libgol.so

clean:	
	rm -rf libgol.o gol.o libgol.so gol gol.exe gol.exe.stackdump