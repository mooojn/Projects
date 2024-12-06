#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
using namespace std;
////////////////// functions
string startingMenu();
void showControls();
string difficultyMenu();
void resetVAlUES();
void playGAME();
///////////////////////////////
// enemy one
void printEnemy1();
void eraseEnemy1();
void moveEnemy1();
// enemy two
void printEnemy2();
void eraseEnemy2();
void moveEnemy2();
// enemy three
void printEnemy3();
void eraseEnemy3();
void moveEnemy3();
// player
void erasePlayer();
void printPlayer();
// player movement
void movePlayerLeft();
void movePlayerRight();
void movePlayerUp();
void movePlayerDown();
void changeFirePosition();
void playerFire();
void moveFire();
// maze
void printMaze();
// header
void header();
void invaldError();
// score
void score();
void storeScore();
void loadScore();
void viewLastHighScore();
// screens
void setDifficulty();
void printScores();
void winScreen();
void loseScreen();
// other
char getCharAtxy(short int x, short int y);
void gotoxy(int x, int y);//
string setcolor(unsigned short color);
void hideCursor();
// colors
int blue = 1, green = 2, cyan = 3, red = 4, brown = 6, lightwhite = 7, lightblue = 9, lightgreen = 10, lightcyan = 11, lightred = 12, yellow = 14, white = 15;
/////////////////////// enemy varaibles
int e1X = 2, e1Y = 1;
bool e1WallHit = false;
int enemy1Health = 2;    // default
///
int e2X = 30, e2Y = 20;
bool e2WallHit = false;
int enemy2Health = 4;   // values
///
int e3X = 69, e3Y = 1;
bool e3WallHit = false;
int enemy3Health = 2;  // set to easy difficulty
// player variables
int pX = 45, pY = 21;
bool fired = false;
int bulletX = 0;
int bulletY = 0;
int playerHealth = 6;
bool horizontal = true;  // horizontal fire
bool vertical = false;  // vertical fire
// enemy 1 fire
void enemy1Fire();
void moveEnemy1Bullet();
int enemy1BulletX = 0;
int enemy1BulletY = 0;
bool enemy1Fired = false;
bool dead1 = false;
// enemy 2 is an obstacle
bool dead2 = false;
// enemy 3 fire
void enemy3Fire();
void moveEnemy3Bullet();
int enemy3BulletX = 0;
int enemy3BulletY = 0;
bool enemy3Fired = false;
bool dead3 = false;
// scores
int gameScore = 0; 
int lastHighScore = 0;
//////////////////////////
// 2d maze
char maze[25][78] = {              
    "#############################################################################",
    "##                                                                         ##",
    "##                                              ##                         ##",
    "##                                              ##                         ##",
    "##                                                          ##             ##",
    "##                                                          ##             ##",
    "##                          ###                             ##             ##",
    "##       #######            ###                              ######        ##",
    "##                                                 ##                      ##",
    "##                                                 ##                      ##",
    "##                                                                         ##",
    "##                                                                         ##",
    "##                                                                         ##",
    "##                                                                         ##",
    "##                         ##                                              ##",
    "##                         ##                                              ##",
    "##                                                                         ##",
    "##        ######                                             ######        ##",
    "##          ** ##                                           ##             ##",
    "##          ** ##                         ==        ==      ##             ##",
    "##             ##          ##             ||        ||      ##             ##",
    "##                         ##             []        []                     ##",
    "##                                        ||        ||                     ##",
    "##                                        //        \\\\                     ##",
    "#############################################################################"
};

// main
int main()
{
GameRestart:         // incase of game restart
    loadScore();    // load last high score
    resetVAlUES();
invalidInput:         // in case of invalid input
    string choice = startingMenu();
    if (choice == "1")
    {        
        playGAME();
        goto GameRestart;
    }
    // other choices
    else if (choice == "2")
        showControls();
    else if (choice == "3")
        setDifficulty();
    else if (choice == "4")
        viewLastHighScore();
    else if (choice == "5")
        return 0;     // end program
    else 
        invaldError();
goto invalidInput;   // incase of invalid input or going back to menu
}

