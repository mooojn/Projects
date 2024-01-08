#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;
//////////////////////////
char getCharAtxy(short int x, short int y);
void gotoxy(int x, int y);//
string setcolor(unsigned short color);
void hideCursor();
int blue = 1, green = 2, cyan = 3, red = 4, brown = 6, lightwhite = 7, lightblue = 9, lightgreen = 10, lightcyan = 11, lightred = 12, yellow = 14, white = 15;
int bonus1 = 0; 
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
// maze
void printMaze();
// header
void header();
//
void score();
// player movement
void movePlayerLeft();
void movePlayerRight();
void movePlayerUp();
void movePlayerDown();
/////////////////////// enemy varaibles
int e1X = 2, e1Y = 1;
bool e1WallHit = false;
///
int e2X = 30, e2Y = 20;
bool e2WallHit = false;
///
int e3X = 69, e3Y = 1;
bool e3WallHit = false;
// player variables
int pX = 45, pY = 21;
/////////////////////////////////////
void changeFirePosition();
void setPlayerFiringCoords();
void moveBullet();
void printScores();
void winScreen();
///////////////
int bulletX[100];
int bulletY[100];
int bulletCount = 0;
void erasePlayerBullet(int x_coord, int y_coord);
void firePlayerBullet(int x_coord, int y_coord);
void moveBulletArrays();
void eraseBulletFromArray(int indexToRemove);
////////////////////
bool fired = false;
int bulletX_axis = 0;
int bulletY_axis = 0;
//////////////////////////
int playerHealth = 3;
int enemy1Health = 3;
int enemy2Health = 6;   // obstacle health
int enemy3Health = 3;
/////
bool horizontal = true;
bool vertical = false;
bool dead1 = false;
bool dead2 = false;
bool dead3 = false;
// enemy fire

void enemy1Fire();
void moveEnemy1Bullet();
int enemy1BulletX = 0;
int enemy1BulletY = 0;
bool enemy1Fired = false;

// enemy 2 is an obstacle

void enemy3Fire();
void moveEnemy3Bullet();
int enemy3BulletX = 0;
int enemy3BulletY = 0;
bool enemy3Fired = false;
//////////////////////////

