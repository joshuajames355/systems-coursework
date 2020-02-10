#include "gol.h"
#include <string.h>
#include <stdlib.h>

void readLine(FILE *infile, char* out, int size)
{
    int currentPos = 0;
    char temp;
    while (currentPos < size)
    {
        temp = fgetc(infile);
        if(temp == EOF) //handle EOF
        {
            out[0] = '\0';
            return;
        }
        if(temp == '\n'){
            out[currentPos] = '\0';
            return;
        };
        out[currentPos] = temp;
        currentPos += 1;
    }
    //discard rest of line after newline char
    while (1)
    {
        temp = fgetc(infile);
        if(temp == '\n' || temp == EOF) return;
    }
}

void read_in_file(FILE *infile, struct universe *u)
{
    char row[513]; //Max length of 512 + null seperator
    readLine(infile, row, 512);

    (*u).width = strlen(row);
    (*u).start = malloc((*u).width * sizeof(int));

    int rowIndex = 0;

    while (strlen(row) != 0)
    {
        (*u).start = realloc((*u).start, (rowIndex+1)*(*u).width*sizeof(int));
    
        int posIn = 0; //curent position in row
        int posOut = 0; //current position in u.start

        //Copy from input (row) to output (u.start)
        while(posIn < (int) strlen(row) && posOut < (*u).width)
        {
            if(row[posIn] == '*') 
            {
                (*u).start[rowIndex*(*u).width + posOut] = 1;
                ++posOut;
            }
            else if(row[posIn] == '.') 
            {
                (*u).start[rowIndex*(*u).width + posOut] = 0;
                ++posOut;
            }
            ++posIn;
        }

        if(rowIndex == 0) //set width after first line completed
        {
            (*u).width = posOut;
        }
        else
        {
            //Pad output with 0's until the reached width (the width of the first line) is reached
            while(posIn < (*u).width)
            {
                (*u).start[rowIndex*(*u).width + posOut] = 0;
                ++posIn;
                ++posOut;
            }
        }        

        rowIndex += 1;
        readLine(infile, row, (*u).width);
    }
    (*u).height = rowIndex;

    //initialize stats
    (*u).numGenerations = 1;
    (*u).numAlive = getNumAliveCells(u);
    (*u).totalAlive = (*u).numAlive;
}

void write_out_file(FILE *outfile, struct universe *u)
{
    for (int x = 0; x < (*u).width*(*u).height; x++)
    {
        if(x != 0 && x % (*u).width == 0)
        {
            fprintf(outfile,"\n");
        }
        if((*u).start[x] == 0) fprintf(outfile,".");
        else fprintf(outfile,"*");
    }
}

int is_alive(struct universe *u, int column, int row)
{
    if (row < 0 || column < 0 || row > (*u).height -1 || column > (*u).width -1) return 0; //bounds check
    return (*u).start[(*u).width * row + column] != 0;
}

int will_be_alive(struct universe *u, int column, int row)
{
    int aliveParents = is_alive(u, column-1, row-1) + is_alive(u, column-1, row) + is_alive(u, column-1, row+1) +
        is_alive(u, column, row-1) + is_alive(u, column, row+1) + 
        is_alive(u, column+1, row-1) + is_alive(u, column+1, row) + is_alive(u, column+1, row+1);

    int isAlive = is_alive(u, column, row);

    if(isAlive && (aliveParents == 2 || aliveParents == 3)) return 1;
    if(!isAlive && aliveParents == 3) return 1;
    return 0;
}

int mod(int num, int base)
{
    while (num < 0) num += base;
    return num % base;
}

int will_be_alive_torus(struct universe *u,  int column, int row)
{
    int width = (*u).width;
    int height = (*u).height;

    int aliveParents = is_alive(u, mod(column-1, width), mod(row-1, height)) + is_alive(u, mod(column-1, width), mod(row, height))  + is_alive(u, mod(column-1, width), mod(row+1, height)) +
        is_alive(u, mod(column, width), mod(row-1, height))  + is_alive(u, mod(column, width), mod(row+1, height))  + 
        is_alive(u, mod(column+1, width), mod(row-1, height)) + is_alive(u, mod(column+1, width), mod(row, height))  + is_alive(u, mod(column+1, width), mod(row+1, height));

    int isAlive = is_alive(u, column, row);

    if(isAlive && (aliveParents == 2 || aliveParents == 3)) return 1;
    if(!isAlive && aliveParents == 3) return 1;
    return 0;
}

void evolve(struct universe *u, int (*rule)(struct universe *u, int column, int row))
{
    int* new = malloc((*u).width * (*u).height * sizeof(int));
    for (int x = 0; x < (*u).width; x++)
    {
        for(int y = 0; y < (*u).height; y++)
        {
            new[y*(*u).width + x] = rule(u, x, y);
        }
    }
    free((*u).start);
    (*u).start = new;

    //update stats
    (*u).numGenerations += 1;
    (*u).numAlive = getNumAliveCells(u);
    (*u).totalAlive += (*u).numAlive ;
}

void print_statistics(struct universe *u)
{
    int numCells = (*u).height*(*u).width;
    printf("%2.3f %% of cells currently alive\n", (100.0*(*u).numAlive)/numCells);
    printf("%2.3f %% of cells alive on average\n", (100.0*(*u).totalAlive)/(numCells*(*u).numGenerations));
}

int getNumAliveCells(struct universe *u)
{
    int alive = 0;
    for(int i=0; i < (*u).height*(*u).width; i++)
    {
        if ((*u).start[i] != 0)
        {
            alive += 1;
        }
    }
    return alive;
}