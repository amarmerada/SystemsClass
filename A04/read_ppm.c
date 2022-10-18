#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"


/** Choose *one* to implement

struct ppm_pixel* read_ppm(const char* filename, int* w, int* h) {

  

  return NULL;
}*/

struct ppm_pixel** read_ppm_2d(const char* filename, int* w, int* h) {
  int weight = *w;
  int height = *h;
  FILE* fp;
  fp = fopen("feep-raw.ppm", "rb");
  struct ppm_pixel** rtn = (struct ppm_pixel**)malloc(weight*height*sizeof(struct ppm_pixel));
  
  char buff[20];
  fgets(buff, 20, fp);
  if((buff[0]!= 'P') | (buff[1]!= '6')){
    printf("incorrect file format (must be P6) \n");
    exit(1);
  }
  printf("%c%c   \n", buff[0], buff[1]);
  fgets(buff, 20, fp);
  printf("%s", buff);
  fgets(buff, 20, fp);
  printf("%s", buff);
  fgets(buff, 20, fp);
  printf("%s", buff);
  fgets(buff, 20, fp);
  printf("%s", buff);
  fgets(buff, 20, fp);
  printf("%s", buff);
  unsigned int x;
  fgetu(x, fp);
  printf("%u", x);
  fclose(fp);
  return rtn;
}

int main(){
  int a = 5;
  int b = 6;
  int*x = &a;
  int*y = &b;
  read_ppm_2d("feep-raw.ppm", x, y);
return 0;
}

