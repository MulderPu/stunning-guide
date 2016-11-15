#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

struct player{
	char name[10];
	char win[10];
	int score;
};

/*prototype*/
void playername(struct player *player1, struct player *player2);
void showboard(char board[8][8],int r,int c, char *black, char *white, char *cursor);
void chessposition(char board[8][8],char *black, char *white, char *cursor);
void moveposition(char *number, int x, int y, int *unable ,int r, int c,char board[8][8], char *memory,
					int *player1turn, int *player2turn, int *blackturn, int *whiteturn, char *black, char *white, char *cursor, int *pNumblack,int *pNumwhite,
					struct player *player1, struct player *player2,int *box1,int *box2,int *box3,int *box4,int *box5,int *box6,int *box7,int *box8, int row,
					int column, int count,struct player player[5]);
void printboard(int *x, int *y, int r, int c, char board[8][8], char *memory, int *player1turn,
				int *player2turn, int *blackturn, int *whiteturn, char *black, char *white,char *cursor,int *pNumblack, int *pNumwhite);
void tokencalculate(char board[8][8],int r, int c, char *black, char *white, int *pNumblack,int *pNumwhite);
void checkrules(int *box1,int *box2,int *box3,int *box4,int *box5,int *box6,int *box7,int *box8, int r, int c, int *x, int *y, char *black, char *white,
				int *player1turn, int *player2turn,int *available, char board[8][8], char *memory,int row,
					int column, int count);
void checkmove(int *player1move, int *player2move, int *anymove, int r, int c, int *available, int *player1turn, int *player2turn);
void checkwinner(int *pNumwhite, struct player *player1, struct player *player2, int *game, int *player1move, int *player2move, int r, int c, int *pNumblack, char board[8][8],struct player player[5]);
void printscore (struct player player[5]);

int main(void){
	/*Variables Declaration*/
	struct player player1;
	struct player player2;
	struct player player[5];

	int r=0;
	int c=0;
	int x=0;
	int y=0;
	int unable =0;
	int blackturn =0;
	int whiteturn =0;
	int player1turn = 0;
	int player2turn = 0;
	int pNumblack=2;
	int pNumwhite=2;
	int box1, box2, box3, box4, box5, box6, box7, box8;
	int row=0;
	int column=0;
	int count;

	char number;
	char board[8][8];
	char cursor = 'X';
	char black = '@';
	char white = 'O';
	char memory = ' ';

	printf("Previous winner:\n");
	printf("Name				Score\n");
	/*Call function*/
	printscore(player);
	playername(&player1, &player2);
	showboard(board, r,c,&black, &white,&cursor);
	moveposition(&number,x, y, &unable, r, c,board, &memory,&player1turn, &player2turn, &blackturn, &whiteturn,
				 &black, &white,&cursor,&pNumblack,&pNumwhite,&player1, &player2,&box1,&box2,&box3,&box4,&box5,
				 &box6,&box7,&box8, row, column, count,player);
	return 0;
}

/*show previous winner*/
void printscore (struct player player[5]){
	FILE *sb;
	char str[10];
	int num=0;
	int x=0;

	/*open file in read mode*/
	sb = fopen("scoreboard.txt","r");
	/*check if any error opening the file*/
	if (sb == NULL){
		/*close the file*/
		fclose(sb);

		/*open the file in write mode and create empty file*/
		sb = fopen("scoreboard.txt", "w");

		for (x=0;x<4;x++){
			if (x == 0){
				fprintf(sb,"-	 	 	 	 0");
			}
		}

		/*close the file again*/
		fclose(sb);

	  	/*open read mode*/
		sb=fopen("scoreboard.txt","r");
	}

	while (fscanf (sb,"%s				%2i", str, &num) ==2){
		printf("%s				%2i",str, num);
		printf("\n");
	}

	fclose (sb);
}

