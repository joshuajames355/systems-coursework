gameoflife: gameoflife.c libgol.so
	gcc -c -Wall -Wextra -pedantic -std=c11 gameoflife.c -I lib -o gameoflife.o -g
	gcc gameoflife.o -L . -l:libgol.so -o gameoflife -g

libgol.so:	gol.c gol.h 
	gcc -fPIC -c -Wall -Wextra -pedantic -std=c11 gol.c -o libgol.o -g
	gcc -shared libgol.o -o libgol.so -g

clean:	
	rm -rf libgol.o libgol.so gameoflife.o gol.exe gol.exe.stackdump gameoflife