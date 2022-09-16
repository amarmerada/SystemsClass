#include <stdio.h>
#include <string.h>

struct restaurant {
  char name[50];
  int open;
  int close;
  double stars;
  char snacks[3][50];
}

; int main(){
  struct restaurant cafe;
  struct restaurant store; 
  struct restaurant fineDining;

  strcpy(cafe.name, "Rubi's Coffees and Sandwiches");
  cafe.open = 6;
  cafe.close = 17;
  cafe.stars = 4.5;

  strcpy(store.name, "The Southfield Store"); 
  store.open = 7;
  store.close = 16;
  store.stars = 1.5;
  
  strcpy(fineDining.name, "The Old Inn on the Green");
  fineDining.open = 11;
  fineDining.close = 2;
  fineDining.stars = 4.0;
  struct restaurant list[3];
  list[0] = cafe;
  list[1] = store;
  list[2] = fineDining;
  printf("Welcome to your list of local restaurants.\nWhat is the time (24 hour clock)?\n");
  int time = 0;
  scanf("%d", &time);
  for (int i = 0; i<3; i++){
    printf("\n%d) %s\tOpens: %d:00\tCloses: %d:00 \tStars: %g\n", i, list[i].name, 
    list[i].open, list[i].close, list[i].stars); 
  }
  printf("\nWhat restaurant would you like to visit? [0, 1, 2]  \n");
  int choice = 0;
  scanf("%d", &choice);
  struct restaurant selection = list[choice];
  int hours = 0;
  if(selection.open < selection.close){
    if (selection.open < time && time < selection.close){
      hours = selection.close - time;
      printf("%s is open for another %d hours\n", selection.name, hours);
    }
    else{
      hours = selection.open - time;
      printf("Sorry, %s won't open for another %d hours\n", selection.name, hours);
    }
  }
  else{
    if(selection.close < time && time < selection.open){
      hours = selection.open - time;
      printf("Sorry, %s won't open for another %d hours\n", selection.name, hours);
    }
    else{
      hours = selection.close - time;
      printf("%s is open for another %d hours\n", selection.name, hours);
    }
  }
  return 0;
}
