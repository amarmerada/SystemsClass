#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"


/** Choose *one* to implement

struct ppm_pixel* read_ppm(const char* filename, int* w, int* h) {

  

  return NULL;
}*/

void printpixels(struct ppm_pixel** toPrint, int height, int width){
  struct ppm_pixel printer;
  unsigned char red;
  unsigned char green;
  unsigned char blue;
  for (int i = 0; i < height; i ++){
    for (int j = 0; j < width; j++){
      printer = toPrint[i][j]; 
      red = printer.red;
      green = printer.green;
      blue = printer.blue;
      if(j == width -1){
        printf("( %u, %u, %u ) \n", red, green, blue);
      }
      else{
        printf("( %u, %u, %u ) ", red, green, blue);
      }
    }
  }

}

struct ppm_pixel** read_ppm_2d(const char* filename, int* w, int* h) {
  int width = *w;
  int height = *h;
  FILE* fp;
  fp = fopen(filename, "rb");
  
  char buff[1024];
  fgets(buff, 1024, fp);
  if((buff[0]!= 'P') | (buff[1]!= '6')){
    printf("incorrect file format (must be P6) \n");
    exit(1);
  }
  printf("%c%c   \n", buff[0], buff[1]);
  fgets(buff, 1024, fp);
  printf("%s", buff);
  fscanf(fp, "%d %d", &width, &height);
  printf("%d %d\n", width, height);
  fgets(buff, 1024, fp);
  //printf("%s", buff);
  fgets(buff, 1024, fp);
  printf("%s", buff);
  
  struct ppm_pixel** rtn = (struct ppm_pixel**)malloc(height*sizeof(struct ppm_pixel));
  for (int i = 0; i < height; i++){
    rtn[i] = (struct ppm_pixel*)malloc(width*sizeof(struct ppm_pixel));
    fread(rtn[i], sizeof(struct ppm_pixel), width, fp);
  }
  fclose(fp);
  printpixels(rtn, height, width);
  *w = width;
  *h = height;
  
  return rtn;
}

int main(int argc, char** argv){
  char* nameOfFile = (char*)malloc(argc*sizeof(char*));
  strcpy(nameOfFile, argv[1]);
  int a = 200;
  int b = 300;
  int*x = &a;
  int*y = &b;
  read_ppm_2d(nameOfFile, x, y);
return 0;
}