// main
int main()
{
    system("cls");
    printMaze();

    gotoxy(0,23);
    header();
    
    score();

    printEnemy1();
    // printEnemy2();
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
            // if (!fired)
            // {
                setPlayerFiringCoords();
                // fired = true;
            // }
        }
        moveBulletArrays();
        // score
        printScores();

        // fire
        if (fired)
        {
            moveBullet();
        }
        if (enemy1Health != 0)
        {
            moveEnemy1();
        }
        // enemy one dead
        if (dead1)
        {
            eraseEnemy1();
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
            gotoxy(80,15);
            cout << "Game Over";
            gotoxy(80,16);
            cout << "Your Score: " << bonus1;
            break;
        }
        // game win..... ///////
        if (enemy1Health == 0 && enemy2Health == 0 && enemy3Health == 0)
        {
            winScreen();
            break;
        }
        Sleep(75);
    }
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
    cout << "Your Score: " << bonus1;
}
void printScores()
{
    int x1 = 100;  // location
    int x2 = 120;
    //////////////////////////
    gotoxy(x1+5,10);
    cout << "Points";
    gotoxy(x2,10);
    cout << bonus1;

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
void moveBullet()
{
    setcolor(green);
    if (horizontal)
    {
        gotoxy(bulletX_axis,bulletY_axis);
        cout << " ";
        if (getCharAtxy(bulletX_axis, bulletY_axis-1) == ' ')
        {
            bulletY_axis = bulletY_axis - 1;
            gotoxy(bulletX_axis,bulletY_axis);
            cout << "^";
        }
        else if (getCharAtxy(bulletX_axis, bulletY_axis - 1) == 'O' || getCharAtxy(bulletX_axis, bulletY_axis - 1) == 'E')
        {
            bonus1 += 5;
            gotoxy(bulletX_axis,bulletY_axis);
            cout << " ";
            fired = false;
            enemy1Health--;
            if (enemy1Health == 0)
            {
                dead1 = true;
            }
        }
        else if (getCharAtxy(bulletX_axis, bulletY_axis - 1) == '1' || getCharAtxy(bulletX_axis, bulletY_axis - 1) == 'e'|| getCharAtxy(bulletX_axis, bulletY_axis - 1) == '_')
        {
            bonus1 += 5;
            gotoxy(bulletX_axis,bulletY_axis);
            cout << " ";
            fired = false;
            enemy2Health--;
            if (enemy2Health == 0)
            {
                dead2 = true;
            }
        }
        else if (getCharAtxy(bulletX_axis, bulletY_axis - 1) == '-' || getCharAtxy(bulletX_axis, bulletY_axis - 1) == 'j'|| getCharAtxy(bulletX_axis, bulletY_axis - 1) == '0')
        {
            bonus1 += 5;
            gotoxy(bulletX_axis,bulletY_axis);
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
            gotoxy(bulletX_axis,bulletY_axis);
            cout << " ";
            fired = false;
        }
    }
    else if (vertical)
    {
        gotoxy(bulletX_axis,bulletY_axis);
        cout << " ";
        if (getCharAtxy(bulletX_axis + 2, bulletY_axis) == ' ')
        {
            bulletX_axis = bulletX_axis + 2;
            gotoxy(bulletX_axis,bulletY_axis);
            cout << ">";
        }
        else if (getCharAtxy(bulletX_axis + 2, bulletY_axis) == 'O' || getCharAtxy(bulletX_axis + 2, bulletY_axis) == 'E')
        {
            bonus1 += 5;
            gotoxy(bulletX_axis, bulletY_axis);
            cout << " ";
            fired = false;
            enemy1Health--;
            if (enemy1Health == 0)
            {
                dead1 = true;
            }
        }
        else if (getCharAtxy(bulletX_axis + 2, bulletY_axis) == '1' || getCharAtxy(bulletX_axis + 2, bulletY_axis) == 'e'|| getCharAtxy(bulletX_axis + 2, bulletY_axis) == '_')
        {
            bonus1 += 5;
            gotoxy(bulletX_axis,bulletY_axis);
            cout << " ";
            fired = false;
            enemy2Health--;
            if (enemy2Health == 0)
            {
                dead2 = true;
            }
        }
        else if (getCharAtxy(bulletX_axis + 2, bulletY_axis) == '-' || getCharAtxy(bulletX_axis + 2, bulletY_axis) == 'j'|| getCharAtxy(bulletX_axis, bulletY_axis) == '0')
        {
            bonus1 += 5;
            gotoxy(bulletX_axis,bulletY_axis);
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
            gotoxy(bulletX_axis,bulletY_axis);
            cout << " ";
            fired = false;
        }
    }
    setcolor(white);
}

void setPlayerFiringCoords()
{
    if (getCharAtxy(pX + 3, pY - 1) != '#' && getCharAtxy(pX + 2, pY - 1) != '#')  // check if player is not near wall
    {
        setcolor(green);
        if (horizontal)
        {
            bulletX[bulletCount] = pX + 2;
            bulletY[bulletCount] = pY - 1;
            firePlayerBullet(bulletX[bulletCount], bulletY[bulletCount]);
            moveBulletArrays();
            bulletCount++;
            // bulletX_axis = pX + 2;
            // bulletY_axis = pY - 1;
            // gotoxy(bulletX_axis, bulletY_axis);
            // cout << "^";
        }
        else if (vertical)
        {
            bulletX_axis = pX + 2;
            bulletY_axis = pY - 1;
            gotoxy(bulletX_axis, bulletY_axis);
            cout << ">";
        }
        setcolor(white);
    }
}
void moveBulletArrays()
{
    for (int x = 0; x < bulletCount; x++)
    {
        char nextObject = getCharAtxy(bulletY[x] - 1, bulletY[x]);
        if (nextObject == ' ')
        {
            erasePlayerBullet(bulletX[x], bulletY[x]);
            bulletY[x] = bulletY[x] - 1;
            firePlayerBullet(bulletX[x], bulletY[x]);
        }
        else
        {
            erasePlayerBullet(bulletX[x], bulletY[x]);
            eraseBulletFromArray(x);          // index of bullet to be erased
        }
    }
}
void eraseBulletFromArray(int indexToRemove)
{
    for (int x = indexToRemove; x < bulletCount; x++)
    {
        bulletX[x] = bulletX[x + 1];
        bulletY[x] = bulletY[x + 1];
    }
    bulletCount--;

}
void erasePlayerBullet(int x_coord, int y_coord)
{
    gotoxy(x_coord,y_coord);
    cout << " " << endl;
}
void firePlayerBullet(int x_coord, int y_coord)
{
    gotoxy(x_coord,y_coord);
    cout << "^";
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
    if (!e3WallHit){        
        e3Y = e3Y + 1;
        if(e3Y == 20)
            e3WallHit = true;
    }
    else if(e3WallHit){
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
        bonus1 += 1;
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
        bonus1 += 1;
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
        bonus1 +=1;
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
        bonus1 +=1;
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
    // setcolor(lightgreen);
    cout << "#############################################################################" << endl;
    cout << "##                                                                         ##" << endl;
    cout << "##                                              ##                         ##" << endl;
    cout << "##                                              ##                         ##" << endl;
    cout << "##                                                          ##             ##" << endl;
    cout << "##                                                          ##             ##" << endl;
    cout << "##                          ###                             ##             ##" << endl;
    cout << "##       #######            ###                              ######        ##" << endl;
    cout << "##                                                 ##                      ##" << endl;
    cout << "##                                                 ##                      ##" << endl;
    cout << "##                                                                         ##" << endl;
    cout << "##                                                                         ##" << endl;
    cout << "##                                                                         ##" << endl;
    cout << "##                                                                         ##" << endl;
    cout << "##                         ##                                              ##" << endl;
    cout << "##                         ##                                              ##" << endl;
    cout << "##                                                                         ##" << endl;
    cout << "##        ######                                             ######        ##" << endl;
    cout << "##             ##                                           ##             ##" << endl;
    cout << "##             ##                         ==        ==      ##             ##" << endl;
    cout << "##             ##          ##             ||        ||      ##             ##" << endl;
    cout << "##                         ##             []        []                     ##" << endl;
    cout << "##                                        ||        ||                     ##" << endl;
    cout<<R"(##                                        //        \\                     ##)" << endl;
    cout << "#############################################################################" << endl;
    setcolor(white);
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