#include <stdio.h>

int main() {
  int matrix[4][4];
  int matrixHolder[4][4];
  int hold;
  int ind1;
  int ind2;
  for(int i =0; i<16; i++){
    scanf(" %d", &hold);
    ind1 = i/4;
    ind2 = i%4;
    matrix[ind1][ind2] = hold;
    matrixHolder[ind1][ind2] = hold;
  }
  int numShifts = 0;
  int largNoShift = 0;
  int largest = 0;
  int shiftResult = 0;
  ind1 = 0;
  ind2 = 0;
  int ind3 = 0;
  int ind4 = 0;
  for(int i = 0; i < 16; i++){
    ind1 = i/4;
    ind2 = i%4;
    ind3 = (i+1)/4;
    ind4 = (i+1)%4;
    if(ind3 == ind1){
        if(matrix[ind1][ind2] == matrix[ind3][ind4]){
            shiftResult = matrix[ind1][ind2] + matrix[ind3][ind4];
            if(shiftResult > 0){
              numShifts++;
            }
        if(shiftResult > largest){
            largest = shiftResult;
      }
    }
  }
  if((matrix[ind1][ind2]!= 0 )&& (matrix[ind3][ind4] == 0)){
    matrix[ind3][ind4] = matrix[ind1][ind2];
    
  }
  }
  for(int i =0; i<16; i++){
    ind1 = i/4;
    ind2 = i%4;
    matrix[ind1][ind2] = matrixHolder[ind1][ind2];
  }
  for(int i = 0; i < 12; i++){
    ind1 = i/4;
    ind2 = i%4;
    ind3 = ind1 + 1;
    ind4 = ind2;

    if((matrix[ind1][ind2] > largNoShift)){ 
      largNoShift = matrix[ind1][ind2];
    }
    if((matrix[ind3][ind4] > largNoShift)){
      largNoShift = matrix[ind3][ind4];
    }
    if(ind3 < 4){
        if(matrix[ind1][ind2] == matrix[ind3][ind4]){
            shiftResult = matrix[ind1][ind2] + matrix[ind3][ind4];
            if(shiftResult > 0){
              numShifts++;
            }
        if(shiftResult > largest){
            largest = shiftResult;
      }
    }
  }
  if((matrix[ind1][ind2]!= 0 )&& (matrix[ind3][ind4] == 0)){
    matrix[ind3][ind4] = matrix[ind1][ind2];
  }
  }
  if(numShifts > 0){
  printf("The largest value is: %d\n", largest);
  }
  else{
  printf("The largest value is: %d\n", largNoShift);
  }
  return 0;
}
