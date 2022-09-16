#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * encode(int n, char* str){
  char hold = ' ';
  char *word = malloc(sizeof(str));
  memset(word, 0, 10);
  for (int i = 0; i < sizeof(str); i++){ // took out -2
    hold = str[i];
    if (hold == '\0'){
      break;
    }
    hold = (((hold + n)-97)%26) + 97;
    word[i] = hold;
  }
  return word;
}

int main() {
  char str[12];
  int shift = 0;
  printf("Enter a word: ");
  scanf("%11s", str);
  printf("Enter a shift: ");
  scanf("%d", &shift);
  if(shift < 0){
    shift = 26 + shift;
  }
  char *encrypted = encode(shift, str);
  printf("Your cypher is %s\n", encrypted);
  return 0;
}