/*print the board again to move the cursor*/
void printboard(int *x, int *y,int r, int c, char board[8][8], char *memory, int *player1turn,
				int *player2turn, int *blackturn, int *whiteturn,  char *black, char *white, char *cursor,int *pNumblack, int *pNumwhite){
	/*check if x and clear x*/
 	for (r=0; r<8; r++){
		for (c=0; c<8; c++){
			/*count tokens*/
			tokencalculate(board,r, c, &*black, &*white, &*pNumblack,&*pNumwhite);

			if (board[r][c] == *cursor){
				board[r][c] = *memory;
			}
		}
	}

	/*place white token and move x back to original place*/
	if (*blackturn ==1){
		board[*x][*y] = *white;
		*blackturn =0;
		*memory = board[0][0];

		*player1turn =0;
		*player2turn = 1;
		board[0][0]=*cursor;
		*x=0;
		*y=0;
		board[0][0] = *memory;
	}
	/*place black token and move x back to original place*/
	else if (*whiteturn ==1){
		board[*x][*y]=*black;
		*whiteturn =0;
		*memory = board[0][0];

		*player2turn =0;
		*player1turn =1;
		board[0][0]=*cursor;
		*x=0;
		*y=0;
		board[0][0]=*memory;
	}else{
		*memory = board[0][0];
	}

	tokencalculate(board,r, c, &*black, &*white, &*pNumblack,&*pNumwhite);
	*memory = board[*x][*y];
	board[*x][*y] = *cursor;

	/*print board again*/
	for(r=0;r<8;r++){
		for(c=0;c<8;c++){
			printf("| %c",board[r][c]);
		}
		printf("|\n");
	}
}

