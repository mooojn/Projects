#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
using namespace std;
int rollDice();
void Grid();
void printPlayersOnGrid();
void printPlayer1OnGrid(int player1Turn);
void printPlayer2OnGrid(int player2Turn);
void score();
/////////////////
const int gridSize = 10;            // size of the grid
int board[gridSize][gridSize];     // ludo game board
////
int player2 = 0;
int player1 = 0;
bool player1Wins = false;
bool player2Wins = false;
// ladder and snake positions
const int size = 3;
int ladderOnTheGrid[size] = {4, 15, 25};
int ladderTakesTo[size] = {14, 30, 50};
int snakeOnTheGrid[size] = {17, 54, 62};
int snakeTakesTo[size] = {7, 34, 18};
void checkPlayerLadderOrSnake(int &player);
// extra
string setcolor(unsigned short color);
int blue = 1, green = 2, cyan = 3, red = 4, brown = 6, lightwhite = 7, lightblue = 9, lightgreen = 10, lightcyan = 11, lightred = 12, yellow = 14, white = 15;
///
int main()
{
    int count = 1;  // player turns counter
    int player1Turn = 0, player2Turn = 0;
    Grid();       // printing the grid
    while (!player1Wins || !player2Wins)
    {
        if (count == 1)
        {
            cout << "Player 1 turn: " << endl;
            cout << "Press any key to roll..." << endl;
            getch();
            player1Turn = rollDice();
            cout << "You got: " << player1Turn << endl;
            printPlayer1OnGrid(player1Turn);
            if (player1 == 100)
            {
                player1Wins = true;
                break;
            }
            count++;    // next turn
        }
        else if (count == 2)
        {
            cout << "Player 2 turn: " << endl;
            cout << "Press any key to roll..." << endl;
            getch();
            player2Turn = rollDice();
            cout << "You got: " << player2Turn << endl;
            printPlayer2OnGrid(player2Turn);
            if (player2 == 100)
            {
                player2Wins = true;
                break;
            }
            count--;   // next turn
        }
        score();
    }
    // win screen
    system("cls");
    if (player1Wins)
    {
        setcolor(lightblue);
        cout << "Player 1 wins!" << endl;
        setcolor(white);
    }
    else if (player2Wins)
    {
        setcolor(lightred);
        cout << "Player 2 wins!" << endl;
        setcolor(white);
    }
    getch();
    return 0;
}
int rollDice() 
{
    srand(time(0));
    return (rand() % 6) + 1;
}
void printPlayer1OnGrid(int player1Turn)
{
    player1 += player1Turn;
    checkPlayerLadderOrSnake(player1);
    if (player1 > 100)
    {
        player1 -= player1Turn;
        printPlayersOnGrid();
    }
    else
    {
        printPlayersOnGrid();
    }
}
void printPlayer2OnGrid(int player2Turn)
{
    player2 += player2Turn;
    checkPlayerLadderOrSnake(player2);
    if (player2 > 100)
    {
        player2 -= player2Turn;
        printPlayersOnGrid();
    }
    else
    {
        printPlayersOnGrid();
    }
}
void printPlayersOnGrid()
{
    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < gridSize; j++)
        {
            if (board[i][j] == player1)
            {
                setcolor(blue);
                cout << "* ";
                setcolor(white);
            }
            else if (board[i][j] == player2)
            {
                setcolor(red);
                cout << "x ";
                setcolor(white);
            }
            else
            {
                cout << board[i][j] << " ";
            }
        }
        cout << endl;
    }
}
void checkPlayerLadderOrSnake(int &player)
{
    for (int i = 0; i < size; i++)
    {
        if (player == ladderOnTheGrid[i])
        {
            player = ladderTakesTo[i];
        }
        else if (player == snakeOnTheGrid[i])
        {
            player = snakeTakesTo[i];
        }
    }
}
void Grid() 
{
    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < gridSize; j++) 
        {
            board[i][j] = i * gridSize + j + 1;  // placing the numbers in 10x10 grid
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}
void score()
{
    setcolor(lightblue);
    cout << "Player 1: " << player1 << " " << endl;
    setcolor(lightred);
    cout << "Player 2: " << player2 << " " << endl;
    setcolor(white);
}
// for coloring
string setcolor(unsigned short color)
{
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon, color);
    return "";
}