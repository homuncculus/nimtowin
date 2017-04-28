#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define YODA 1
#define HOOMAN 2

typedef struct m
{
    int p_index;
    int stones_R;
}move;

void showStatus (int piles[], int n)
{
    int i;
    printf ("Current Game Status -> ");
    for (i=0; i<n; i++)
        printf ("%c-->%d\t",65+i,piles[i]);
    printf("\n");
    return;
}

int XOR(int tile[],int n)
{
  int i,diff=tile[0];
  
  for ( i = 1; i < n; i++)     diff=diff ^ tile[i];
  
  return diff;
}

void perfect_move(move tile[])
{
  int i=0,pop=XOR(tile);

  while((tile[i].val ^ pop > tile[i].val)&&(i>0)) i++;

  tile[i].val=tile[i].val-pop;
  printf("%s removed %d from pile %c",COM,pop,tile[i].pile);
}

int main(){
  move tile[SIZE];
  input(tile);
  perfect_move(tile);
}