/*Move the cursor on board*/
void moveposition(char *number, int x, int y, int *unable, int r, int c,char board[8][8], char *memory,int *player1turn,
					 int *player2turn, int *blackturn, int *whiteturn, char *black, char *white, char *cursor,int *pNumblack,int *pNumwhite,
					 struct player *player1, struct player *player2,int *box1,int *box2,int *box3,int *box4,int *box5,int *box6,int *box7,int *box8, int row,
					int column, int count,struct player player[5]){
	int game =1;
	while (game ==1){
		char answer;
		int spam =1;
		int clear =1;
		int anymove =0;
		int player1move=0;
		int player2move=0;
		int available =0;

		*box1=0;
		*box2=0;
		*box3=0;
		*box4=0;
		*box5=0;
		*box6=0;
		*box7=0;
		*box8=0;

		do{
		/*show each players turn*/
		if (*player1turn ==1){
			printf("%s, is your turn (white O)\n", (*player2).name);
		}else if (*player2turn ==1){
			printf("%s, is your turn (black @)\n", (*player1).name);
		}

		/*show number of token each player collected*/
		printf("The token collected by %s, Black(@) = %2i\n", (*player1).name, *pNumblack);
		printf("The token collected by %s, White(O) = %2i\n", (*player2).name, *pNumwhite);

		/*give instruction*/
		printf("\nPlease select your position:\n");
		printf("Press 6/d to move to the right\n");
		printf("Press 4/a to move to the left\n");
		printf("Press 8/w to move upward\n");
		printf("Press 2/s to move downward\n");
		printf("And press 5/e to comfirm your position\n");
		printf("Press Q to quit\n");

		/*get the key that the player press directly*/
		printf("Please enter your position:\n");
		*number = getch();

		/*left*/
		if (*number == '4'|| *number =='a'){
			if (y>0){
				y--;
			}
		}
		/*right*/
		else if (*number == '6' || *number =='d'){
	    	if (y<7){
				y++;
			}
		}
		/*up*/
		else if (*number == '8'|| *number =='w'){
			if (x>0){
				x--;
			}
		}
		/*down*/
		else if (*number == '2'|| *number =='s'){
			if (x<7){
				x++;
			}
		}
		/*enter*/
		else if (*number == '5' || *number =='e'){
		/*after comfirm, check the rules of the game*/
		checkrules(&*box1,&*box2,&*box3,&*box4,&*box5,&*box6,&*box7,&*box8, r,  c,  &x,  &y, &*black, &*white,
					&*player1turn, &*player2turn,&available,  board, &*memory, row,
						 column, count);

		/*check if space is available*/
		if (*box1==1 || *box2==1 || *box3==1 || *box4==1 || *box5==1 || *box6==1 || *box7==1 || *box8==1 ){
			/*if player1 then place black token*/
			if (*player1turn == 1){
				*blackturn =1;
			}
			/*if player2 then place white token*/
			else if (*player2turn == 1){
		 		*whiteturn =1;
			}
			spam =0;
		}else{
			checkwinner(&*pNumwhite, &*player1, &*player2, &game, &player1move, &player2move,  r,  c, &*pNumblack, board,player);
			*unable =1;
			clear =0;
		}

		}
		/*quit*/
		else if (*number == 'Q'){
			/*ask to quit*/
			printf("Are you sure you want to quit?(y/n) \n");
			answer = getch();

			if (answer =='y'){
				printf("\nAw~See you next time!\n");
				checkwinner(&*pNumwhite, &*player1, &*player2, &game, &player1move, &player2move,  r,  c, &*pNumblack, board,player);
				return;
			}
		}else{
			clear = 0;
		}

		if (clear == 1){
			system("cls");
		}else{
			system("cls");
			if (*unable == 1){
				printf("Here is not available.\n");
				*unable =0;
			}else{
				printf("Invalid Input.This key is not available to move.\n");
			}
			clear = 1;
		}

		/*to print the output into the board*/
		printboard(&x, &y ,r, c,board, &*memory, &*player1turn, &*player2turn, &*blackturn, &*whiteturn, &*black, &*white, &*cursor,&*pNumblack, &*pNumwhite);

		/*swap player turn*/
		if (*player1turn ==0){
			*player2turn =1;
		}else if (*player2turn ==0){
			*player1turn =1;
		}

		/*check player move*/
		while (anymove == 0){
			checkmove(&player1move, &player2move, &anymove, r, c, &available, player1turn, player2turn);
			if (player1move == 0 && player2move ==0){
				anymove==1;
			}
		}

		/*check for the winner*/
		if (*pNumblack + *pNumwhite ==64){
			checkwinner(&*pNumwhite, &*player1, &*player2, &game, &player1move, &player2move,  r,  c, &*pNumblack, board,player);
			break;
		}else if (*pNumblack ==0){
			checkwinner(&*pNumwhite, &*player1, &*player2, &game, &player1move, &player2move,  r,  c, &*pNumblack, board,player);
			break;
		}else if (*pNumwhite == 0){
			checkwinner(&*pNumwhite, &*player1, &*player2, &game, &player1move, &player2move,  r,  c, &*pNumblack, board,player);
			break;
		}
	}while(spam=1);
	}
}

/*check players whether have any move or not*/
void checkmove(int *player1move, int *player2move, int *anymove, int r, int c, int *available, int *player1turn, int *player2turn){
	if (*player2turn ==1){
		for (r=0; r<8;r++){
			for (c=0;c<8;c++){
				if (*available ==1 ){
					*player1move=1;
					*anymove=1;
					break;
				}
			}
		}

		if (*player1move==0){
			*player2turn=1;
			*anymove=1;
		}
	}else{
		for (r=0; r<8;r++){
			for (c=0;c<8;c++){
				if (*available ==1 ){
					*player2move=1;
					*anymove=1;
					break;
				}
			}
		}

		if (*player2move==0){
			*player1turn=1;
			*anymove=1;
		}
	}
}

