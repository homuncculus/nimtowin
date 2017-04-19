#include <stdio.h>
#define SIZE 3
#define COM "YODA"

typedef struct a{
  int val;
  char pile;
}move;

void input(move tile[])
{
  for (size_t i = 0; i < SIZE; i++)
  {
    tile[i].val=i+3;
    tile[i].pile=i+65;
  }
}

int XOR(move tile[])
{
  int diff=0;
  for (size_t i = 0; i < SIZE; i++) {
    diff=diff^tile[i].val;
  }
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
