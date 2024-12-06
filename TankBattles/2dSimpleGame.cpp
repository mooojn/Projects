#include<iostream>
#include <windows.h>
using namespace std;
void printBoard(char[][21]);
void printBorder(char[][21]);
void fire(char[][21]);
void moveFire(char[][21], int step); 
void removeFire(char[][21]);
void movePlayer(char[][21], char);
void moveEnemy(char [][21], char, char);
bool wallNotDetected(char[][21]); // for fire
void moveFire(char Board[][21]);
int random(int min, int max);      /// for random enemy movement
int main()
{
    char Board[10][21] = {"####################",
                          "#               x  #", 
                          "#     e            #", 
                          "#                  #", 
                          "#                  #", 
                          "#                  #", 
                          "#        p         #", 
                          "#                  #",  
                          "####################"};
    bool bulletFired = false;
    printBoard(Board);
    while(true)
    {
        if(GetAsyncKeyState(VK_LEFT))
        {
            movePlayer(Board, 'l');
            printBoard(Board);
        }
        if(GetAsyncKeyState(VK_RIGHT))
        {
            movePlayer(Board, 'r');
            printBoard(Board);
        }
        if (GetAsyncKeyState(VK_SPACE))
        {
            if(!bulletFired)
            {
                fire(Board);    
                printBoard(Board);       
                bulletFired = true;
            }
        }
        if (bulletFired)  /// if true then move fire
        {
            if (wallNotDetected(Board))
            {
                moveFire(Board);
                printBoard(Board);
            }
            else
            {
                bulletFired = false;
                printBoard(Board);
            }
        }
        int a=random(0,1);
        if (a==0)
        {
            moveEnemy(Board, 'e', 'r');
            moveEnemy(Board, 'x', 'l');
            printBoard(Board);
        }
        else
        {
            moveEnemy(Board, 'e', 'l');
            moveEnemy(Board, 'x', 'r');
            printBoard(Board);
        }
        if(GetAsyncKeyState(VK_ESCAPE))
        {
            break;
        }
    }
    return 0;
}
int random(int min, int max)
{
    return rand() % (max - min + 1) + min;
}
void removeFire(char Board[][21])
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 21; j++)
        {
            if (Board[i][j] == '.')
            {
                Board[i][j] = ' ';
                break;
            }
        }
    }
}
void moveEnemy(char Board[][21], char enemyType, char move)
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 21; j++)
        {
            if (Board[i][j] == enemyType)
            {
                if (move == 'r')     /// right
                {
                    if (Board[i][j] == enemyType && Board[i][j + 1] == ' ')     /// wall collision
                    {
                        Board[i][j] = ' ';
                        Board[i][j + 1] = enemyType;
                        break;
                    }
                }
                else if (move == 'l')       /// left
                {
                    if (Board[i][j - 1] == ' ' && Board[i][j - 1] != '#')
                    {
                        Board[i][j] = ' ';
                        Board[i][j-1] = enemyType;
                        break;
                    }  
                }
            }
        }
    }
}
void movePlayer(char Board[][21], char position)
{
   for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 21; j++)
        {
            if (Board[i][j] == 'p')
            {
                if (position == 'r')     /// right
                {
                    if (j + 1 < 21 && Board[i][j + 1] == ' ')     /// wall collision
                    {
                        Board[i][j] = ' ';
                        Board[i][j + 1] = 'p';
                        break;
                    }
                }
                else if (position == 'l')       /// left
                {
                    if (Board[i][j - 1] == ' ')
                    {
                        Board[i][j] = ' ';
                        Board[i][j-1] = 'p';
                        break;
                    }  
                }
            }

        }
    }
}
void moveFire(char Board[][21], int step)
{
    while(step != 0)
    {
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 21; j++)
            {
                if (Board[i][j] == '.')
                {
                    Board[i][j] = ' ';
                    Board[i-1][j] = '.';
                }
            }
        }
        step--;    
    }
}
void moveFire(char Board[][21])
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 21; j++)
        {
            if (Board[i][j] == '.')
            {
                Board[i][j] = ' ';
                Board[i-1][j] = '.';
            }
        }
    }
}
void fire(char Board[][21])
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 21; j++)
        {
            if (Board[i][j] == 'p')
            {
                Board[i-1][j] = '.';
            }
        }
    }
}
// this functions will only print the border of the board
void printBorder(char Board[][21])
{
    system("cls");
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 21; j++)
        {
            // apply if condition to print only the border
            // if the element is '#' or ' ' then print it
            if (Board[i][j] == '#' || Board[i][j] == ' ')
                cout << Board[i][j];
            else
                cout << ' ';
        }
        cout << endl;
    }   
}
void printBoard(char Board[][21])
{
    string buffer = "";
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 21; j++)
        {
            buffer += Board[i][j];    /// storing each element of the array in the buffer string variable
        }
        buffer += "\n";
    }
    system("cls");
    cout << buffer;               /// printing the buffer string variable which has the whole board
}
bool wallNotDetected(char arr[][21])
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 21; j++)
        {
            if (arr[i][j] == '.' && arr[i - 1][j] == '#')
            {
                arr[i][j] = ' ';  // remove fire
                return false; // Collision detected, stop moving
            }
        }
    }
    return true; // No collision detected, continue moving
}