/*check who win!*/
void checkwinner(int *pNumwhite, struct player *player1, struct player *player2, int *game, int *player1move, int *player2move, int r, int c, int *pNumblack, char board[8][8],struct player player[5]){
	FILE *sb;
	int winner =0;
	int emptycount =0;

	if(*pNumwhite == 0){
		printf("The token collected by %s, Black(@) = %2i\n", (*player1).name, *pNumblack);
		printf("The token collected by %s, White(O) = %2i\n", (*player2).name, *pNumwhite);
		printf("%s Wins!\n", (*player1).name);
		winner=1;
		*game=0;
	}else if (*pNumblack ==0){
		printf("The token collected by %s, Black(@) = %2i\n", (*player1).name, *pNumblack);
		printf("The token collected by %s, White(O) = %2i\n", (*player2).name, *pNumwhite);
		printf("%s Wins!\n", (*player2).name);
		winner=2;
		*game=0;
	}else{
		for (r=0; r<=8;r++){
			for (c=0; c<=8;c++){
				if (board[r][c] == ' '){
					emptycount +=1;
				}
			}
		}

		if (emptycount == 0){
			if (*pNumblack> *pNumwhite){
				printf("The token collected by %s, Black(@) = %2i\n", (*player1).name, *pNumblack);
				printf("The token collected by %s, White(O) = %2i\n", (*player2).name, *pNumwhite);
				printf("%s Wins!\n", (*player1).name);
				winner=1;
				*game =0;
			}else if (*pNumwhite>*pNumblack){
				printf("The token collected by %s, Black(@) = %2i\n", (*player1).name, *pNumblack);
				printf("The token collected by %s, White(O) = %2i\n", (*player2).name, *pNumwhite);
				printf("%s Wins!\n", (*player2).name);
				winner=2;
				*game=0;
			}else if (*pNumwhite==*pNumblack){
				printf("The token collected by %s, Black(@) = %2i\n", (*player1).name, *pNumblack);
				printf("The token collected by %s, White(O) = %2i\n", (*player2).name, *pNumwhite);
				printf("Well...It is a draw!!!\n");
				*game=0;
			}
		}
		/*quit and check*/
		else if (*player1move == 0 && *player2move == 0){
			if (*pNumblack> *pNumwhite){
				printf("The token collected by %s, Black(@) = %2i\n", (*player1).name, *pNumblack);
				printf("The token collected by %s, White(O) = %2i\n", (*player2).name, *pNumwhite);
				printf("%s Wins!\n", (*player1).name);
				winner=1;
				*game =0;
			}else if (*pNumwhite>*pNumblack){
				printf("The token collected by %s, Black(@) = %2i\n", (*player1).name, *pNumblack);
				printf("The token collected by %s, White(O) = %2i\n", (*player2).name, *pNumwhite);
				printf("%s Wins!\n", (*player2).name);
				winner=2;
				*game=0;
			}else if (*pNumwhite==*pNumblack){
				printf("The token collected by %s, Black(@) = %2i\n", (*player1).name, *pNumblack);
				printf("The token collected by %s, White(O) = %2i\n", (*player2).name, *pNumwhite);
				printf("Well...It is a draw!!!\n");
				*game=0;
			}
		}
	}

	if (winner ==1){
		strcpy(player[0].win, (*player1).name);
		player[0].score = *pNumblack;
	}else if (winner == 2){
		strcpy(player[0].win,(*player2).name);
		player[0].score=*pNumwhite;
	}

	/*To store winner name and score*/
	sb=fopen("scoreboard.txt","w");
	fprintf(sb, "%s				%2i\n", player[0].win, player[0].score);
	fclose(sb);

	FILE *fp;
	/*open file in read mode*/
	fp = fopen("storeboard.txt","r");
	/*check if any error opening the file*/
	if (fp == NULL){
		/*close the file*/
		fclose(fp);

		/*open the file in write mode to create empty file*/
		fp = fopen("storeboard.txt", "w");

		/*close the file again*/
		fclose(fp);

	  	/*open read mode*/
		fp=fopen("storeboard.txt","r");
	}

	/*To add new winner into the record*/
	fp=fopen("storeboard.txt","a");
	fprintf(fp, "%s				%2i\n", player[0].win, player[0].score);
	fclose(fp);
}

