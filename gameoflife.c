#include <stdlib.h>
#include <string.h>
#include"gol.h"

int main(int argc, char *argv[]){
  char *inputFile = 0;
  char *outputFile = 0;

  int printStats = 0;
  int torus = 0;
  int generations = -1;

  int state = 0;
  for(int x = 1; x < argc; x++)
  {
    switch(state)
    {
      case 0:
        switch(argv[x][0])
        {
          case '-':
            if (strlen(argv[x]) == 2)
            {
              switch(argv[x][1])
              {
                case 'i':
                  state = 1;
                  continue;
                case 'o':
                  state = 2;
                  continue;
                case 'g':
                  state = 3;
                  continue;
                case 's':
                  printStats = 1;
                  continue;
                case 't':
                  torus = 1;
                  continue;
              }
            }
        }
        fprintf(stderr, "ERROR: Unrecognized command line option %s.", argv[x]);
        return 1;
      case 1://handling i
        state = 0;
        if(inputFile && strcmp(inputFile, argv[x]))
        {
          fprintf(stderr, "ERROR: Conflicting command line options.");
          return 1;
        }
        inputFile = argv[x];
        break;
      case 2://handling o
        state = 0;
        if(outputFile && strcmp(outputFile, argv[x]))
        {
          fprintf(stderr, "ERROR: Conflicting command line options.");
          return 1;
        }
        outputFile = argv[x];
        break;
      case 3://handling g
        state = 0;
        if(generations != -1 && generations != atoi(argv[x]))
        {
          fprintf(stderr, "ERROR: Conflicting command line options.");
          return 1;
        }
        generations = atoi(argv[x]);
        break;
    }
  }
  if(state != 0)
  {
    fprintf(stderr, "ERROR: Expecting another value after %s.", argv[argc-1]);
    return 1;
  }

  if(generations == -1) generations = 5;

  struct universe v; 
  if(inputFile)
  {
    read_in_file(fopen(inputFile, "r"),&v);
  }
  else
  {
    read_in_file(stdin,&v);
  }

  for(int x = 0; x<generations; x++)
  {
    if(torus) evolve(&v,will_be_alive_torus);
    else evolve(&v,will_be_alive);
  }
  
  if(printStats) print_statistics(&v);

  if(outputFile)
  {
    FILE* outFile = fopen(outputFile, "w");
    write_out_file(outFile,&v);
    fclose(outFile);
  }
  else
  {
    write_out_file(stdout,&v);
  }

  return 0;
}
