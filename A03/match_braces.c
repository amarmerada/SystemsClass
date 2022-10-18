#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
    int braceType;
    int linenNum;
    int charNum;
    struct node* next;
    struct node* prev;

};



int stacksize = 0;
struct matched_braces{
    struct node* leftBrace;
    struct node* rightBrace;
};

void printNdPt(struct node* tp){
  printf("node of pointer: ln: %d cn: %d\n", tp->linenNum, tp->charNum);
}

void printNd(struct node tp){
  printf("node of pointer: ln: %d cn: %d\n", tp.linenNum, tp.charNum);
}

void printmb(struct matched_braces toPrint){
    struct node* L = toPrint.leftBrace;
    struct node* R = toPrint.rightBrace;
    printf("Found matching braces: (%d, %d) --> (%d, %d)\n", L->linenNum, L->charNum, R->linenNum, R->charNum );
}

struct node* pop(struct node* top){
  stacksize--;
  struct node* rtn = (struct node*)malloc(sizeof(struct node));
  rtn->braceType = top->braceType;
  rtn->linenNum = top->linenNum;
  rtn->charNum = top->charNum;
  *top = *top->prev;
  //printf("stack size: %d\n", stacksize);
  return rtn;
};


struct node* push(struct node newNode, struct node* top){ 
  stacksize++;
  struct node* oldTop = top; 
  top->next = &newNode;
  newNode.prev = oldTop;
  top = &newNode; 
  oldTop->next = &newNode;
  return top;
};

void clear(){
  
};

int main(int argc, char** argv) {
struct node head;
head.linenNum = 0;
head.charNum = 0;
head.next = NULL;
head.prev = &head;
head.braceType = 0;
struct node *top = &head;

char curr;
int line = 1;
int numChar = 1;
if (argc > 300){
  printf("Use single filename as command line argument");
}
else{
  FILE* fp;
  fp = fopen(argv[1], "r");
  printf("size argc: %d\n", argc);
  if (fp == NULL){
    printf("Could not open file\n");
    return(1);
  }
  while(!feof(fp)){ 
    curr = fgetc(fp); 
    numChar++;
    if(curr == '{'){ 
      struct node c;
      c.braceType = 0; 
      c.linenNum = line;
      c.charNum = numChar; 
      top = push(c, top);
    }
    if(curr =='}'){
      if(stacksize > 0){
        struct node *current = (struct node*)malloc(sizeof(struct node));
        current->braceType = 1;
        current->linenNum = line;
        current->charNum = numChar;
        struct matched_braces pair;
        //printNdPt(top);
        pair.leftBrace = pop(top); //top is not updated
        //printNdPt(top);
        pair.rightBrace = current;
        printmb(pair);
      }
      else{
        printf("found unmatched right brace: (%d, %d)\n", line, numChar);
      }
    }
    if(curr =='\n'){
      line++;
      numChar = 0;
    }
  }
  while(stacksize > 0){
    //printf("%d\n", stacksize);
    if(!(top == &head)){
      struct node *unmatched = pop(top);
      printf("found unmatched left brace: (%d, %d)\n", unmatched->linenNum, unmatched->charNum);
    }
  }



}
  return 0;
}
