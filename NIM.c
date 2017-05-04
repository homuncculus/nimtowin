#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h> //used to create Random function and nanosleep

#define ERROR "WRONG INPUT....TRY AGAIN\n" // random shit
#define TRUE 1
#define FALSE 0
#define QUIT -1

typedef struct m //needed data-structure
{
    int p_index; //index of the pile to remove from
    int stones_R;//no. of stones to be removed
}move;


char *PLAYER1,*PLAYER2;
void showStatus(int*, int);
bool gameOver(int*, int);
int XOR(int*, int);
void displayInstructions(void);
void declareWinner(int);
void human_move(int*, int, move*, int);
void perfect_move(int*, int, move*);
void human_game(void);
char *getPlayerName(short);
void jarvis_game(void);
int printHomeMenu(void);
int row_no(void);
void nim(void);
int Rand(void);

int main()
{
	nim();
}

void nim(){
	int choice;
   do {
       choice=printHomeMenu();

        switch(choice) {
           case 1:
               jarvis_game();
               break;
           case 2:
               human_game();
               break;
           case 3:
               system("clear");
               displayInstructions();
               break;
           case 4:
               break;
           default:
               printf(ERROR);
       }
       if(choice != 4)
           system("clear");
   } while(choice != 4);
}

int Rand() {

    time_t current_time;
    char* c_time_string;

    current_time = time(NULL);

    /* Convert to local time format. */
    c_time_string = ctime(&current_time);

    int t=(int)c_time_string[17]-48,o=(int)c_time_string[18]-48;

    return (t*10+o);
}
void showStatus (int tile[], int MAX) // printing current game conditions
{
    int i;
    printf("\n\n\t*******************************************************");
    printf("\n\t*\t~@~   N:I:M  G:A:M:E  I:S  O:N:!   ~@~        *\n");
    printf("\t*******************************************************\n");

    for (i=0; i<MAX; i++){
        printf ("\tRow %c  ",65+i);
        int j;
        for(j=0;j<tile[i];j++){
        	printf("\t+-+");
        }
		printf ("\n\t-----");
		for(j=0;j<tile[i];j++)
        	printf("\t|_|");
		printf("\n");
	}
    printf("\n\t*******************************************************");
    printf("\n");
    printf("\t*******************************************************\n");
}

bool gameOver(int tile[], int n) //returns true if there is no stone left
{
    int i;
    for (i=0; i<n; i++)
        if (tile[i]!=0) //returns false if a stack is nonzero
            return FALSE;

    return TRUE;
}

int XOR(int tile[],int n) // xor operator ^ used for all stacks
{
  int i,diff=tile[0];

  for ( i = 1; i < n; i++)     diff=diff ^ tile[i];

  return diff;
}

void displayInstructions() {
	struct timespec tm;
	tm.tv_sec=25;
	tm.tv_nsec=0;
    printf("\n\n********************************************************************************");
    printf("\n*              ~@~   INSTRUCTIONS FOR PLAYING NIM GAME   ~@~                  *\n");
    printf("********************************************************************************\n");
    printf("\n* This is a very simple game!");
    printf("\n* You have MAX 7 rows and few objects in each row");
    printf("\n* You select a row with objects available");
    printf("\n* You say how many objects you want to remove from that row");
    printf("\n* Remember, in one turn, you have to remove objects from only one row");
    printf("\n* Also, you have to remove at least one object in each of your turns");
    printf("\n* This continues till there are no objects in any row");
    printf("\n* The one who removes the last object loses and the other player wins!");
    printf("\n* Any moment you want to quit the game and go back, give -1 as input");
    printf("\n* The one who quit the game is declared as to lose the game and the other one - Winner!");
    printf("\n\t\tNow, start the game and get your brains to work!");
    printf("\n\t\t  (; ~@~ H:a:p:p:y ;;; G:a:m:i:n:g:! ~@~ ;) ");

    printf("\n\n******************************************************************************");
    printf("\n*                        END OF INSTRUCTIONS                                 *\n");
    printf("*******************************************************************************\n");
	nanosleep(&tm,NULL);
}

