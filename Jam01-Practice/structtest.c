#include <stdio.h>
#include <string.h>

struct snack {
    char name[2]; // 1, 2, 3, 4 = 12, | 5, 6, 7, 8 = 16 || 9-12 = 20 | 13 -
    int quantity; // removing this subtracts 4
    float cost; // removing this subtracts 4
};
// when the struct has attributes other than the char array, char array allocates intervals of 4 bytes 
// s.t. when there are 3 elements in the array and when there are 4 elements in the array, there are 4 bytes
//allocated for the array, while 5,6,7, and 8 element arrays all have 8 bytes allocated.
// since each char is size 1, the array is allocating more than the array calls for for some reason
// UNLESS there are no other attributes to the struct, in which case 1 byte of memory is added per added
// element space to the array, which makes sense for chars which are 1 byte.
int main(){
    struct snack snack1;
    strcpy(snack1.name, "D");
    //snack1.quantity = 5;
    //snack1.cost = 4.00;
    int size = sizeof(snack1);
    printf("Size: %d\n", size);
};