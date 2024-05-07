#include<conio.h>
#include<windows.h>
#include<unistd.h>
#include<stdio.h>

void consoleSize();
void welcomePage();
void cursorPos(int,int);
int startPage();
int gamePlay(char *);
void gamePageUI();
void updateUI(char,char *,int);
int gameLogic(int *);
int result(int);
int player(char *);
int help();
void goodByePage();

int columns,rows;

int main()
{ 
    int i=0;
    char playerIcon[]={'X','O'};
    welcomePage();
    while(1)
    {
        switch (i)
        {
            case 0:
                i=startPage();
                break;
            case 1:
                i=gamePlay(playerIcon);
                break;
            case 2:
                i=player(playerIcon);
                break;
            case 3:
                i=help();
                break;
            case 4:

                break;
            case 9:
                goto s2;
        }
    } 
    s2:
    goodByePage();
    return 0;     
}

void consoleSize()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void cursorPos(int x,int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void welcomePage()
{
    system("cls");
    consoleSize();
    cursorPos(columns/2-5,rows/2);
    printf("Welcome");
    for(int i=0;i<3;i++)
    {
        sleep(1);
        printf(".");
    }
    sleep(1);
}

int startPage()
{
    char option;
    system("cls");
    consoleSize();
    cursorPos(columns/2-6,rows/2-7);
    printf("-: Welcome :-");
    cursorPos(columns/2-7,rows/2-5);
    printf("|1|  | Start |");
    cursorPos(columns/2-7,rows/2-3);
    printf("|2|  | Player |");
    cursorPos(columns/2-7,rows/2-1);
    printf("|3|  | Help |");
    cursorPos(columns/2-7,rows/2+1);
    printf("|0|  | Exit |");
    cursorPos(columns/2-7,rows/2+3);
    printf(">>>");
    cursorPos(columns/2-3,rows/2+3);
    scanf("%c",&option);
    while(1)
        switch (option)
        {
            case '0':
                return 9;
            case '1':
                return 1;
            case '2':
                return 2;
            case '3':
                return 3;
            default:
                cursorPos(columns/2-3,rows/2+3);
                printf("     ");
                cursorPos(columns/2-3,rows/2+3);
                scanf("%c",&option);
        }
}

int gamePlay(char *playerIcon)
{
    int i=0,j=0,move[]={0,0,0,0,0,0,0,0,0},hide=0;
    char option;
    system("cls");
    consoleSize();
    gamePageUI();
    while(i<9)
    {
        s1:
        cursorPos(2,rows-3);
        printf("Player - ");
        j?printf("2"):printf("1");
        cursorPos(6,rows-2);
        scanf("%c",&option);
        cursorPos(6,rows-2);
        printf("     ");
        if((option>=48 && option<=57) || option==72 || option==104)
            switch (option)
            {
                case '0':
                    return 0;
                case 'h':
                    s2:
                    if(hide==0)
                    {
                        cursorPos(columns/2-11,rows/2-2);
                        printf("1______|2______|3______");
                        cursorPos(columns/2-11,rows/2+1);
                        printf("4______|5______|6______");
                        cursorPos(columns/2-11,rows/2+4);
                        printf("7      |8      |9");
                        cursorPos(columns-33,rows-2);
                        printf("|H|  | Hide Num |  |0|  | Back |");
                        hide=1;
                    }
                    else
                    {
                        cursorPos(columns/2-11,rows/2-2);
                        printf("_______|_______|_______");
                        cursorPos(columns/2-11,rows/2+1);
                        printf("_______|_______|_______");
                        cursorPos(columns/2-11,rows/2+4);
                        printf("       |       | ");
                        cursorPos(columns-33,rows-2);
                        printf("|H|  | Show Num |  |0|  | Back |");
                        hide=0;
                    }
                    break;
                case 'H':
                    goto s2;           
                default:
                    for(int k=0;k<=i;k++)
                        if(option-48==move[k])
                            goto s1;
                    move[i]=option-48;
                    updateUI(option,playerIcon,j);
                    if(i>=4)
                        switch (gameLogic(move))
                        {
                            case 0:
                                break;
                            case 1:
                                return result(1);
                            case 2:
                                return result(2);
                        }
                    j?j=0:j=1;
                    i++;
                    break;
            }
    }
    return result(3);
}

void gamePageUI()
{
    // Game Page UI

    cursorPos(0,0);
    printf("-: Tic Tac Toe :-");
    cursorPos(2,rows-2);
    printf(">>>");
    cursorPos(columns-33,rows-2);
    printf("|H|  | Show Num |  |0|  | Back |");

    // Game Fild

    cursorPos(columns/2-4,rows/2-4); //line 1
    printf("|       |");
    cursorPos(columns/2-4,rows/2-3);
    printf("|       |");
    cursorPos(columns/2-11,rows/2-2);
    printf("_______|_______|_______");//23
    cursorPos(columns/2-4,rows/2-1); // line 2
    printf("|       |");
    cursorPos(columns/2-4,rows/2);
    printf("|       |");
    cursorPos(columns/2-11,rows/2+1);
    printf("_______|_______|_______");//24
    cursorPos(columns/2-4,rows/2+2); // line 3
    printf("|       |");
    cursorPos(columns/2-4,rows/2+3);
    printf("|       |");
    cursorPos(columns/2-4,rows/2+4);
    printf("|       |");
}

void updateUI(char option,char *playerIcon,int j)
{
    switch (option)
    {
    case '1':
        cursorPos(columns/2-8,rows/2-3);
        printf("%c",playerIcon[j]);
        break;
    case '2':
        cursorPos(columns/2,rows/2-3);
        printf("%c",playerIcon[j]);
        break;
    case '3':
        cursorPos(columns/2+8,rows/2-3);
        printf("%c",playerIcon[j]);
        break;
    case '4':
        cursorPos(columns/2-8,rows/2);
        printf("%c",playerIcon[j]);
        break;
    case '5':
        cursorPos(columns/2,rows/2);
        printf("%c",playerIcon[j]);
        break;
    case '6':
        cursorPos(columns/2+8,rows/2);
        printf("%c",playerIcon[j]);
        break;
    case '7':
        cursorPos(columns/2-8,rows/2+3);
        printf("%c",playerIcon[j]);
        break;
    case '8':
        cursorPos(columns/2,rows/2+3);
        printf("%c",playerIcon[j]);
        break;
    case '9':
        cursorPos(columns/2+8,rows/2+3);
        printf("%c",playerIcon[j]);
        break;
    }
}

int gameLogic(int *move)
{
    for(int j=0;j<5;j+=2)
        for(int k=j+2;k<7;k+=2)
            for(int l=k+2;l<9;l+=2)
                if((move[j]+move[k]+move[l]==6) || (move[j]+move[k]+move[l]==24) || (move[j]*move[k]*move[l]==28) || (move[j]*move[k]*move[l]==162))
                    {
                        if(move[j]!=0 && move[k]!=0 && move[l]!=0)
                            return 1;
                    }
                else
                    if(move[j]+move[k]+move[l]==15)
                        if(move[j]==5||move[l]==5||move[k]==5)
                            return 1;
                                
    for(int j=1;j<4;j+=2)
        for(int k=j+2;k<6;k+=2)
            for(int l=k+2;l<8;l+=2)
                if((move[j]+move[k]+move[l]==6) || (move[j]+move[k]+move[l]==24) || (move[j]*move[k]*move[l]==28) || (move[j]*move[k]*move[l]==162))
                    {
                        if(move[j]!=0 && move[k]!=0 && move[l]!=0)
                            return 2;
                    }
                else
                    if(move[j]+move[k]+move[l]==15)
                        if(move[j]==5 || move[l]==5 || move[k]==5)
                            return 2;

    return 0;
}

int result(int i)
{
    char option;
    consoleSize();
    cursorPos(0,0);
    printf("                 ");
    cursorPos(columns/2-8,0);
    printf("-: Tic Tac Toe :- ");
    cursorPos(2,rows-2);
    printf("     ");
    cursorPos(columns-33,rows-2);
    printf("                                 ");
    cursorPos(2,rows-3);
    printf("           ");
    cursorPos(columns/6-6,rows/2-6);
    printf("-: Result :-");
    cursorPos(columns/6-6,rows/2-4);
    if(i==1)
        printf("Player 1 Win");
    else
        if(i==2)
            printf("Player 2 Win");
        else
        {
            cursorPos(columns/6-2,rows/2-4);
            printf("Draw");
        }
    cursorPos(columns/6-10,rows/2-2);
    printf("|1|  | Play Again |");
    cursorPos(columns/6-10,rows/2);
    printf("|2|  | Start Page |");
    cursorPos(columns/6-10,rows/2+2);
    printf("|0|  | Exit |");
    cursorPos(columns/6-10,rows/2+4);
    printf(">>>");
    while (1)
    {
        cursorPos(columns/6-6,rows/2+4);
        scanf("%c",&option);
        switch (option)
        {
            case '0':
              return 9;  
            case '1':
                return 1;
            case '2':
                return 0;
            default:
                cursorPos(columns/6-6,rows/2+4);
                printf("     ");
        }
    }
}

int player(char *playerIcon)
{
    char option;
    system("cls");
    consoleSize();
    cursorPos(columns/2-6,rows/2-6);
    printf("-: Player :-");
    cursorPos(columns/2-7,rows/2-4);
    printf("# Player 1 --> %c",playerIcon[0]);
    cursorPos(columns/2-7,rows/2-2);
    printf("# Player 2 --> %c",playerIcon[1]);
    cursorPos(columns/2-7,rows/2);
    printf("|1|  | Change |");
    cursorPos(columns/2-7,rows/2+2);
    printf("|0|  | Back |");
    cursorPos(columns/2-7,rows/2+4);
    printf(">>>");
    while(1)
    {
        cursorPos(columns/2-2,rows/2+4);
        scanf("%c",&option);
        switch (option)
        {
            case '0':
                return 0;
            case '1':
                char a;
                a=playerIcon[0];
                playerIcon[0]=playerIcon[1];
                playerIcon[1]=a;
                cursorPos(columns/2-7,rows/2-4);
                printf("# Player 1 --> %c",playerIcon[0]);
                cursorPos(columns/2-7,rows/2-2);
                printf("# Player 2 --> %c",playerIcon[1]);
            default:
                cursorPos(columns/2-2,rows/2+4);
                printf("     ");    
        }
    }
}

int help()
{
    printf("NOT AVAILABLE !!\n");
    getch();
    return 0;
}

void goodByePage()
{
    system("cls");
    consoleSize();
    cursorPos(columns/2-5,rows/2);
    printf("Good Bye");
    for(int i=0;i<3;i++)
    {
        sleep(1);
        printf(".");
    }
    sleep(1);
}