/*To calculate token of each player have*/
void tokencalculate(char board[8][8],int r, int c, char *black, char *white, int *pNumblack,int *pNumwhite){
	*pNumblack =0;
	*pNumwhite =0;

	for(r=0;r<8;r++){
		for(c=0;c<8;c++){
			/*collect number of black token*/
			if (board[r][c] == *black){
				*pNumblack =*pNumblack + 1;
			}
			/*collect number of white token*/
			else if (board[r][c] == *white){
				*pNumwhite = *pNumwhite + 1;
			}
		}
	}
}

/*ask for both players name*/
void playername(struct player *player1, struct player *player2){
	printf("Dear players,Welcome to Black and White Chess!\n");
	printf("Hello,Player 1, please enter your name (Token:Black):");
	scanf ("%s", &(*player1).name);
	printf("Hello,Player 2, please enter your name (Token:White):");
	scanf ("%s", &(*player2).name);
	printf("\nWelcome %s and %s has joined the game. Please enjoy and all the best!\n", (*player1).name, (*player2).name);
	printf("\n");
}

/*show chess board*/
void showboard(char board[8][8],int r,int c, char *black, char *white, char *cursor){
	for (r=0; r<8; r++){
		for (c=0; c<8;c++){
			board[r][c]=' ';
		}
	}

	chessposition(board,&*black, &*white, &*cursor);

	for(r=0;r<8;r++){
		for(c=0;c<8;c++){
			printf("| %c",board[r][c]);
		}
		printf("|\n");
	}
}

/*fix the chess position*/
void chessposition(char board[8][8], char *black, char *white, char *cursor){
	board[4][4]=*black;
	board[3][3]=*black;
	board[3][4]=*white;
	board[4][3]=*white;
	board[0][0]=*cursor;
}

