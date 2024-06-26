#include<conio.h>
#include<windows.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>

#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"
#define RST "\e[0m"

void consoleSize();
void welcomePage();
void cursorPos(int,int);
int startPage();
int gamePlay(char *,char *,char *);
void gamePageUI();
void updateUI(char,char *,int);
int gameLogic(int *);
int result(int,char *,char *);
int player(char *,char *,char *);
int help();
void goodByePage();

int columns,rows;

int main()
{ 
    int i=0;
    char playerIcon[]={'X','O'};
    char p1[11],p2[11];
    strcpy(p1,"Player 1");
    strcpy(p2,"Player 2");
    welcomePage();
    while(1)
    {
        switch (i)
        {
            case 0:
                i=startPage();
                break;
            case 1:
                i=gamePlay(playerIcon,p1,p2);
                break;
            case 2:
                i=player(playerIcon,p1,p2);
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
    for(int i=0;i<3;i++)
    {
        switch (i)
        {
        case 0:
            printf(RED);
            break;
        case 1:
            printf(YEL);
            break;
        case 2:
            printf(GRN);
            break;
        }
        cursorPos(columns/2-5,rows/2);
        printf("Welcome");
        cursorPos(columns/2+2+i,rows/2);
        printf(".");
        sleep(1);
    }
}

int startPage()
{
    char option;
    system("cls");
    consoleSize();
    cursorPos(columns/2-6,rows/2-7);
    printf(MAG"-: Welcome :-"WHT);
    cursorPos(columns/2-7,rows/2-5);
    printf("|1|  "GRN"| Start |"WHT);
    cursorPos(columns/2-7,rows/2-3);
    printf("|2|  "YEL"| Player |"WHT);
    cursorPos(columns/2-7,rows/2-1);
    printf("|3|  "BLU"| Help |"WHT);
    cursorPos(columns/2-7,rows/2+1);
    printf("|0|  "RED"| Exit |"WHT);
    cursorPos(columns/2-7,rows/2+3);
    printf(CYN">>>"WHT);
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

int gamePlay(char *playerIcon,char *p1,char *p2)
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
        printf("             ");
        cursorPos(2,rows-3);
        playerIcon[0]=='X'?j?printf(RED):printf(GRN):j?printf(GRN):printf(RED);
        j?printf("%s"WHT,p2):printf("%s"WHT,p1);
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
                        printf(CYN"1"WHT"______|"CYN"2"WHT"______|"CYN"3"WHT"______");
                        cursorPos(columns/2-11,rows/2+1);
                        printf(CYN"4"WHT"______|"CYN"5"WHT"______|"CYN"6"WHT"______");
                        cursorPos(columns/2-11,rows/2+4);
                        printf(CYN"7      "WHT"|"CYN"8      "WHT"|"CYN"9"WHT);
                        cursorPos(columns-33,rows-2);
                        printf("|H|  "WHT"| Hide Num |  "WHT"|0|  "BLU"| Back |"WHT);
                        hide=1;
                    }
                    else
                    {
                        cursorPos(columns/2-11,rows/2-2);
                        printf(WHT"_______|_______|_______");
                        cursorPos(columns/2-11,rows/2+1);
                        printf("_______|_______|_______");
                        cursorPos(columns/2-11,rows/2+4);
                        printf("       |       | "WHT);
                        cursorPos(columns-33,rows-2);
                        printf("|H|  "WHT"| Show Num |  "WHT"|0|  "BLU"| Back |"WHT);
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
                                return result(1,playerIcon,p1);
                            case 2:
                                return result(2,playerIcon,p2);
                        }
                    if(j==0)
                        j=1;
                    else
                        j=0;
                        
                    i++;
                    break;
            }
    }
    return result(3,playerIcon,p1);
}

void gamePageUI()
{
    // Game Page UI

    cursorPos(0,0);
    printf(MAG"-: Tic Tac Toe :-"WHT);
    cursorPos(2,rows-2);
    printf(CYN">>>"WHT);
    cursorPos(columns-33,rows-2);
    printf("|H|  "WHT"| Show Num |"WHT"  |0|  "BLU"| Back |"WHT);

    // Game Fild

    cursorPos(columns/2-4,rows/2-4); //line 1
    printf(WHT"|       |");
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
    printf("|       |"WHT);
}

