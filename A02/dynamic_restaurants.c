#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct restaurant {
  char name[50];
  int open;
  int close;
  double stars;
};
int main() {
  int restNum;
  printf("Enter the number of restuarants you would like to add: ");
  scanf("%d", &restNum);
  struct restaurant* inpList = (struct restaurant*)malloc(restNum * sizeof(struct restaurant));
  char nameHold[50];
  int openHold;
  int closeHold;
  double starsHold;
  for (int i = 0; i < restNum; i++){
    printf("Enter a name: ");
    scanf(" %[^\n]%*c",  nameHold);
    strcpy(inpList[i].name, nameHold);
    printf("Open time: ");
    scanf("%d%*c", &openHold);
    inpList[i].open = openHold;
    printf("Close time: ");
    scanf("%d%*c", &closeHold);
    inpList[i].close = closeHold;
    printf("Stars: ");
    scanf("%lf", &starsHold);
    inpList[i].stars = starsHold;
  }
  printf("Restaurant Directory: \n");
  for (int j = 0; j<restNum; j++){
     printf("\n%d) %s\tOpens: %d:00\tCloses: %d:00 \tStars: %.1lf\n", j, inpList[j].name, 
    inpList[j].open, inpList[j].close, inpList[j].stars);
  }
    free(inpList);
  return 0;
}
