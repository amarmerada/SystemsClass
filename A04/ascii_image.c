#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"



int main(int argc, char** argv) {
  if (argc != 2) {
    printf("usage: ascii_image <file.ppm>\n");
    return 0;
  }
  int width;
  int height;
  FILE* fp;
  fp = fopen(argv[1], "rb");
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
  fclose(fp);
  int*x = &width;
  int*y = &height;
  char* nameOfFile = (char*)malloc(argc*sizeof(char*));
  strcpy(nameOfFile, argv[1]);
  struct ppm_pixel** asciiTarget = read_ppm_2d(nameOfFile, x ,y);
  struct ppm_pixel hold;
  unsigned char each = 0;
  for (int i = 0; i < height; i++){
    for (int j = 0; j < width; j++){
      hold = asciiTarget[i][j];
      each = hold.red + hold.blue + hold.green;
      
      if((each >= 0)&& (each < 26)){
        printf("@");
      }
      else if((each >= 26)&&( each <51)){
        printf("#");
      }
      else if((each >= 51)&&( each <76)){
        printf("$");
      }
      else if((each >= 76)&&( each <101)){
        printf("*");
      }
      else if((each >= 101)&&( each <126)){
        printf("o");
      }
      else if((each >= 126)&&( each <151)){
        printf(";");
      }
      else if((each >= 151)&&( each <176)){
        printf(":");
      }
      else if((each >= 176)&&( each <201)){
        printf(",");
      }
      else if((each >= 201)&&( each <226)){
        printf(".");
      }
      else{
        printf(" ");
      }

      if(j == width-1){
        printf("\n");
      }
    }
  }

  return 0;
}

