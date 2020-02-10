libgol.so:	lib/gol.c lib/gol.h 
	gcc -fPIC -c -Wall -Wextra -pedantic -std=c11 lib/gol.c -o libgol.o
	gcc -shared libgol.o -o libgol.so

gameoflife: cli/gameoflife.c libgol.so
	gcc -c -Wall -Wextra -pedantic -std=c11 cli/gameoflife.c -I lib -o gol.o
	gcc gol.o -L . -l:libgol.so -o gol

clean:	
	rm -rf libgol.o gol.o libgol.so gol gol.exe