void declareWinner(int Turn)
{
	char *winner;
    if (Turn == 1){
		winner=(char*)malloc(strlen(PLAYER2));
        strcpy(winner,PLAYER2);}

    else{
		winner=(char*)malloc(strlen(PLAYER1));
        strcpy(winner,PLAYER1);}

    int i;
    int padding;
    int len = strlen(winner);
    char leftPadding[6];
    char rightPadding[6];
    struct timespec tm;
	tm.tv_sec=15;
	tm.tv_nsec=0;

    padding = (14 - len) / 2;
    for(i = 0;i < padding;i++) {
        leftPadding[i] = ' ';
    }
    leftPadding[i] = '\0';

    padding = (14 - len) - padding;
    for(i = 0;i < padding;i++) {
        rightPadding[i] = ' ';
    }
    rightPadding[i] = '\0';

    system("clear");
    printf("\n\n\t\t************************************************");
    printf("\n\t\t\t    *\t\t     *");
    printf("\n\t\t\t    *\t\t     *");
    printf("\n\t\t\t    *\t\t     *");
    printf("\n\t\t\t    *\t\t     *");
    printf("\n\t\t\t    *\t\t     *");
    printf("\n\t\t\t    *\t\t     *");
    printf("\n\t\t************************************************");
    printf("\n\t\t************************************************");
    printf("\n\t\t **\t\t\t\t\t     **");
    printf("\n\t\t **\t\t\t\t\t     **");
    printf("\n\t\t **\t      %s%s WINS!%s           **", leftPadding, winner, rightPadding);
    printf("\n\t\t **\t\t\t\t\t     **");
    printf("\n\t\t **\t %sCONGRATULATIONS %s!%s     **", leftPadding, winner, rightPadding);
    printf("\n\t\t **\t\t\t\t\t     **");
    printf("\n\t\t **\t\t\t\t\t     **");
    printf("\n\t\t************************************************");
    printf("\n\t\t************************************************\n\n\n");
    nanosleep(&tm,NULL);
}


