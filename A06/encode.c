#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"
#include "write_ppm.h"

int* ltob(char* inp){
  int* binary = (int*)malloc(8*sizeof(inp)*4);
  int hold;
  for(int i = 0; i<(sizeof(inp)*8); i+= 8){ // goes through each char * 8/8
      hold = inp[i/8]; // goes thru each char
      binary[i + 7] = hold % 2;
      hold = hold / 2;
      binary[i + 6] = hold % 2;
      hold = hold / 2;
      binary[i + 5] = hold % 2;
      hold = hold / 2;
      binary[i + 4] = hold % 2;
      hold = hold / 2;
      binary[i + 3] = hold % 2;
      hold = hold / 2;
      binary[i + 2] = hold % 2;
      hold = hold / 2;
      binary[i + 1] = hold % 2;
      hold = hold / 2;
      binary[i] = hold % 2;
  }
  return binary;
}

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("usage: encode <file.ppm>\n");
    return 0;
  }
  int w;
  int h;
  struct ppm_pixel** image = read_ppm_2d(argv[1], &w, &h);
  int char_capacity = (w*h*3)/8;
  printf("Image size: %d x %d  Number of possible characters: %d\n Enter a phrase (%d characters or less): ", w, h, char_capacity, char_capacity);
  char* phrase = (char*)malloc(char_capacity*sizeof(char));
  scanf("%s", phrase);
  //convert phrase to binary array
  
  int* bin = ltob(phrase);
  
  //add each item in binary array to end of each color in image
  int s = 0;
 
  while(s<(8*char_capacity)){
  for(int i = 0; i < h; i++){
    for(int j = 0; j < w; j++){
      image[i][j].red = (image[i][j].red & 0b11111110) | bin[s];
      s++;
      image[i][j].green = (image[i][j].green & 0b11111110) | bin[s];
      s++;
      image[i][j].blue = (image[i][j].blue & 0b11111110) | bin[s];
      s++;
    }
  }
  }
  char * filename = argv[1];
  char * outputfile = malloc(strlen(argv[1]) + 8);
  strcpy(outputfile, argv[1]);
  outputfile[strlen(outputfile)-4] = '\0';
  strcat(outputfile, "-encoded.ppm");
  /*strcpy(outputfile, argv[1]);
  
  
  outputfile[strlen(outputfile)-4] = '\0';
  strcat(outputfile, "-encoded2.ppm");*/
  
  //printf("writing to file: %s \n", outputfile);
  write_ppm_2d(outputfile, image, w, h);
  for(int i = 0; i < h; i++){
    free(image[i]);
  }
  free(image);
  free(bin);
  free(phrase);
  return 0;
}

