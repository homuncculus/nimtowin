#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define ERROR "WRONG INPUT BITCH....TRY AGAIN"
#define YODA 1
#define HOOMAN 2

typedef struct m
{
    int p_index;
    int stones_R;
}move;

int Rand() {

    time_t current_time;
    char* c_time_string;

    current_time = time(NULL);

    /* Convert to local time format. */
    c_time_string = ctime(&current_time);

    int t=(int)c_time_string[17]-48,o=(int)c_time_string[18]-48;

    return (t*10+o);
}
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

  while(1){
  printf("Select non-zero stack to remove from: ");
  scanf("%d",&((*moves).p_index));

  (*moves).p_index--;

  if(tile[(*moves).p_index])
  {
        printf("Stones to remove (1-%d): ",tile[(*moves).p_index]);
        scanf("%d",&((*moves).stones_R));

        if(((*moves).stones_R<=tile[(*moves).p_index]) && (*moves).stones_R>0){
            tile[(*moves).p_index]-=(*moves).stones_R;
            return;}

        else {
            printf("%s\n",ERROR);
            continue;
        }
  }
  else
  {
       printf("%s\n",ERROR);
        continue;
  }
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

        (*moves).p_index = n_index[(Rand() % (count))];
        (*moves).stones_R =
                 1 + (Rand() % (tile[(*moves).p_index]));
        tile[(*moves).p_index] =
         tile[(*moves).p_index] - (*moves).stones_R;

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
                   "at index %c\n", moves.stones_R,
                   moves.p_index+65);
            Turn = HOOMAN;
        }
        else
        {
            human_move(tile, n, &moves);

            printf("HUMAN removes %d stones from pile at "
                   "index %c\n", moves.stones_R,
                   moves.p_index+65);
            Turn = YODA;
        }
    }

    showStatus(tile, n);
    declareWinner(Turn);
    return;
}

int main(){
  int tile[]={Rand()%8+1,Rand()%7+1,Rand()%6+1};
  play_game(tile,3,1);
}