void human_move(int tile[],int n,move *moves,int Turn) //taking input from user to make their move
{
  struct timespec tm;
	tm.tv_sec=3;
	tm.tv_nsec=0;
  while(1){ //loop until acceptable values are entered
  printf("Select non-zero stack to remove from: ");
  //fflush(stdin);
  char c;
  fflush(stdin);
  scanf("%c",&c);
  c=toupper(c);
  if(c>='A' && c<='Z')
  (*moves).p_index=c-65;

  else {
	  printf(ERROR);
	  continue;}

  if(tile[(*moves).p_index])
  {
        printf("Stones to remove (1-%d): ",tile[(*moves).p_index]);
        scanf("%d",&((*moves).stones_R));

        if(((*moves).stones_R<=tile[(*moves).p_index]) && (*moves).stones_R>0){
            tile[(*moves).p_index]-=(*moves).stones_R;
            return;} // return once stone is removed;

        else {if((*moves).stones_R == QUIT) {
				system("clear");
				printf("\n\n\n");
                printf("\n\t\t<<< YOU ENTERED -1 REQUESTING TO QUIT THE GAME,"
                "\n\t\t\t\t IF YOU QUIT,"
                "\n\t\t THE OTHER PLAYER WILL BE DECLARED WINNER >>>");
                printf("\n");
                nanosleep(&tm,NULL);
                system("clear");
                declareWinner(Turn);
                exit(0);
                }

            printf(ERROR);
            continue;
        }
  }
  else
  {
       printf(ERROR);
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
        {/*I'll prefer to keep this a secret
			so that you can't win against computer*/
            if ((tile[i] ^ pop) < tile[i]) {
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


void human_game()
{
	//printf("\nGAME STARTS\n\n");
    move moves; //it will store the values to use in output
    char t[15];
    int i;
    printf("enter player1 username: ");
    scanf("%s",t);
    PLAYER1=(char*)malloc(strlen(t));
    strcpy(PLAYER1,t);
    while(PLAYER1[i]) {
        PLAYER1[i] = toupper(PLAYER1[i]);
        i++;}
    printf("enter player2 username: ");
    scanf("%s",t);
    PLAYER2=(char*)malloc(strlen(t));
    strcpy(PLAYER2,t);
    while(PLAYER2[i]) {
        PLAYER2[i] = toupper(PLAYER2[i]);
        i++;}

    int n=row_no(),*tile=NULL;

	tile=(int*)malloc(n*sizeof(int));

    for(i=0;i<n;i++) tile[i]=Rand()%(5+i)+1;

    int Turn=Rand()%2;

       while (gameOver(tile, n) == false)
    {
        showStatus(tile, n);

        if (Turn == 1)
        {
			printf("\n\nIt is your turn %s...\n", PLAYER1);
            human_move(tile, n, &moves, Turn);

            printf("%s removes %d stones from pile "
                   "at index %c\n",PLAYER1, moves.stones_R,
                   moves.p_index+65);
            Turn = 2; //will change the turn for further use
        }
        else
        {
			printf("\n\nIt is your turn %s...\n", PLAYER2);
            /*take input from user to make the move*/
            human_move(tile, n, &moves, Turn);

            printf("%s removes %d stones from pile at "
                   "index %c\n",PLAYER2, moves.stones_R,
                   moves.p_index+65);
            //change the Turn
            Turn = 1;
        }
    }
    showStatus(tile, n);
    declareWinner(Turn);
}


void jarvis_game()
{
   // printf("\nGAME STARTS\n\n");
    move moves; //it will store the values to use in output
    struct timespec tm;
	tm.tv_sec=4;
	tm.tv_nsec=0;
	int i;
    PLAYER1=(char*)malloc(7);
    strcpy(PLAYER1,"JARVIS");
    char t[15];
    printf("PLEASE ENTER USERNAME : ");
    scanf("%s",t);
    PLAYER2=(char*)malloc(strlen(t));
    strcpy(PLAYER2,t);
    while(PLAYER2[i]) {
        PLAYER2[i] = toupper(PLAYER2[i]);
        i++;}

    int n=row_no(),*tile=NULL;

    tile=(int*)malloc(n*sizeof(int));

    for(i=0;i<n;i++) tile[i]=Rand()%(5+i)+1;

    int Turn=Rand()%2;

	if(XOR(tile,n)==0) Turn=2;

	printf("\n\n\t<<< EVERYTHING IS SET FOR THE GAME! ALL THE BEST %s >>>\n", PLAYER2);
    nanosleep(&tm,NULL);

    while (gameOver(tile, n) == FALSE)
    {
		if(Turn == 1){
		 printf("\n\n\t\t<<< JARVIS HAS DECIDED THE MOVE!>>>"
		 " \n\t<<< WAIT TO FIND WHAT JARVIS IS GOING TO PLAY! >>>\n");
		 nanosleep(&tm,NULL);}

        showStatus(tile, n);

        if (Turn == 1)
        {
            /*NOw computer should make the perfect move*/

            perfect_move(tile, n, &moves);

            printf("%s removes %d stones from pile "
                   "at index %c\n",PLAYER1, moves.stones_R,
                   moves.p_index+65);
            nanosleep(&tm,NULL);

            Turn = 2; //will change the turn for further use
        }
        else
        {
			printf("\n\nIt is your turn %s...\n", PLAYER2);
            /*take input from user to make the move*/
            human_move(tile, n, &moves, Turn);
            //change the Turn
            Turn = 1;
        }
    }

    showStatus(tile, n);
    declareWinner(Turn);
}


int printHomeMenu() {
	system("clear");
    printf("\n\n\t\t***********************************");
    printf("\n\t\t*\t  NIM GAME MENU      \t  *\n");
    printf("\t\t***********************************\n");

    printf("\t\t*\t\t\t          *");
    printf("\n\t\t*    1. Play against Jarvis       *");
    printf("\n\t\t*    2. Play against a friend     *");
    printf("\n\t\t*    3. Instructions              *");
    printf("\n\t\t*    4. Exit                      *");

    printf("\n\t\t*\t\t\t          *");
    printf("\n\t\t***********************************\n");
    printf("\t\t*\t                          *");
    printf("\n\t\t***********************************\n");
	int choice;
	printf("\t\tINPUT YOUR CHOICE:");
	scanf("%d",&choice);

	return choice;
}

int row_no(){

    printf("HOW MANY STACK WOULD YOU PREFER?\n");
    int flag;
    while(1){
	printf("\t\t3\t\t5\t\t7\nYour choice?: ");
    scanf("%d",&flag);
    switch(flag)
    {
        case 3: return 3;
        case 5: return 5;
        case 7: return 7;
        default:printf(ERROR);
				printf("\n");
                continue;
    };
    }
}
