#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include"gol.h"

int main(int argc, char *argv[]){
  char inputFile[50] = "";
  char outputFile[50] = "";
  int printStats = 0;
  int torus = 0;
  int generations = 5;


  int opt;
  while ((opt = getopt(argc, argv, "i:o:g:st")) != -1)
  {
    switch (opt)
    {
    case 'i':
      strcpy(inputFile, optarg);
      break;
    case 'o':
      strcpy(outputFile, optarg);
      break;
    case 'g':
      generations = atoi(optarg);
      break;
    case 's':
      printStats = 1;
      break;
    case 't':
      torus = 1;
      break;
    }
  }

  struct universe v; 
  if(strlen(inputFile) > 0)
  {
    read_in_file(fopen(inputFile, "r"),&v);
  }
  else
  {
    read_in_file(stdin,&v);/* code */
  }

  for(int x = 0; x<generations; x++)
  {
    if(torus) evolve(&v,will_be_alive_torus);
    else evolve(&v,will_be_alive);
  }
  
  if(printStats) print_statistics(&v);

  if(strlen(outputFile) > 0)
  {
    FILE* outFile = fopen(outputFile, "W");
    write_out_file(outFile,&v);
    fclose(outFile);
  }
  else
  {
    write_out_file(stdout,&v);
  }

  return 0;
}
