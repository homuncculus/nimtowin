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

void showStatus (int tile[], int n)
{
    int i;
    printf ("Current Game Status -> ");
    for (i=0; i<n; i++)
        printf ("%c-->%d\t",65+i,tile[i]);
    printf("\n");
    return;
}

bool gameOver(int tile[], int n)
{
    int i;
    for (i=0; i<n; i++)
        if (tile[i]!=0)
            return (false);

    return (true);
}

int XOR(int tile[],int n)
{
  int i,diff=tile[0];

  for ( i = 1; i < n; i++)     diff=diff ^ tile[i];

  return diff;
}

void declareWinner(int Turn)
{
    if (Turn == YODA)
        printf ("\nHOOMAN won\n\n");
    else
        printf("\nYODA won\n\n");
    return;
}

void human_move(int tile[],int n,move *moves)
{
  int i;

  printf("Select non-zero stack to remove from: ");
  scanf("%d",&((*moves).p_index));

  (*moves).p_index--;

  if(tile[(*moves).p_index])
  {
        printf("Stones to remove (1-%d): ",tile[(*moves).p_index]);
        scanf("%d",&((*moves).stones_R));

        if(((*moves).stones_R<=tile[(*moves).p_index]) && (*moves).stones_R>0)
            tile[(*moves).p_index]-=(*moves).stones_R;
  }
}

void perfect_move(int tile[],int n,move *moves)
{
  int i,pop=XOR(tile,n);

  if (pop != 0)
    {
        for (i=0; i<n; i++)
        {
            if ((tile[i] ^ pop) < tile[i])
            {
                (*moves).p_index = i;
                (*moves).stones_R =
                                 tile[i]-(tile[i]^pop);
                tile[i] = (tile[i] ^ pop);
                break;
            }
        }
    }

    else
    {
        int n_index[n],count;

        for (i=0, count=0; i<n; i++)
            if (tile[i] > 0)
                n_index[count++] = i;

        (*moves).p_index = n_index[(rand() % (count))];
        (*moves).stones_R =
                 1 + (rand() % (tile[(*moves).p_index]));
        tile[(*moves).p_index] =
         tile[(*moves).p_index] - (*moves).stones_R;

        if (tile[(*moves).p_index] < 0)
            tile[(*moves).p_index]=0;
    }

}

void play_game(int tile[], int n, int Turn)
{
    printf("\nGAME STARTS\n\n");
    move moves;

    while (gameOver(tile, n) == false)
    {
        showStatus(tile, n);

        if (Turn == YODA)
        {
            perfect_move(tile, n, &moves);

            printf("COMPUTER removes %d stones from pile "
                   "at index %d\n", moves.stones_R,
                   moves.p_index);
            Turn = HOOMAN;
        }
        else
        {
            human_move(tile, n, &moves);

            printf("HUMAN removes %d stones from pile at "
                   "index %d\n", moves.stones_R,
                   moves.p_index);
            Turn = YODA;
        }
    }

    showStatus(tile, n);
    declareWinner(Turn);
    return;
}

int main(){
  int tile[]={3,4,5};
  play_game(tile,3,1);
}
