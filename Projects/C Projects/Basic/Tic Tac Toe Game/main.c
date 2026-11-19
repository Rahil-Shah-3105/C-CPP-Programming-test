// Autor : Nemonet TYP
// Title: Tic Tac Toe Game project in C
// PROJECT FOR C/C++ PROGRAMMING TUTORIAL


#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include <windows.h>

int board[10] = {2,2,2,2,2,2,2,2,2,2};
int turn = 1,flag = 0;
int player,comp;

void menu();
void go(int n);
void start_game();
void check_draw();
void draw_board();
void player_first();
void put_X_O(char ch,int pos);
COORD coord= {0,0}; // this is global variable
//center of axis is set to the top left cornor of the screen
void gotoxy(int x,int y)
{
	fprintf(stderr, "[ERROR] >>> Entering gotoxy(x=%d,y=%d)\n", x, y);
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void main()
{
	fprintf(stderr, "[ERROR] >>> Entering main()\n");
    system("cls");
    menu();
	fprintf(stderr, "[WARN] <<< Exiting main()\n");
    getch();

}

void menu()
{
	fprintf(stderr, "[ERROR] >>> Entering menu()\n");
    int choice;
    system("cls");
    printf("\n--------MENU--------");
    printf("\n1 : Play with X");
    printf("\n2 : Play with O");
    printf("\n3 : Exit");
    printf("\nEnter your choice:>");
    scanf("%d",&choice);
    turn = 1;
	fprintf(stderr, "[DEBUG] menu(): turn → %d\n", turn);
    switch (choice)
    {
    case 1:
        player = 1;
		fprintf(stderr, "[ERROR] menu(): player → %d\n", player);
		fprintf(stderr, "[DEBUG] menu(): player → %d\n", player);
        comp = 0;
        player_first();
		fprintf(stderr, "[DEBUG] menu(): comp → %d\n", comp);
        break;
    case 2:
        player = 0;
        comp = 1;
		fprintf(stderr, "[ERROR] menu(): comp → %d\n", comp);
        start_game();
        break;
    case 3:
        exit(1);
    default:
        menu();
    }
}

int make2()
{
	fprintf(stderr, "[ERROR] >>> Entering make2()\n");
    if(board[5] == 2)
        return 5;
    if(board[2] == 2)
        return 2;
    if(board[4] == 2)
        return 4;
    if(board[6] == 2)
        return 6;
    if(board[8] == 2)
        return 8;
    return 0;
}

int make4()
{
	fprintf(stderr, "[ERROR] >>> Entering make4()\n");
    if(board[1] == 2)
        return 1;
    if(board[3] == 2)
        return 3;
    if(board[7] == 2)
        return 7;
    if(board[9] == 2)
        return 9;
    return 0;
}

int posswin(int p)
{
fprintf(stderr, "[ERROR] >>> Entering posswin(p=%d)\n", p);
// p==1 then X   p==0  then  O
    int i;
    int check_val,pos;

    if(p == 1)
        check_val = 18;
    else
        check_val = 50;
		fprintf(stderr, "[ERROR] posswin(p=%d): check_val → %d\n", p, check_val);
		fprintf(stderr, "[DEBUG] posswin(p=%d): check_val → %d\n", p, check_val);

    i = 1;
    while(i<=9)//row check
    {
        if(board[i] * board[i+1] * board[i+2] == check_val)
        {
            if(board[i] == 2)
                return i;
            if(board[i+1] == 2)
                return i+1;
            if(board[i+2] == 2)
                return i+2;
        }
        i+=3;
    }

    i = 1;
    while(i<=3)//column check
    {
        if(board[i] * board[i+3] * board[i+6] == check_val)
        {
            if(board[i] == 2)
                return i;
            if(board[i+3] == 2)
                return i+3;
            if(board[i+6] == 2)
                return i+6;
        }
        i++;
    }

    if(board[1] * board[5] * board[9] == check_val)
    {
        if(board[1] == 2)
            return 1;
        if(board[5] == 2)
            return 5;
        if(board[9] == 2)
            return 9;
    }

    if(board[3] * board[5] * board[7] == check_val)
    {
        if(board[3] == 2)
            return 3;
        if(board[5] == 2)
            return 5;
        if(board[7] == 2)
            return 7;
    }
	fprintf(stderr, "[WARN] <<< Exiting posswin(p=%d)\n", p);
    return 0;
}

void go(int n)
{
	fprintf(stderr, "[ERROR] >>> Entering go(n=%d)\n", n);
    if(turn % 2)
        board[n] = 3;
    else
        board[n] = 5;
    turn++;
	fprintf(stderr, "[WARN] <<< Exiting go(n=%d)\n", n);
}

void player_first()
{
	fprintf(stderr, "[ERROR] >>> Entering player_first()\n");
    int pos;

    check_draw();
    draw_board();
    gotoxy(30,18);
    printf("Your Turn :> ");
    scanf("%d",&pos);

    if(board[pos] != 2)
        player_first();

    if(pos == posswin(player))
    {
        go(pos);
        draw_board();
        gotoxy(30,20);
        //textcolor(128+RED);
        printf("Player Wins");
        getch();
        exit(0);
    }

    go(pos);
    draw_board();
    start_game();
	fprintf(stderr, "[WARN] <<< Exiting player_first()\n");
}

void start_game()
{
fprintf(stderr, "[ERROR] >>> Entering start_game()\n");
// p==1 then X   p==0  then  O
    if(posswin(comp))
    {
        go(posswin(comp));
        flag = 1;
		fprintf(stderr, "[DEBUG] start_game(): flag → %d\n", flag);
    }
    else if(posswin(player))
        go(posswin(player));
    else if(make2())
        go(make2());
    else
        go(make4());
    draw_board();

    if(flag)
    {
        gotoxy(30,20);
        //textcolor(128+RED);
        printf("Computer wins");
        getch();
    }
    else
        player_first();
		fprintf(stderr, "[WARN] <<< Exiting start_game()\n");
}

void check_draw()
{
	fprintf(stderr, "[ERROR] >>> Entering check_draw()\n");
    if(turn > 9)
    {
        gotoxy(30,20);
        //textcolor(128+RED);
        printf("Game Draw");
        getch();
        exit(0);
    }
	fprintf(stderr, "[WARN] <<< Exiting check_draw()\n");
}

void draw_board()
{
	fprintf(stderr, "[ERROR] >>> Entering draw_board()\n");
    int j;

    for(j=9; j<17; j++)
    {
        gotoxy(35,j);
        printf("|       |");
    }
    gotoxy(28,11);
    printf("-----------------------");
    gotoxy(28,14);
    printf("-----------------------");

    for(j=1; j<10; j++)
    {
        if(board[j] == 3)
            put_X_O('X',j);
        else if(board[j] == 5)
            put_X_O('O',j);
    }
	fprintf(stderr, "[WARN] <<< Exiting draw_board()\n");
}

void put_X_O(char ch,int pos)
{
	fprintf(stderr, "[ERROR] >>> Entering put_X_O(ch=%c,pos=%c)\n", ch, pos);
    int m;
    int x = 31, y = 10;

    m = pos;

    if(m > 3)
    {
        while(m > 3)
        {
            y += 3;
            m -= 3;
        }
    }
    if(pos % 3 == 0)
        x += 16;
    else
    {
        pos %= 3;
        pos--;
        while(pos)
        {
            x+=8;
            pos--;
        }
    }
    gotoxy(x,y);
    printf("%c",ch);
	fprintf(stderr, "[WARN] <<< Exiting put_X_O(ch=%c,pos=%c)\n", ch, pos);
}
