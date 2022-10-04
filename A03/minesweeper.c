#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]) {

  int height = atoi(argv[1]);
  int width1 = atoi(argv[2]);
  double pb = atof(argv[3]);
  srand(time(0));
  int limit = pb * 100;
  int decision;
  int count;

  //printf("width: %d, height: %d, probability: %f\n", width, height, pb);


  if((pb > 1)|(pb < 0)){
    printf("\nprobability must be between 0 and 1\n");
  }
  else{
  char** board = (char**)malloc((height) * sizeof(char*)); // makes init array size width (columns)
  for (int i = 0; i < height; i++){
    board[i] = (char*)malloc(width1 * sizeof(char)); // creates row for each column
  }
  
  for(int j = 0; j < width1; j++){ // iterates  through columns
    for(int k = 0; k < height; k++){ // iterates through rows
      decision = rand() % 100;
      if(decision < limit){
        board[k][j] = 'X';
      }
      else{
        board[k][j] = '.';
      }
    }
  }

  for(int l = 0; l < height; l++){
    for(int m = 0; m < width1; m++){
      printf(" %c ", board[l][m]);
      if(m == width1 -1){
        printf("\n");
      }
    }
  }
  printf("\n\n\n");
  char** numMines = (char**)malloc((height) * sizeof(char*)); // makes init array size width (columns)
  for (int i = 0; i < height; i++){
    numMines[i] = (char*)malloc(width1 * sizeof(char)); // creates row for each column
  }
  
  for(int n = 0; n < width1; n++){
    for(int o = 0; o < height; o++){
      if(board[o][n] == 'X'){
        numMines[o][n] = 'X';
      }
      else{
        count = 0;
        if((n> 1) && (o > 1)){ 
          if(board[o-1][n-1] == 'X'){
            count++;
          }
        }
        if((n> 1)){ 
          if(board[o][n-1] == 'X'){
            count++;
          }
        }
        if((n> 1)&& (o < height -1)){ 
          if(board[o+1][n-1] == 'X'){
            count++;
          }
        }
        if((o > 1)){ 
          if(board[o-1][n] == 'X'){
            count++;
          }
        }
        if((n < width1 -1) && (o< height-1)){ 
          if(board[o+1][n] == 'X'){
            count++;
          }
        }
        if((o > 1) && (n < width1 -1)){ 
          if(board[o-1][n+1] == 'X'){
            count++;
          }
        }
        if((n < width1 -1)){ 
            if(board[o][n+1] == 'X'){
            count++;
          }
        }
        if((o < height-1) && (n < width1 -1)){ 
            if(board[o+1][n+1] == 'X'){
            count++;
          }
        }
        if(count > 0){
          count += 48;
           numMines[o][n] = (char) count;
        }
        else{
        numMines[o][n] = '.';
        }
      }
      
    }
  }
  for(int p = 0; p < height; p++){
    for(int q = 0; q < width1; q++){
      printf(" %c ", numMines[p][q]);
      if(q == width1 -1){
        printf("\n");
      }
    }
  }
  for(int i = 0; i < height; i++){
      free(numMines[i]);
      free(board[i]);
  }
  free(numMines);
  free(board);
  }
  return 0;
}
