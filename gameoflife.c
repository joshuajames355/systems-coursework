#include <stdlib.h>
#include <string.h>
#include"gol.h"

int main(int argc, char *argv[]){
  char *inputFile = 0;
  char *outputFile = 0;

  int printStats = 0;
  int torus = 0;
  int generations = 5;

  int state = 0;
  for(int x = 1; x < argc; x++)
  {
    switch(state)
    {
      case 0:
        switch(argv[x][0])
        {
          case '-':
            if (strlen(argv[x]) > 1)
            {
              switch(argv[x][1])
              {
                case 'i':
                  state = 1;
                  break;
                case 'o':
                  state = 2;
                  break;
                case 'g':
                  state = 3;
                  break;
                case 's':
                  printStats = 1;
                  break;
                case 't':
                  torus = 1;
                  break;
              }
            }
        }
        break;
      case 1://handling i
        state = 0;
        inputFile = argv[x];
        break;
      case 2://handling o
        state = 0;
        outputFile = argv[x];
        break;
      case 3://handling g
        state = 0;
        generations = atoi(argv[x]);
        break;
    }
  }

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
