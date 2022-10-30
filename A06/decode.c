#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"
#include <math.h>

int BtoD(int* byte){
  int decimal = 0;
  int hold;
  for(int i = 7; i >= 0; i--){
    //printf(" %d ", byte[i]);
    int hold = byte[i];
    decimal += hold * pow(2.0, (double)(7-i));
    
  }
  return decimal;
}

/*char DtoL(int ascii){
  char converted = ascii;
  return converted;
}*/

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("usage: decode <file.ppm>\n");
    return 0;
  }
  int w;
  int h;
  struct ppm_pixel** image = read_ppm_2d(argv[1], &w, &h);
  int char_capacity = (w*h*3)/8;
  printf("Image size: %d x %d  Number of possible characters: %d\n", w, h, char_capacity);

  //printpixels(image, h, w);

  for (int i = 0; i <(h); i ++){ // should be i < width
    
    for (int j = 0; j < (w); j++){
      image[i][j].red = image[i][j].red & 0b1;
      image[i][j].green = image[i][j].green & 0b1;
      image[i][j].blue = image[i][j].blue & 0b1;
    }
  }
  //printpixels(image, h, w);
  unsigned char* output = (unsigned char*)malloc(w*h*3*sizeof(unsigned char));
  int s = 0;
  for(int i = 0; i < (h); i++){
    for(int j = 0; j < (w); j++){
      output[s] = image[i][j].red;
      s++;
      output[s] = image[i][j].green, 
      s++;
      output[s] = image[i][j].blue;
      s++;
    }
  }
  for (int i = 0; i < h; i++){
    free(image[i]);
  }
  free(image);
  
  int final[8];
  int x;
  char* text = (char*)malloc(char_capacity*sizeof(char));
  for(int i = 0; i < s; i += 8){ // for each 8 bit sequence
      final[0] = output[i];
      final[1] = output[i+1];
      final[2] = output[i+2];
      final[3] = output[i+3];
      final[4] = output[i+4];
      final[5] = output[i+5];
      final[6] = output[i+6];
      final[7] = output[i+7];
      x = BtoD(final);
      // printf("%d, ", x);
      text[i/8] = x;
      //printf("%c \n", text[i/8]);

  }


  
  /*for (int i = 0; i < s; i++){
    printf("%u ", output[i]);
  }*/
  printf("\n");

  for (int i = 0; i < (char_capacity); i++){
    printf("%c", text[i]);
    if(text[i] == '}'){
      break;
    }
  }
  free(output);
  
  free(text);
  printf("\n");
  return 0;
}

