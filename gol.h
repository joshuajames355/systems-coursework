#include <stdio.h>

struct universe {
    int* start; //an array of width*height ints, where "start" is the pointer to the first element
    int width;
    int height;

    //additional statisitics
    unsigned int numAlive; //number of cells that are currently alive
    unsigned int totalAlive; //total of numAlive across all generations
    unsigned int numGenerations; 
};

/*Do not modify the next seven lines*/
void read_in_file(FILE *infile, struct universe *u);
void write_out_file(FILE *outfile, struct universe *u);
int is_alive(struct universe *u, int column, int row);
int will_be_alive(struct universe *u, int column, int row);
int will_be_alive_torus(struct universe *u,  int column, int row);
void evolve(struct universe *u, int (*rule)(struct universe *u, int column, int row));
void print_statistics(struct universe *u);
/*You can modify after this line again*/

void print_universe(struct universe *u);
int getNumAliveCells(struct universe *u);