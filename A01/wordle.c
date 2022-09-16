#include <stdio.h>
#include <string.h>
#include <time.h>
#include "words.h" // header that defined chooseWord()

int testWord(char* guess, const char* word){
  char holdGuess;
  char holdWord;
  int matches = 0;
  for( int i = 0; i < 5; i++){
    holdGuess = guess[i];
    for(int j = 0; j < 5; j++){
      holdWord = word[j];
      if (holdGuess == holdWord){
        if (i == j){
          printf("%c is in the word AND in the correct spot!\n", holdGuess);
          matches++;
          break;
        }
        else{
          printf("%c is in the word, but not in the correct spot.\n", holdGuess);
          break;
        }
      }
      if (j == 4){
        printf("%c is not in the word\n", holdGuess);
      }
    }
  }
  if (matches == 5){
    printf("You guessed it! The word is %s\n", word);
  }
return matches;
}

; int main() {
  srand(time(0));
  const char* word = chooseWord();
  printf("Welcome to Wordle!\n");
  int guessCounter = 0;
  int success = 0;
  while(guessCounter < 6){
    printf("Please enter a 5-letter word:  ");
    char guess[6];
    scanf("%5s", guess);
    printf("You entered %s!\n", guess);
    success = testWord(guess, word);
    if (success == 5){
      break;
    }
  guessCounter++;
  }
  if (success != 5){
    printf("Sorry, you're all out of tries. The word was:  %s\n", word);
  }
  return 0;
}
