#include "gol.h"
#include <string.h>

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

//each line is a seperate
void read_in_file(FILE *infile, struct universe *u)
{
    char row[513]; //Max length of 512 + null seperator
    readLine(infile, &row, 512);

    (*u).width = strlen(row);
    (*u).start = malloc((*u).width * sizeof(int));

    unsigned int rowIndex = 0;

    while (strlen(row) != 0)
    {
        (*u).start = realloc((*u).start, (rowIndex+1)*(*u).width*sizeof(int));
    
        unsigned int currentPos = 0;

        while(currentPos < strlen(row) && currentPos < (*u).width)
        {
            if(row[currentPos] == '*') (*u).start[rowIndex*(*u).width + currentPos] = 1;
            else (*u).start[rowIndex*(*u).width + currentPos] = 0;
            currentPos += 1;
        }
        while(currentPos < (*u).width)
        {
            (*u).start[rowIndex*(*u).width + currentPos] = 0;
            currentPos += 1;
        }

        rowIndex += 1;
        readLine(infile, &row, (*u).width);
    }
    (*u).height = rowIndex;
    printf("width: %d\n", (*u).width);
    printf("height: %d\n", (*u).height);
}