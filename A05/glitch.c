#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"
#include "write_ppm.h"



int main(int argc, char** argv) {
  if (argc != 2) {
    printf("usage: glitch <file.ppm>\n");
    return 0;
  }

  char * filename = argv[1];
  char * outputfile = malloc(strlen(argv[1])+10);
  strcpy(outputfile, argv[1]);
  outputfile[strlen(outputfile)-4] = '\0';
  strcat(outputfile, "-glitch.ppm");

  unsigned char old;
  unsigned char new;

  unsigned char oldR;
  unsigned char oldG;
  unsigned char oldB;
  unsigned char newR;
  unsigned char newG;
  unsigned char newB;

  int w, h;
  printf("Reading %s ", filename);
  struct ppm_pixel** pixels = read_ppm_2d(filename, &w, &h);
  printf("width %d height %d\n", w, h);
  for (int i = 0; i < h; i ++){ // should be i < width
    for (int j = 0; j < w; j++){
      oldR = pixels[i][j].red;
      //newR = oldR << (rand() % 2);
      oldG = pixels[i][j].green;
      //newG = oldG << (rand() % 2);
      oldB = pixels[i][j].blue;
      //newB = oldB << (rand() % 2);
      pixels[i][j].blue = oldR;
      pixels[i][j].red = oldG;
      pixels[i][j].green = oldB;
    }
  } 
   for (int i = 0; i <h; i ++){ // should be i < width
    for (int j = 0; j < w; j++){
      //printf("here %d %d\n", i, j);
      old = pixels[i][j].red;
      new = old << (rand() % 2);
      pixels[i][j].red = new;
      old = pixels[i][j].green;
      new = old << (rand() % 2);
      pixels[i][j].green = new;
      old = pixels[i][j].green;
      new = old << (rand() % 3);
      pixels[i][j].blue = new;
    }
  }
  
  printf("writing to %s\n", outputfile);
  write_ppm_2d(outputfile, pixels, w, h);

  for (int i = 0; i < h; i++){
    free(pixels[i]);
  }
  free(pixels);
  free(outputfile);

  return 0;
}