void invaldError()
{
    setcolor(lightred);
    cout << "Invalid Input" << endl;
    setcolor(white);
    Sleep(700);
}
void playGAME()
{
    system("cls");
    printMaze();
    gotoxy(0,23);
    header();
    score();    
    // enemies
    printEnemy1();
    printEnemy2();
    printEnemy3();
    printPlayer();
    // hideCursor();
    while(true)
    {
        if (GetAsyncKeyState(VK_LEFT))
        {
            movePlayerLeft();
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
            movePlayerRight();
        }
        if (GetAsyncKeyState(VK_UP))
        {
            movePlayerUp();
        }
        if (GetAsyncKeyState(VK_DOWN))
        {
            movePlayerDown();
        }
        // change fire position
        if (GetAsyncKeyState('F'))
        {
            if (!fired)
            {
                changeFirePosition();
                printPlayer();
            } 
        }
        // fire
        if (GetAsyncKeyState(VK_SPACE))
        {
            if (!fired)
            {
                playerFire();
                fired = true;
            }
        }
        // fire
        if (fired)
        {
            moveFire();
        }
        if (enemy1Health != 0)
        {
            moveEnemy1();
        }
        // enemy one dead
        if (dead1)
        {
            eraseEnemy1();
            gotoxy(enemy1BulletX, enemy1BulletY);
            cout << " ";
            dead1 = false;
        }
        if (enemy2Health != 0)
        {
            moveEnemy2();
        }
        // enemy two dead
        if (dead2)
        {
            eraseEnemy2();
            dead2 = false;
        }
        if (enemy3Health != 0)
        {
            moveEnemy3();
        }
        // enemy three dead
        if (dead3)
        {
            eraseEnemy3();
            gotoxy(enemy3BulletX, enemy3BulletY);
            cout << " ";
            dead3 = false;
        }
        /// enemy fire's
        if (!enemy1Fired)
        {
            enemy1Fire();
        }
        if (enemy1Fired && enemy1Health != 0)
        {
            moveEnemy1Bullet();
        }
        if (!enemy3Fired)
        {
            enemy3Fire();
        }
        if (enemy3Fired && enemy3Health != 0)
        {
            moveEnemy3Bullet();
        }
        ////// game lost..... ///////
        if (playerHealth == 0)
        {
            loseScreen();
            storeScore();
            break;
        }
        // game win..... ///////
        if (enemy1Health == 0 && enemy2Health == 0 && enemy3Health == 0)
        {
            winScreen();
            storeScore();
            break;
        }
        // score
        printScores();
        Sleep(75);
    }
}
void loseScreen()
{
    gotoxy(80,15);
    cout << "Game Over";
    gotoxy(80,16);
    cout << "Your Score: " << gameScore;
    Sleep(2000);
    getch();
}
void resetVAlUES()
{
    playerHealth = 6;
    enemy1Health = 2;
    enemy2Health = 4;
    enemy3Health = 2;
    gameScore = 0; 
    fired = false;
    bulletX = 0;
    bulletY = 0;
    horizontal = true;
    vertical = false;
    dead1 = false;
    dead2 = false;
    dead3 = false;
    e1X = 2, e1Y = 1;
    e1WallHit = false;
    e2X = 30, e2Y = 20;
    e2WallHit = false;
    e3X = 69, e3Y = 1;
    e3WallHit = false;
    pX = 45, pY = 21;
    enemy1BulletX = 0;
    enemy1BulletY = 0;
    enemy1Fired = false;
    enemy3BulletX = 0;
    enemy3BulletY = 0;
    enemy3Fired = false;
}
void setDifficulty()
{
againInput:       // incase of invalid choice
    string choiceOfDifficulty = difficultyMenu();
    if (choiceOfDifficulty == "1")
    {
        playerHealth = 6;
        enemy1Health = 2;
        enemy2Health = 4;
        enemy3Health = 2;
    }
    else if (choiceOfDifficulty == "2")
    {  
        playerHealth = 4;
        enemy1Health = 4;
        enemy2Health = 6;
        enemy3Health = 4;
    }
    else if (choiceOfDifficulty == "3")
    {
        playerHealth = 3;
        enemy1Health = 6;
        enemy2Health = 8;
        enemy3Health = 6;
    }
    else
    {
        setcolor(lightred);
        cout << "Invalid Input" << endl;
        setcolor(white);
        Sleep(700);
        goto againInput;
    }
    setcolor(lightgreen);
    cout << "Difficulty has been Changed....";
    Sleep(700);
    setcolor(white);
}
void showControls()
{
    system("cls");
    header();
    cout << "Controls" << endl;
    setcolor(lightgreen);
    cout << "Move Tank Left: Left Arrow Key" << endl;
    setcolor(lightgreen);
    cout << "Move Tank Right: Right Arrow Key" << endl;
    setcolor(lightgreen);
    cout << "Move Tank Up: Up Arrow Key" << endl;
    setcolor(lightgreen);
    cout << "Move Tank Down: Down Arrow Key" << endl;
    setcolor(yellow);
    cout << "Change Firing Position: F" << endl;
    setcolor(red);
    cout << "Fire: Space Bar" << endl;
    setcolor(cyan);
    cout << "Press any key to go back...";
    setcolor(white);
    getch();
}
string difficultyMenu()
{
    system("cls");
    header();
    cout << "Difficulty Selection Default is Easy" << endl;
    setcolor(lightgreen);
    cout << "1. Easy" << endl;
    setcolor(lightblue);
    cout << "2. Medium" << endl;
    setcolor(lightred);
    cout << "3. Hard" << endl;
    setcolor(white);
    string choice;
    cout << "Enter the number of difficulty: ";
    cin >> choice;
    return choice;
}
string startingMenu()
{
    system("cls");
    header();
    string choice;
    setcolor(lightgreen);
    cout << "1. Start a New Game" << endl;
    cout << "2. Controls" << endl;  
    cout << "3. Set Difficulty" << endl; 
    cout << "4. View Last High Score" << endl;
    setcolor(red);
    cout << "5. Exit" << endl;
    setcolor(white);
    cout << "Enter the number of your choice: ";
    cin >> choice;
    return choice;
}
void viewLastHighScore()
{
    system("cls");
    header();
    cout << "Last High Score: " << lastHighScore << endl;
    cout << "Press any key to go back...";
    getch();
}
void enemy3Fire()
{
    enemy3BulletX = e3X - 2;
    enemy3BulletY = e3Y + 1;
    gotoxy(enemy3BulletX, enemy3BulletY);
    setcolor(lightred);
    cout << "3";
    setcolor(white);
    enemy3Fired = true;
}
void moveEnemy3Bullet()
{
    gotoxy(enemy3BulletX, enemy3BulletY);
    cout << " ";
    gotoxy(enemy3BulletX - 1, enemy3BulletY);
    setcolor(lightred);
    cout << "3";
    setcolor(white);
    if (getCharAtxy(enemy3BulletX - 2, enemy3BulletY) == ' ')
        enemy3BulletX = enemy3BulletX - 1;
    else if (getCharAtxy(enemy3BulletX - 2, enemy3BulletY) == '@' || getCharAtxy(enemy3BulletX - 2, enemy3BulletY) == '|')
    {
        gotoxy(enemy3BulletX - 1, enemy3BulletY);
        cout << " ";
        enemy3Fired = false;
        playerHealth--;
    }
    else
    {
        gotoxy(enemy3BulletX - 1, enemy3BulletY);
        cout << " ";
        enemy3Fired = false;
    }
}
void moveEnemy1Bullet()
{
    gotoxy(enemy1BulletX, enemy1BulletY);
    cout << " ";
    gotoxy(enemy1BulletX, enemy1BulletY + 1);
    setcolor(cyan);
    cout << "{";
    setcolor(white);
    if (getCharAtxy(enemy1BulletX, enemy1BulletY + 2) == ' ')
        enemy1BulletY = enemy1BulletY + 1;
    else if (getCharAtxy(enemy1BulletX, enemy1BulletY + 2) == '@' || getCharAtxy(enemy1BulletX, enemy1BulletY + 2) == '|')
    {
        gotoxy(enemy1BulletX, enemy1BulletY + 1);
        cout << " ";
        enemy1Fired = false;
        playerHealth--;
    }
    else
    {
        gotoxy(enemy1BulletX, enemy1BulletY + 1);
        cout << " ";
        enemy1Fired = false;
    }
}
void enemy1Fire()
{
    enemy1BulletX = e1X + 2;
    enemy1BulletY = e1Y + 3;
    gotoxy(enemy1BulletX, enemy1BulletY);
    setcolor(cyan);
    cout << "{"; 
    setcolor(white);
    enemy1Fired = true;
}
void winScreen()
{
    gotoxy(80,15);
    cout << "You Win";
    gotoxy(80,16);
    cout << "Your Score: " << gameScore;
    Sleep(2000);
    getch();
}
void printScores()
{
    int x1 = 100;  // location
    int x2 = 120;
    //////////////////////////
    gotoxy(x1+5,10);
    cout << "Points";
    gotoxy(x2,10);
    cout << gameScore;

    setcolor(lightgreen);
    gotoxy(x1,12);
    cout << "Player Health";
    gotoxy(x2,12);
    cout << playerHealth;
    
    setcolor(lightblue);
    gotoxy(x1,14);
    cout << "Enemy One Health";
    gotoxy(x2,14);
    cout << enemy1Health;

    setcolor(brown);
    gotoxy(x1,15);
    cout << "Enemy Two Health";
    gotoxy(x2,15);
    cout << enemy2Health;

    setcolor(red);
    gotoxy(x1,16);
    cout << "Enemy Three Health";
    gotoxy(x2,16);
    cout << enemy3Health;
    
    setcolor(white);
}
void moveFire()
{
    setcolor(green);
    if (horizontal)
    {
        gotoxy(bulletX,bulletY);
        cout << " ";
        char nextObject = getCharAtxy(bulletX, bulletY - 1);
        if (nextObject == ' ')
        {
            bulletY = bulletY - 1;
            gotoxy(bulletX,bulletY);
            cout << "^";
        }
        else if (nextObject == 'O' || nextObject == 'E')
        {
            gameScore += 5;
            gotoxy(bulletX,bulletY);
            cout << " ";
            fired = false;
            enemy1Health--;
            if (enemy1Health == 0)
            {
                dead1 = true;
            }
        }
        else if (nextObject == '1' || nextObject == 'e'|| nextObject == '_')
        {
            gameScore += 5;
            gotoxy(bulletX,bulletY);
            cout << " ";
            fired = false;
            enemy2Health--;
            if (enemy2Health == 0)
            {
                dead2 = true;
            }
        }
        else if (nextObject == '-' || nextObject == 'j'|| nextObject == '0')
        {
            gameScore += 5;
            gotoxy(bulletX,bulletY);
            cout << " ";
            fired = false;
            enemy3Health--;
            if (enemy3Health == 0)
            {
                dead3 = true;
            }
        }
        else
        {
            gotoxy(bulletX,bulletY);
            cout << " ";
            fired = false;
        }
    }
    else if (vertical)
    {
        gotoxy(bulletX,bulletY);
        cout << " ";
        char nextObject = getCharAtxy(bulletX + 2, bulletY);
        if (nextObject == ' ')
        {
            bulletX = bulletX + 2;
            gotoxy(bulletX,bulletY);
            cout << ">";
        }
        else if (nextObject == 'O' || nextObject == 'E')
        {
            gameScore += 5;
            gotoxy(bulletX, bulletY);
            cout << " ";
            fired = false;
            enemy1Health--;
            if (enemy1Health == 0)
            {
                dead1 = true;
            }
        }
        else if (nextObject == '1' || nextObject == 'e'|| nextObject == '_')
        {
            gameScore += 5;
            gotoxy(bulletX,bulletY);
            cout << " ";
            fired = false;
            enemy2Health--;
            if (enemy2Health == 0)
            {
                dead2 = true;
            }
        }
        else if (nextObject == '-' || nextObject == 'j'|| nextObject == '0')
        {
            gameScore += 5;
            gotoxy(bulletX,bulletY);
            cout << " ";
            fired = false;
            enemy3Health--;
            if (enemy3Health == 0)
            {
                dead3 = true;
            }
        }
        else
        {
            gotoxy(bulletX,bulletY);
            cout << " ";
            fired = false;
        }
    }
    setcolor(white);
}