void updateUI(char option,char *playerIcon,int j)
{
    playerIcon[j]=='X'?printf(GRN):printf(RED);
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
    printf(WHT);
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

int result(int i,char * playerIcon,char *p)
{
    char option;
    consoleSize();
    cursorPos(0,0);
    printf("                 ");
    cursorPos(columns/2-8,0);
    printf("-: Tic Tac Toe :- "WHT);
    cursorPos(2,rows-2);
    printf("     ");
    cursorPos(columns-33,rows-2);
    printf("                                 ");
    cursorPos(2,rows-3);
    printf("           ");
    cursorPos(columns/6-6,rows/2-6);
    printf(MAG"-: Result :-"WHT);
    cursorPos(columns/6-6,rows/2-4);
    playerIcon[0]=='X'?i==1?printf(GRN"%s Win"WHT,p):i==2?printf(RED"%s Win"WHT,p):(cursorPos(columns/6-2,rows/2-4),printf("Draw")):i==1?printf(RED"%s Win"WHT,p):i==2?printf(GRN"%s Win"WHT,p):(cursorPos(columns/6-2,rows/2-4),printf("Draw"));
    cursorPos(columns/6-10,rows/2-2);
    printf("|1|  "YEL"| Play Again |"WHT);
    cursorPos(columns/6-10,rows/2);
    printf("|2|  "BLU"| Start Page |"WHT);
    cursorPos(columns/6-10,rows/2+2);
    printf("|0|  "RED"| Exit |"WHT);
    cursorPos(columns/6-10,rows/2+4);
    printf(CYN">>>"WHT);
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

int player(char *playerIcon,char *p1,char *p2)
{
    char option;
    s3:
    system("cls");
    consoleSize();
    cursorPos(columns/2-6,rows/2-8);
    printf(MAG"-: Player :-"WHT);
    cursorPos(columns/2-7,rows/2-6);
    playerIcon[0]=='X'?printf(GRN):printf(RED);
    printf("# %s --> %c"WHT"   (A) Edit",p1,playerIcon[0]);
    cursorPos(columns/2-7,rows/2-4);
    playerIcon[1]=='O'?printf(RED):printf(GRN);
    printf("# %s --> %c"WHT"   (B) Edit",p2,playerIcon[1]);
    cursorPos(columns/2-7,rows/2-2);
    printf(WHT"|1|  "YEL"| Change |"WHT);
    cursorPos(columns/2-7,rows/2);
    printf("|2|  | Play |");
    cursorPos(columns/2-7,rows/2+2);
    printf("|0|  "BLU"| Back |"WHT);
    cursorPos(columns/2-7,rows/2+4);
    printf(CYN">>>"WHT);
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
                cursorPos(columns/2-7,rows/2-6);
                playerIcon[0]=='X'?printf(GRN):printf(RED);
                printf("# %s --> %c",p1,playerIcon[0]);
                cursorPos(columns/2-7,rows/2-4);
                playerIcon[1]=='O'?printf(RED):printf(GRN);
                printf("# %s --> %c"WHT,p2,playerIcon[1]);
                break;
            case '2':
                return 1;
            case 'A':
            {
                s1:
                char p[11];
                cursorPos(columns/2-18,rows/2+4);
                printf("%s",p1);
                cursorPos(columns/2-2,rows/2+4);
                printf("            ");  
                cursorPos(columns/2-2,rows/2+4);
                scanf("%s",p);
                if(strlen(p)>10)
                {
                    cursorPos(columns/2-3,rows/2+5);
                    printf(RED"Too Long !!"WHT);
                    goto s1;
                }
                else
                {
                    strcpy(p1,p);
                    goto s3;
                }
            }
            case 'a':
                goto s1;
            case 'B':
            {
                s2:
                char p[11];
                cursorPos(columns/2-18,rows/2+4);
                printf("%s",p2);
                cursorPos(columns/2-2,rows/2+4);
                printf("            ");  
                cursorPos(columns/2-2,rows/2+4);
                scanf("%s",p);
                if(strlen(p)>10)
                {
                    cursorPos(columns/2-3,rows/2+5);
                    printf(RED"Too Long !!"WHT);
                    goto s2;
                }
                else
                {
                    strcpy(p2,p);
                    goto s3;
                }
            }
            case 'b':
                goto s2;
            default:
                cursorPos(columns/2-2,rows/2+4);
                printf("            ");    
        }
    }
}

int help()
{
    printf(RED"NOT AVAILABLE !!\n"WHT);
    getch();
    return 0;
}

void goodByePage()
{
    system("cls");
    consoleSize();
    for(int i=0;i<3;i++)
    {
        switch (i)
        {
        case 0:
            printf(GRN);
            break;
        case 1:
            printf(YEL);
            break;
        case 2:
            printf(RED);
            break;
        }
        cursorPos(columns/2-5,rows/2);
        printf("Good Bye");
        cursorPos(columns/2+3+i,rows/2);
        printf(".");
        sleep(1);
    }
    printf(RST);
}