#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h> //used to create Random function

#define ERROR "WRONG INPUT BITCH....TRY AGAIN" // random shit
#define YODA 1   //COMPUTER "COOL RIGHT?"
#define HOOMAN 2 //USER

typedef struct m //needed data-structure
{
    int p_index; //index of the pile to remove from
    int stones_R;//no. of stones to be removed
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
void showStatus (int tile[], int n) // printing current game conditions
{
    int i;
    printf ("Current Game Status -> ");
    for (i=0; i<n; i++)
        printf ("%c-->%d\t",65+i,tile[i]);
    printf("\n");
    return;
}

bool gameOver(int tile[], int n) //returns true if there is no stone left
{
    int i;
    for (i=0; i<n; i++)
        if (tile[i]!=0) //returns false if a stack is nonzero
            return (false);

    return (true);
}

int XOR(int tile[],int n) // xor operator ^ used for all stacks
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

void human_move(int tile[],int n,move *moves) //taking input from user to make their move
{
  int i;

  while(1){ //loop until acceptable values are entered
  printf("Select non-zero stack to remove from: ");
  scanf("%d",&((*moves).p_index));

  (*moves).p_index--;

  if(tile[(*moves).p_index])
  {
        printf("Stones to remove (1-%d): ",tile[(*moves).p_index]);
        scanf("%d",&((*moves).stones_R));

        if(((*moves).stones_R<=tile[(*moves).p_index]) && (*moves).stones_R>0){
            tile[(*moves).p_index]-=(*moves).stones_R;
            return;} // return once stone is removed;

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

void perfect_move(int tile[],int n,move *moves) //actual algo used here
{
  int i,pop=XOR(tile,n); // pop stores the value of xor of all stacks

  if (pop != 0) // if Xor is nonzero
    {/* xor of pop with each stack is taken and condition
        is satisfied if it is less than no. of stones in
         the stack
       */
       //moves - new struct variable
        for (i=0; i<n; i++)
        {
            if ((tile[i] ^ pop) < tile[i]) { //phone karlena yaha pohochoge tab
                (*moves).p_index = i; //stores index of stack whose xor is less than no. of stones
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

        /* n_index will store the index of nonzero
        stack and count will count the
        number of nonzero stacks*/

        for (i=0, count=0; i<n; i++)
            if (tile[i] > 0)
                n_index[count++] = i;

        (*moves).p_index = n_index[(Rand() % (count))];//taking a random nonzero index
        (*moves).stones_R =
                 1 + (Rand() % (tile[(*moves).p_index]));//removing random stones

        /*updating the value of that stack */
        tile[(*moves).p_index] -= (*moves).stones_R;
    //all done
    }

}

void play_game(int tile[], int n, int Turn)
{
    printf("\nGAME STARTS\n\n");
    move moves; //it will store the values to use in output

    while (gameOver(tile, n) == false)
    {
        showStatus(tile, n);

        if (Turn == YODA)
        {
            /*NOw computer should make the perfect move*/

            perfect_move(tile, n, &moves);

            printf("COMPUTER removes %d stones from pile "
                   "at index %c\n", moves.stones_R,
                   moves.p_index+65);

            Turn = HOOMAN; //will change the turn for further use
        }
        else
        {
            /*take input from user to make the move*/
            human_move(tile, n, &moves);

            printf("HUMAN removes %d stones from pile at "
                   "index %c\n", moves.stones_R,
                   moves.p_index+65);
            //change the Turn
            Turn = YODA;
        }
    }

    showStatus(tile, n);
    declareWinner(Turn);
    return;
}

int main(){
 /* the values in tile at certain index defines the
  stones in that stack so here we gonna take it random*/
  int tile[]={Rand()%8+1,Rand()%7+1,Rand()%6+1};
/* to play the game we need the stacks,the number of stacks
  and gonna start with Computer to make the
  first move,"1" is for that*/
  play_game(tile,3,1);
}