void playerFire()
{
    if (getCharAtxy(pX + 3, pY - 1) != '#' && getCharAtxy(pX + 2, pY - 1) != '#')  // check if player is not near wall
    {
        setcolor(green);
        if (horizontal)
        {
            bulletX = pX + 2;
            bulletY = pY - 1;
            gotoxy(bulletX, bulletY);
            cout << "^";

        }
        else if (vertical)
        {
            bulletX = pX + 2;
            bulletY = pY - 1;
            gotoxy(bulletX, bulletY);
            cout << ">";
        }
        setcolor(white);
    }
}
void changeFirePosition()
{
    if (horizontal)
    {
        vertical = true;
        horizontal = false;
    }
    else if (vertical)
    {
        vertical = false;
        horizontal = true;
    }
}
// enemy one
void printEnemy1()
{
    setcolor(lightblue);
    gotoxy(e1X,e1Y);
    cout << "O    O" << endl;
    gotoxy(e1X,e1Y+1);
    cout << "O_EE_O" << endl;
    gotoxy(e1X,e1Y+2);
    cout << "O EE O" << endl;
    setcolor(white);
}
void eraseEnemy1()
{
    gotoxy(e1X,e1Y);
    cout << "      " << endl;
    gotoxy(e1X,e1Y+1);
    cout << "      " << endl;
    gotoxy(e1X,e1Y+2);
    cout << "      " << endl;
}
void moveEnemy1()
{
    eraseEnemy1();    
    if (!e1WallHit && getCharAtxy(e1X + 11, e1Y) != '@' && getCharAtxy(e1X + 11, e1Y + 1) != '@' && getCharAtxy(e1X + 11, e1Y + 2) != '@'){     
        e1X = e1X + 1;
        if(e1X == 42)
            e1WallHit = true;
    }
    else if(e1WallHit && getCharAtxy(e1X - 1, e1Y) != '@' && getCharAtxy(e1X - 1, e1Y + 1) != '@' && getCharAtxy(e1X - 1, e1Y + 2) != '@'){ 
        e1X = e1X - 1;
        if(e1X < 3)
            e1WallHit = false;
    }
    printEnemy1();
}
// enemy two 
void printEnemy2()
{
    setcolor(brown);
    gotoxy(e2X,e2Y);
    cout << "1 ee 1" << endl;
    gotoxy(e2X,e2Y+1);
    cout << "1_ee_1" << endl;
    gotoxy(e2X,e2Y+2);
    cout << "1    1" << endl;
    setcolor(white);
}
void eraseEnemy2()
{
    gotoxy(e2X,e2Y);
    cout << "      " << endl;
    gotoxy(e2X,e2Y+1);
    cout << "      " << endl;
    gotoxy(e2X,e2Y+2);

    cout << "      " << endl;
}
void moveEnemy2()
{
    eraseEnemy2();
    // collision with player
    if (getCharAtxy(e2X + 6, e2Y - 1) == '@' || getCharAtxy(e2X + 6, e2Y) == '@' || getCharAtxy(e2X + 6, e2Y + 1) == '@' || getCharAtxy(e2X + 6, e2Y + 2) == '@' || getCharAtxy(e2X - 1, e2Y - 1) == '@' || getCharAtxy(e2X - 1, e2Y) == '@' || getCharAtxy(e2X - 1, e2Y + 1) == '@' || getCharAtxy(e2X - 1, e2Y + 2) == '@' || getCharAtxy(e2X + 1, e2Y - 1) == '@' || getCharAtxy(e2X + 2, e2Y - 1) == '@'|| getCharAtxy(e2X + 3, e2Y - 1) == '@'|| getCharAtxy(e2X + 4, e2Y - 1) == '@' || getCharAtxy(e2X + 5, e2Y - 1) == '@' || getCharAtxy(e2X + 6, e2Y - 1) == '@')
    {
        playerHealth--;
        erasePlayer();
        pX = 45;
        pY = 21;
        printPlayer();
    }
    if (!e2WallHit){        
        e2X = e2X + 1;
        e2Y = e2Y - 1;
        if(e2X == 43)
            e2WallHit = true;
    }    
    else if(e2WallHit){ 
        e2X = e2X - 1;
        e2Y = e2Y + 1;
        if(e2X == 30)
            e2WallHit = false;
    }
    printEnemy2();
}
// enemy three
void printEnemy3()
{
    setcolor(red);
    gotoxy(e3X,e3Y);
    cout << "0-0-0" << endl;
    gotoxy(e3X,e3Y+1);
    cout << "jjj| " << endl;
    gotoxy(e3X,e3Y+2);
    cout << "0-0-0" << endl;
    setcolor(white);
}
void eraseEnemy3()
{
    gotoxy(e3X,e3Y);
    cout << "     " << endl;
    gotoxy(e3X,e3Y+1);
    cout << "     " << endl;
    gotoxy(e3X,e3Y+2);
    cout << "     " << endl;
}
void moveEnemy3()
{       
    eraseEnemy3();
    // condtions for collision with player
    if (!e3WallHit && getCharAtxy(e3X, e3Y + 3) != '@' && getCharAtxy(e3X + 1, e3Y + 3) != '@'&& getCharAtxy(e3X + 2, e3Y + 3) != '@' && getCharAtxy(e3X + 3, e3Y + 3) != '@'&& getCharAtxy(e3X + 4, e3Y + 3) != '@'){        
        e3Y = e3Y + 1;
        if(e3Y == 17)
            e3WallHit = true;
    }
    else if(e3WallHit && getCharAtxy(e3X, e3Y - 1) != '@' && getCharAtxy(e3X + 1, e3Y - 1) != '@'&& getCharAtxy(e3X + 2, e3Y - 1) != '@'&& getCharAtxy(e3X + 3, e3Y - 1) != '@'&& getCharAtxy(e3X + 4, e3Y - 1) != '@'){
        e3Y = e3Y - 1;
        if(e3Y < 2)
            e3WallHit = false;
    }
    printEnemy3();
}
// player  
void printPlayer()
{
    setcolor(lightgreen);
    if (horizontal)
    {
        gotoxy(pX,pY);
        cout << "@ || @" << endl;
        gotoxy(pX,pY+1);
        cout << "@_||_@" << endl;
        gotoxy(pX,pY+2);
        cout << "@    @" << endl;    
    }
    else if (vertical)
    {
        gotoxy(pX,pY);
        cout << "@ //  " << endl;
        gotoxy(pX,pY+1);
        cout << "@_||_@" << endl;
        gotoxy(pX,pY+2);
        cout << "@    @" << endl;    
    }
    setcolor(white);
}
void erasePlayer()
{
    gotoxy(pX,pY);
    cout << "      " << endl;
    gotoxy(pX,pY+1);
    cout << "      " << endl;
    gotoxy(pX,pY+2);
    cout << "      " << endl;    
}
// player movements
void movePlayerLeft()
{
    if (getCharAtxy(pX - 1, pY)== '*' || getCharAtxy(pX - 1, pY + 1) == '*' || getCharAtxy(pX - 1, pY + 2) == '*'){
        gameScore += 1;
        erasePlayer();
        pX = pX - 1;
        printPlayer();
    }        
    else if (getCharAtxy(pX - 1, pY) == ' ' && getCharAtxy(pX - 1, pY + 1) == ' ' && getCharAtxy(pX - 1, pY + 2) == ' '){
        erasePlayer();
        pX = pX - 1;
        printPlayer();
    }    
}
void movePlayerRight()
{
    if (getCharAtxy(pX + 6, pY)== '*' || getCharAtxy(pX + 6, pY + 1) == '*' || getCharAtxy(pX + 6, pY + 2) == '*'){
        gameScore += 1;
        erasePlayer();
        pX = pX + 1;
        printPlayer();
    }    
    else if (getCharAtxy(pX + 6, pY) == ' ' && getCharAtxy(pX + 6, pY + 1) == ' ' && getCharAtxy(pX + 6, pY + 2) == ' '){       
        erasePlayer();
        pX = pX + 1;
        printPlayer();
    }
}
void movePlayerUp()
{
    if (getCharAtxy(pX , pY - 1) == '*' || getCharAtxy(pX + 1 , pY - 1) == '*' || getCharAtxy(pX + 2, pY - 1) == '*' || getCharAtxy(pX + 3, pY - 1) == '*'|| getCharAtxy(pX + 4, pY - 1) == '*'|| getCharAtxy(pX + 5, pY - 1) == '*'){
        gameScore +=1;
        erasePlayer();
        pY = pY - 1;
        printPlayer();
    } 
    else if(getCharAtxy(pX , pY - 1) == ' ' && getCharAtxy(pX + 1 , pY - 1) == ' ' && getCharAtxy(pX + 2, pY - 1) == ' '&& getCharAtxy(pX + 3, pY - 1) == ' '&& getCharAtxy(pX + 4, pY - 1) == ' '&& getCharAtxy(pX + 5, pY - 1) == ' '){
        erasePlayer();
        pY = pY - 1;
        printPlayer();
    }    
}
void movePlayerDown()
{
   if (getCharAtxy(pX , pY + 3) == '*' || getCharAtxy(pX + 1 , pY + 3) == '*' || getCharAtxy(pX + 2, pY + 3) == '*' || getCharAtxy(pX + 3, pY + 3) == '*'|| getCharAtxy(pX + 4, pY + 3) == '*'|| getCharAtxy(pX + 5, pY + 3) == '*'){
        gameScore +=1;
        erasePlayer();
        pY = pY + 1;
        printPlayer();
    }
    else if(getCharAtxy(pX , pY + 3) == ' ' && getCharAtxy(pX + 1, pY + 3) == ' ' && getCharAtxy(pX + 2, pY + 3) == ' ' && getCharAtxy(pX + 3, pY + 3) == ' ' && getCharAtxy(pX + 4, pY + 3) == ' ' && getCharAtxy(pX + 5, pY + 3) == ' '){    
        erasePlayer();
        pY = pY + 1;
        printPlayer();
    }
}