/*set rules of the games*/
void checkrules(int *box1,int *box2,int *box3,int *box4,int *box5,int *box6,int *box7,int *box8, int r, int c, int *x, int *y, char *black, char *white,
				int *player1turn, int *player2turn, int *available, char board[8][8], char *memory,int row,
					int column, int count){
	count =0;
	*box1=0;
	*box2=0;
	*box3=0;
	*box4=0;
	*box5=0;
	*box6=0;
	*box7=0;
	*box8=0;


	if (*memory == *white || *memory == *black){
		*available =0;
	}else{
		for (count =0; count <8; count++){
			/*check all top left*/
			if (count ==0){
				if (*player1turn ==1){
					if (board[*x-1][*y-1] == *black){
						c = *y-1;
						for (r=*x-1; r>=0; r--){
							if (board[r][c] == ' '){
								break;
							}else if (board[r][c] == '|'){
								break;
							}else if (board[r][c] == *white){
								*available=1;
								*box1 =1;
								row =r;
								column = c;
								break;
							}
							c-=1;
						}
					}

					if (*box1 ==1){
						c = *y-1;
						for (r = *x-1;r>=row; r--){
							board[r][c] = *white;
							c-=1;
						}
					}
				}else if (*player2turn ==1){
					if (board[*x-1][*y-1] == *white){
						c = *y-1;
						for (r=*x-1; r>=0; r--){
							if (board[r][c] == ' '){
								break;
							}else if (board[r][c] == '|'){
								break;
							}else if (board[r][c] == *black){
								*available=1;
								*box1 =1;
								row =r;
								column = c;
								break;
							}
							c-=1;
						}
					}

					if (*box1 ==1){
						c = *y-1;
						for (r = *x-1; r>=row; r--){
							board[r][c] = *black;
							c-=1;
						}
					}
				}
			}
			/*check left all the way*/
			else if (count ==1){
				if (*player1turn ==1){
					if (board[*x][*y-1] == *black){
						r=*x;
						for (c=*y-1; c>=0; c--){
							if (board[r][c] == ' '){
								break;
							}else if (board[r][c] == '|'){
								break;
							}else if (board[r][c] == *white){
								*available=1;
								*box2=1;
								row = r;
								column = c;
								break;
							}
						}
					}

					if (*box2 ==1){
						r=*x;
						for (c=*y-1; c>=column; c--){
							board[r][c] = *white;
						}
					}
				}else if (*player2turn ==1){
					if (board[*x][*y-1] == *white){
						r=*x;
						for (c=*y-1; c>=0; c--){
							if (board[r][c] == ' '){
								break;
							}else if (board[r][c] == '|'){
								break;
							}else if (board[r][c] == *black){
								*available=1;
								*box2=1;
								row = r;
								column = c;
								break;
							}
						}
					}

					if (*box2 ==1){
						r=*x;
						for (c=*y-1; c>=column; c--){
							board[r][c] = *black;
						}
					}
				}
			}
			/*check bottom left to the end*/
			else if (count ==2){
				if (*player1turn ==1){
					if (board[*x+1][*y-1] == *black){
						c=*y-1;
						for (r=*x+1;r<8; r++){
							if (board[r][c] == ' '){
								break;
							}else if (board[r][c] == '|'){
								break;
							}else if (board[r][c] == *white){
								*available=1;
								*box3 =1;
								row=r;
								column =c;
								break;
							}
							c-=1;
						}
					}

					if (*box3 ==1){
						c = *y-1;
						for (r=*x+1; r<=row;r++){
							board[r][c] = *white;
							c-=1;
						}
					}
				}else if (*player2turn ==1){
					if (board[*x+1][*y-1] == *white){
						c=*y-1;
						for (r=*x+1;r<8; r++){
							if (board[r][c] == ' '){
								break;
							}else if (board[r][c] == '|'){
								break;
							}else if (board[r][c] == *black){
								*available=1;
								*box3 =1;
								row=r;
								column =c;
								break;
							}
							c-=1;
						}
					}

					if (*box3 ==1){
						c = *y-1;
						for (r=*x+1; r<=row;r++){
							board[r][c] = *black;
							c-=1;
						}
					}
				}
			}
			/*check bottom all the way down*/
			else if (count == 3){
				if (*player1turn ==1){
					if (board[*x+1][*y]== *black){
						c=*y;
						for (r=*x+1; r<8; r++){
							if (board[r][c] == ' '){
								break;
							}
							else if (board[r][c] == '|'){
								break;
							}else if (board[r][c] == *white){
								*available=1;
								*box4=1;
								row=r;
								column=c;
								break;
							}
						}
					}

					if (*box4 ==1){
						c=*y;
						for (r=*x+1; r<=row; r++){
							board[r][c] = *white;
						}
					}
				}else if (*player2turn ==1){
					if (board[*x+1][*y]== *white){
						c=*y;
						for (r=*x+1; r<8; r++){
							if (board[r][c] == ' '){
								break;
							}else if (board[r][c] == '|'){
								break;
							}else if (board[r][c] == *black){
								*available=1;
								*box4=1;
								row=r;
								column=c;
								break;
							}
						}
					}

					if (*box4 ==1){
						c=*y;
						for (r=*x+1; r<=row; r++){
							board[r][c] = *black;
						}
					}
				}
			}
			/*check bottom right*/
			else if (count ==4){
				if (*player1turn ==1){
					if (board[*x+1][*y+1] == *black){
						c=*y+1;
						for (r=*x+1; r<8;r++){
							if (board[r][c] == ' '){
								break;
							}
							else if (board[r][c] == '|'){
								break;
							}
							else if (board[r][c] == *white){
								*available=1;
								*box5 =1;
								row =r;
								column = c;
								break;
							}
							c+=1;
						}
					}

					if (*box5 ==1){
						c=*y+1;
						for (r=*x+1; r<=row;r++){
							board[r][c] = *white;
							c+=1;
						}
					}
				}else if (*player2turn ==1){
					if (board[*x+1][*y+1] == *white){
						c=*y+1;
						for (r=*x+1; r<8;r++){
							if (board[r][c] == ' '){
								break;
							}else if (board[r][c] == '|'){
								break;
							}else if (board[r][c] == *black){
								*available=1;
								*box5 =1;
								row =r;
								column = c;
								break;
							}
							c+=1;
						}
					}

					if (*box5 ==1){
					c=*y+1;
					for (r=*x+1; r<=row;r++){
						board[r][c] = *black;
						c+=1;
					}
				}
				}
			}
			/* check right side*/
			else if (count ==5){
				if (*player1turn ==1){
					if (board[*x][*y+1]==*black){
						r=*x;
						for (c=*y+1;c<8;c++){
							if (board[r][c] == ' '){
								break;
							}else if (board[r][c] == '|'){
								break;
							}else if (board[r][c] ==*white){
								*available=1;
								*box6 =1;
								row=r;
								column=c;
								break;
							}
						}
					}

					if (*box6==1){
						r=*x;
						for(c=*y+1; c<=column;c++){
							board[r][c] =*white;
						}
					}
				}else if (*player2turn ==1){
					if (board[*x][*y+1]==*white){
						r=*x;
						for (c=*y+1;c<8;c++){
							if (board[r][c] == ' '){
								break;
							}else if (board[r][c] == '|'){
								break;
							}else if (board[r][c] ==*black){
								*available=1;
								*box6 =1;
								row=r;
								column=c;
								break;
							}
						}
					}

					if (*box6==1){
						r=*x;
						for(c=*y+1; c<=column;c++){
							board[r][c] =*black;
						}
					}
				}
			}
			/*check top right all way long*/
			else if (count == 6){
				if (*player1turn ==1){
					if (board[*x-1][*y+1] == *black){
						c=*y+1;
						for (r=*x-1; r>=0;r--){
							if (board[r][c]== ' '){
								break;
							}else if (board[r][c] == '|'){
								break;
							}else if (board[r][c] == *white){
								*available=1;
								*box7=1;
								row=r;
								column=c;
								break;
							}
							c+=1;
						}
					}

					if (*box7 ==1){
						c=*y+1;
						for (r=*x-1; r>=row; r--){
							board[r][c] =*white;
							c+=1;
						}
					}
				}else if (*player2turn ==1){
					if (board[*x-1][*y+1] ==*white){
						c=*y+1;
						for (r=*x-1; r>=0;r--){
							if (board[r][c]== ' '){
								break;
							}else if (board[r][c] == '|'){
								break;
							}else if (board[r][c] == *black){
								*available=1;
								*box7=1;
								row=r;
								column=c;
								break;
							}
							c+=1;
						}
					}

					if (*box7 ==1){
						c=*y+1;
						for (r=*x-1; r>=row; r--){
							board[r][c] =*black;
							c+=1;
						}
					}
				}
			}
			/*check top side*/
			else if (count ==7){
				if (*player1turn ==1){
					if (board[*x-1][*y] == *black){
						c=*y;
						for (r=*x-1; r>=0; r--){
							if (board[r][c] == ' '){
								break;
							}
							else if (board[r][c] == '|'){
								break;
							}
							else if (board[r][c] == *white){
								*available=1;
								*box8 =1;
								row =r;
								column=c;
								break;
							}
						}
					}

					if (*box8 ==1){
						c=*y;
						for (r=*x-1; r>=row;r--){
							board[r][c] =*white;
						}
					}
				}
				else if (*player2turn ==1){
					if (board[*x-1][*y] == *white){
						c=*y;
						for (r=*x-1; r>=0; r--){
							if (board[r][c] == ' '){
								break;
							}
							else if (board[r][c] == '|'){
								break;
							}
							else if (board[r][c] == *black){
								*available=1;
								*box8 =1;
								row =r;
								column=c;
								break;
							}
						}
					}

					if (*box8 ==1){
						c=*y;
						for (r=*x-1; r>=row;r--){
							board[r][c] =*black;
						}
					}
				}
			}
		}
	}
}
