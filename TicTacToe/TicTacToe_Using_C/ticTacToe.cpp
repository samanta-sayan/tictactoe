#include<conio.h>
#include<windows.h>
#include<unistd.h>
#include<iostream>

using namespace std;

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
    //welcomePage();
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
    cout<<"Welcome";
    for(int i=0;i<3;i++)
    {
        sleep(1);
        cout<<".";
    }
    sleep(1);
}

int startPage()
{
    char option;
    system("cls");
    consoleSize();
    cursorPos(columns/2-6,rows/2-7);
    cout<<"-: Welcome :-";
    cursorPos(columns/2-7,rows/2-5);
    cout<<"|1|  | Start |";
    cursorPos(columns/2-7,rows/2-3);
    cout<<"|2|  | Player |";
    cursorPos(columns/2-7,rows/2-1);
    cout<<"|3|  | Help |";
    cursorPos(columns/2-7,rows/2+1);
    cout<<"|0|  | Exit |";
    cursorPos(columns/2-7,rows/2+3);
    cout<<">>>";
    cursorPos(columns/2-3,rows/2+3);
    cin>>option;
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
                cout<<"     ";
                cursorPos(columns/2-3,rows/2+3);
                cin>>option;
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
        cout<<"Player - ";
        j?cout<<"2":cout<<"1";
        cursorPos(6,rows-2);
        cin>>option;
        cursorPos(6,rows-2);
        cout<<"     ";
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
                        cout<<"1______|2______|3______";
                        cursorPos(columns/2-11,rows/2+1);
                        cout<<"4______|5______|6______";
                        cursorPos(columns/2-11,rows/2+4);
                        cout<<"7      |8      |9";
                        cursorPos(columns-33,rows-2);
                        cout<<"|H|  | Hide Num |  |0|  | Back |";
                        hide=1;
                    }
                    else
                    {
                        cursorPos(columns/2-11,rows/2-2);
                        cout<<"_______|_______|_______";
                        cursorPos(columns/2-11,rows/2+1);
                        cout<<"_______|_______|_______";
                        cursorPos(columns/2-11,rows/2+4);
                        cout<<"       |       | ";
                        cursorPos(columns-33,rows-2);
                        cout<<"|H|  | Show Num |  |0|  | Back |";
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
    cout<<"-: Tic Tac Toe :-";
    cursorPos(2,rows-2);
    cout<<">>>";
    cursorPos(columns-33,rows-2);
    cout<<"|H|  | Show Num |  |0|  | Back |";

    // Game Fild

    cursorPos(columns/2-4,rows/2-4); //line 1
    cout<<"|       |";
    cursorPos(columns/2-4,rows/2-3);
    cout<<"|       |";
    cursorPos(columns/2-11,rows/2-2);
    cout<<"_______|_______|_______";//23
    cursorPos(columns/2-4,rows/2-1); // line 2
    cout<<"|       |";
    cursorPos(columns/2-4,rows/2);
    cout<<"|       |";
    cursorPos(columns/2-11,rows/2+1);
    cout<<"_______|_______|_______";//24
    cursorPos(columns/2-4,rows/2+2); // line 3
    cout<<"|       |";
    cursorPos(columns/2-4,rows/2+3);
    cout<<"|       |";
    cursorPos(columns/2-4,rows/2+4);
    cout<<"|       |";
}

void updateUI(char option,char *playerIcon,int j)
{
    switch (option)
    {
    case '1':
        cursorPos(columns/2-8,rows/2-3);
        cout<<playerIcon[j];
        break;
    case '2':
        cursorPos(columns/2,rows/2-3);
        cout<<playerIcon[j];
        break;
    case '3':
        cursorPos(columns/2+8,rows/2-3);
        cout<<playerIcon[j];
        break;
    case '4':
        cursorPos(columns/2-8,rows/2);
        cout<<playerIcon[j];
        break;
    case '5':
        cursorPos(columns/2,rows/2);
        cout<<playerIcon[j];
        break;
    case '6':
        cursorPos(columns/2+8,rows/2);
        cout<<playerIcon[j];
        break;
    case '7':
        cursorPos(columns/2-8,rows/2+3);
        cout<<playerIcon[j];
        break;
    case '8':
        cursorPos(columns/2,rows/2+3);
        cout<<playerIcon[j];
        break;
    case '9':
        cursorPos(columns/2+8,rows/2+3);
        cout<<playerIcon[j];
        break;
    }
}

