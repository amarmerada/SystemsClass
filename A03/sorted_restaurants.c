#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//this program does not work and is very messy, normally I wouldn't have submitted it like this but time got away from me
//I got lost in all the pointers. My apologies to whoever has to grade this.


struct restaurant {
  char name[50];
  int open;
  int close;
  double stars;
  struct restaurant *next;
};

void clear(struct restaurant head){
    struct restaurant *current = &head;
    while(current->next != NULL){
      struct restaurant *following = head.next;
      free(current);
      current = following;
    }
}

struct restaurant* insert_sorted(struct restaurant *head, char* nameHold, int openHold, int closeHold, double starsHold){
  
  struct restaurant *new = (struct restaurant*)malloc(sizeof(struct restaurant));
  //
  strcpy(new->name, nameHold);
  new->open = openHold;
  new->close = closeHold;
  new->stars = starsHold;
  if(head->stars < new->stars){ // if new restaurant is the highest rated
    new->next = &head;
    head = new;
  }
  else{
  struct restaurant* current = &head;
  double ratingHold = current->stars;
        printf("\nhere ONE\n");
  while((ratingHold > new->stars) && (current->next != NULL)){ //searches through LL
        printf("\nhere\n");
        current = current->next;
        ratingHold = current-> stars;
  }
  //X
  new->next = current;
  
  }
  
  return head;
}





int main() {
  int restNum;
  char nameHold[50];
  int openHold;
  int closeHold;
  double starsHold;
  printf("Enter the number of restuarants you would like to add: ");
  scanf("%d", &restNum);
  struct restaurant *first;
  first->stars = 6.0;
  for(int i = 0; i < restNum; i++){
    printf("Enter a name: ");
  scanf(" %[^\n]%*c",  nameHold);
  printf("Open time: ");
  scanf("%d%*c", &openHold);
  printf("Close time: ");
  scanf("%d%*c", &closeHold);
  printf("Stars: ");
  scanf("%lf", &starsHold);
  first = insert_sorted(first, nameHold, openHold, closeHold, starsHold);
  }
  int j = 0;
  printf("\nhere TWO\n");
  while(first->next != NULL){
    printf("\n%d) %s\tOpens: %d:00\tCloses: %d:00 \tStars: %.1lf\n", j, first->name, 
    first->open, first->close, first->stars);
    j++;
    first = first->next;
  }
  clear(*first);
  return 0;
}