void printMaze()
{
    string mazeBUFFER = "";
    for (int i = 0; i < 25; i++){
        for (int j = 0; j < 78; j++){
            mazeBUFFER += maze[i][j];
        }
        mazeBUFFER += '\n';
    }
    cout << mazeBUFFER;
}

void storeScore()
{
    fstream file;
    file.open("highScore.csv", ios::out);
    if (gameScore > lastHighScore)
        file << gameScore;
    else
        file << lastHighScore;
    file.close();
}
void loadScore()
{
    fstream file;
    file.open("highScore.csv", ios::in);
    if (file.fail())
    {
        lastHighScore = 0;
        return;
    }
    file >> lastHighScore;
    file.close();
}
void header()
{    
    cout << endl;
    cout << endl;
    cout << endl;
    setcolor(cyan);
    cout<<R"(     _________  ________  ________   ___  __                                  )"<<endl;    
    cout<<R"(    |\___   ___\\   __  \|\   ___  \|\  \|\  \                                )"<<endl;    
    cout<<R"(    \|___ \  \_\ \  \|\  \ \  \\ \  \ \  \/  /|_                              )"<<endl;    
    cout<<R"(         \ \  \ \ \   __  \ \  \\ \  \ \   ___  \                             )"<<endl;    
    cout<<R"(          \ \  \ \ \  \ \  \ \  \\ \  \ \  \\ \  \                            )"<<endl;    
    cout<<R"(           \ \__\ \ \__\ \__\ \__\\ \__\ \__\\ \__\                           )"<<endl;    
    cout<<R"(            \|__|  \|__|\|__|\|__|_\|__|\|__| \|__|                           )"<<endl;
    setcolor(lightred);
    cout<<R"(                             ___       ___  _________ ________  ________      )"<<endl;
    cout<<R"(                            |\  \     |\  \|\   __  \|\   __  \|\   ____\     )"<<endl;
    cout<<R"(                            \ \  \    \ \  \ \  \|\  \ \  \|\  \ \  \___|_    )"<<endl;
    cout<<R"(                             \ \  \  __\ \  \ \   __  \ \   _  _\ \_____  \   )"<<endl;
    cout<<R"(                              \ \  \|\__\_\  \ \  \ \  \ \  \\  \\|____|\  \  )"<<endl;
    cout<<R"(                               \ \____________\ \__\ \__\ \__\\ _\ ____\_\  \ )"<<endl;
    cout<<R"(                                \|____________|\|__|\|__|\|__|\|__|\_________\)"<<endl;
    cout<<R"(                                                                  \|_________|)"<<endl;                                                                     
    setcolor(white);
}
void score() 
{
    int x = 80, y = 1; 
    setcolor(yellow);
    gotoxy(x,y);
    cout << R"(  ________  ________  ________  ________  _______      )" << endl;
    
    gotoxy(x,y+1);
    cout << R"( |\   ____\|\   ____\|\   __  \|\   __  \|\  ___ \     )" << endl;
    
    gotoxy(x,y+2);
    cout << R"( \ \  \___|\ \  \___|\ \  \|\  \ \  \|\  \ \   __/|    )" << endl;
    
    gotoxy(x,y+3);
    cout << R"(  \ \_____  \ \  \    \ \  \\\  \ \   _  _\ \  \_|/__  )" << endl;
    
    gotoxy(x,y+4);
    cout << R"(   \|____|\  \ \  \____\ \  \\\  \ \  \\  \\ \  \_|\ \ )" << endl;
    
    gotoxy(x,y+5);
    cout << R"(     ____\_\  \ \_______\ \_______\ \__\\ _\\ \_______\)" << endl;
    
    gotoxy(x,y+6);
    cout << R"(    |\_________\|_______|\|_______|\|__|\|__|\|_______|)" << endl;
    
    gotoxy(x,y+7);
    cout << R"(    \|_________|                                       )" << endl;
    setcolor(white);
}
// functions for game
char getCharAtxy(short int x, short int y)
{
    CHAR_INFO ci;
    COORD xy = {0, 0};
    SMALL_RECT rect = {x, y, x, y};
    COORD coordBufSize;
    coordBufSize.X = 1;
    coordBufSize.Y = 1;
    return ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, coordBufSize, xy, &rect) ? ci.Char.AsciiChar: ' ';
}
void hideCursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}
void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
string setcolor(unsigned short color)
{
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon, color);
    return "";
}
/////////////////////////////////////////// old maze ////////////////////////////////////////////////
    // cout << "#############################################################################" << endl;
    // cout << "##                                                                         ##" << endl;
    // cout << "##                                              ##                         ##" << endl;
    // cout << "##                                              ##                         ##" << endl;
    // cout << "##                                                          ##             ##" << endl;
    // cout << "##                                                          ##             ##" << endl;
    // cout << "##                          ###                             ##             ##" << endl;
    // cout << "##       #######            ###                              ######        ##" << endl;
    // cout << "##                                                 ##                      ##" << endl;
    // cout << "##                                                 ##                      ##" << endl;
    // cout << "##                                                                         ##" << endl;
    // cout << "##                                                                         ##" << endl;
    // cout << "##                                                                         ##" << endl;
    // cout << "##                                                                         ##" << endl;
    // cout << "##                         ##                                              ##" << endl;
    // cout << "##                         ##                                              ##" << endl;
    // cout << "##                                                                         ##" << endl;
    // cout << "##        ######                                             ######        ##" << endl;
    // cout << "##             ##                                           ##             ##" << endl;
    // cout << "##             ##                         ==        ==      ##             ##" << endl;
    // cout << "##             ##          ##             ||        ||      ##             ##" << endl;
    // cout << "##                         ##             []        []                     ##" << endl;
    // cout << "##                                        ||        ||                     ##" << endl;
    // cout<<" ##                                         //        \\                     ##" << endl;
    // cout << "#############################################################################" << endl;
    // setcolor(white);