int gameLogic(int *move)
{
    for(int j=0;j<5;j+=2)
        for(int k=j+2;k<7;k+=2)
            for(int l=k+2;l<9;l+=2)
                if((move[j]+move[k]+move[l]==6) || (move[j]+move[k]+move[l]==24) || (move[j]*move[k]*move[l]==28) || (move[j]*move[k]*move[l]==162))
                    
                        if(move[j]!=0 && move[k]!=0 && move[l]!=0)
                            return 1;
                    
                else
                    if(move[j]+move[k]+move[l]==15)
                        if(move[j]==5||move[l]==5||move[k]==5)
                            return 1;
                                
    for(int j=1;j<4;j+=2)
        for(int k=j+2;k<6;k+=2)
            for(int l=k+2;l<8;l+=2)
                if((move[j]+move[k]+move[l]==6) || (move[j]+move[k]+move[l]==24) || (move[j]*move[k]*move[l]==28) || (move[j]*move[k]*move[l]==162))
                    
                        if(move[j]!=0 && move[k]!=0 && move[l]!=0)
                            return 2;
                    
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
    cout<<"                 ";
    cursorPos(columns/2-8,0);
    cout<<"-: Tic Tac Toe :- ";
    cursorPos(2,rows-2);
    cout<<"     ";
    cursorPos(columns-33,rows-2);
    cout<<"                                 ";
    cursorPos(2,rows-3);
    cout<<"           ";
    cursorPos(columns/6-6,rows/2-6);
    cout<<"-: Result :-";
    cursorPos(columns/6-6,rows/2-4);
    if(i==1)
        cout<<"Player 1 Win";
    else
        if(i==2)
            cout<<"Player 2 Win";
        else
        {
            cursorPos(columns/6-2,rows/2-4);
            cout<<"Draw";
        }
    cursorPos(columns/6-10,rows/2-2);
    cout<<"|1|  | Play Again |";
    cursorPos(columns/6-10,rows/2);
    cout<<"|2|  | Start Page |";
    cursorPos(columns/6-10,rows/2+2);
    cout<<"|0|  | Exit |";
    cursorPos(columns/6-10,rows/2+4);
    cout<<">>>";
    while (1)
    {
        cursorPos(columns/6-6,rows/2+4);
        cin>>option;
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
                cout<<"     ";
        }
    }
}

int player(char *playerIcon)
{
    char option;
    system("cls");
    consoleSize();
    cursorPos(columns/2-6,rows/2-6);
    cout<<"-: Player :-";
    cursorPos(columns/2-7,rows/2-4);
    cout<<"# Player 1 --> "<<playerIcon[0];
    cursorPos(columns/2-7,rows/2-2);
    cout<<"# Player 2 --> "<<playerIcon[1];
    cursorPos(columns/2-7,rows/2);
    cout<<"|1|  | Change |";
    cursorPos(columns/2-7,rows/2+2);
    cout<<"|0|  | Back |";
    cursorPos(columns/2-7,rows/2+4);
    cout<<">>>";
    while(1)
    {
        cursorPos(columns/2-2,rows/2+4);
        cin>>option;
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
                cout<<"# Player 1 --> "<<playerIcon[0];
                cursorPos(columns/2-7,rows/2-2);
                cout<<"# Player 2 --> "<<playerIcon[1];
            default:
                cursorPos(columns/2-2,rows/2+4);
                cout<<"     ";    
        }
    }
}

int help()
{
    cout<<"NOT AVAILABLE !!\n";
    getch();
    return 0;
}

void goodByePage()
{
    system("cls");
    consoleSize();
    cursorPos(columns/2-5,rows/2);
    cout<<"Good Bye";
    for(int i=0;i<3;i++)
    {
        sleep(1);
        cout<<".";
    }
    sleep(1);
}