#include <stdio.h>
#include <stdlib.h>

int main() {
  int pauseLen;
  printf("Enter pause length: ");
  scanf("%d", &pauseLen);
  printf("Enter speech: ");
  char buff[32];
  scanf("%31s", buff);
  char eachChar = buff[0];
  int charCount = 0;
  while(eachChar != '\0'){
    charCount++;
    eachChar = buff[charCount];
  }
  int multiplicand = charCount * (pauseLen+1) + 1;
  char* otpt;
  otpt = malloc(multiplicand* sizeof(char));
  int j = 0;
  int pattern = pauseLen + 1;
  int modulus;
  for (int i = 0; i < multiplicand-1; i++){
    modulus = i % pattern;
    if(modulus == 0){
      otpt[i] = buff[j];
      j++;
    }
    else{
      otpt[i] = '.';
    }
  }
  otpt[multiplicand-1] = '\0';
  printf("Entspeech is: %s \n", otpt);
  free(otpt);
  return 0;
}
