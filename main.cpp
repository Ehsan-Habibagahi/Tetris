#include <iostream>
#include <windows.h>
#include <algorithm>
#include <vector>
#include <conio.h>
using namespace std;
// Globals
int n, m;
int tetNum;
const string reset = "\u001b[0m";
// struct Tetromino_coord
// {
//     int X;
//     int Y;
// }; =
int coord_x, coord_y;
int guide_x;
struct point
{
    int x, y;
};
struct Tetromino
{
    string **p;
    point pivot;
    // bool isguide;
    int weigh;
    int height;
    string color;
};
Tetromino *tetromino[5];
Tetromino currentTetro;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO buffer_info;
// Prototype
void printGuide(string **p);
// Functions
void gotoxy(int x, int y)
{
    COORD position = {(short)x, (short)y};
    SetConsoleCursorPosition(hConsole, position);
}
void hidecursor()
{
    //    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &info);
}
void initialPrint(string **p)
{
    gotoxy(0, 0);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (j != 0)
            {
                GetConsoleScreenBufferInfo(hConsole, &buffer_info);
                gotoxy(buffer_info.dwCursorPosition.X + 1, buffer_info.dwCursorPosition.Y);
            }
            if (p[i][j] == "*")
            {
                cout << "*";
            }
            else
            {
                cout << p[i][j] << "*"
                     << reset;
            }
        }
        GetConsoleScreenBufferInfo(hConsole, &buffer_info);
        gotoxy(0, buffer_info.dwCursorPosition.Y + 1);
    }
}
bool canShape(string **p, Tetromino tetro, int x, int y)
{
    for (int i = 0; i < tetro.height; i++)
    {
        for (int j = 0; j < tetro.weigh; j++)
        {
            if (tetro.p[i][j] != "*")
            {
                if (x + i >= n || y + j >= m || x + i < 0 || y + j < 0)
                {
                    // cout<<"returned false in x: "<<x<<"y: "<<y<<"i: "<<i<<"j: "<<j;
                    return false;
                }
                if (p[x + i][y + j] != "*")
                {
                    // cout<<"lllreturned false in x: "<<x<<"y: "<<y<<"i: "<<i<<"j: "<<j;
                    return false;
                }
            }
        }
    }
    return true;
}
void printTetro(string shape, bool deleting = false, int x = coord_x, int y = coord_y)
{
    for (int i = 0; i < currentTetro.height; i++)
        for (int j = 0; j < currentTetro.weigh; j++)
        {
            if (currentTetro.p[i][j] != "*")
            {
                gotoxy(2 * (y + j), x + i);
                if (deleting == false)
                    cout << currentTetro.color;
                cout << shape << reset;
            }
        }
}
bool spawn(string **p)
{
    srand(static_cast<unsigned int>(time(nullptr)));
    tetNum = rand() % 5;
    string color = "\u001b[38;5;" + to_string((rand() % 16) + 120) + "m";
    currentTetro = *tetromino[tetNum];
    // tetromino[tetNum]->color = color;
    currentTetro.color = color;
    // cout << endl
    //  << "Tetnum: " << tetNum;
    coord_x = 0;
    coord_y = (m - tetromino[tetNum]->weigh) / 2;
    // cout << "Positon of y: " << coord_y;
    if (canShape(p, *tetromino[tetNum], coord_x, coord_y))
    {
        // if(guide_x != coord_x)
        printGuide(p);
        printTetro("*");
        return true;
    }
    return false;
}
bool goDown(string **p)
{
    if (canShape(p, currentTetro, coord_x + 1, coord_y))
    {
        printTetro("*", true);
        ++coord_x;
        printTetro("*");
        return true;
    }
    else
    {
        for (int i = 0; i < currentTetro.height; i++)
        {
            for (int j = 0; j < currentTetro.weigh; j++)
            {
                if (currentTetro.p[i][j] != "*")
                {
                    p[coord_x + i][coord_y + j] = currentTetro.color;
                }
            }
        }
    }
    // cout<<"couldn't shape";
    return false;
}
void goRigh(string **p)
{
    if (canShape(p, currentTetro, coord_x, coord_y + 1))
    {
        printTetro("*", true);
        // Remove Guide
        printTetro("*", true, guide_x);
        ++coord_y;
        printGuide(p);
        printTetro("*");
    }
}
void fitDown(string **p)
{
    printTetro("*", true);
    printTetro("*", false, guide_x);
    coord_x = guide_x;
}
void goLeft(string **p)
{
    if (canShape(p, currentTetro, coord_x, coord_y - 1))
    {
        printTetro("*", true);
        // Remove Guide
        printTetro("*", true, guide_x);
        --coord_y;
        printGuide(p);
        printTetro("*");
    }
}
void printGuide(string **p)
{
    guide_x = coord_x;
    while (canShape(p, currentTetro, guide_x + 1, coord_y))
    {
        ++guide_x;
    }
    // cout<<"guide:"<<guide_x;
    printTetro("-", false, guide_x);
}
void rotateRight(string **p)
{
    int w = currentTetro.weigh;
    int h = currentTetro.height;
    Tetromino temp;
    temp.color = currentTetro.color;
    temp.height = w;
    temp.weigh = h;
    temp.p = new string *[w];
    for (int i = 0; i < w; i++)
        temp.p[i] = new string[h];
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            temp.p[j][h - i - 1] = currentTetro.p[i][j];

    int new_x = coord_x + currentTetro.height / 2;
    int new_y = coord_y;
    if (canShape(p, temp, new_x, new_y))
    {
        // tetromino[tetNum] = &temp;
        printTetro("*", true);
        printTetro("*", true, guide_x);
        // for(int i =0;i<h;i++)
        // delete[] currentTetro.p[i];
        // delete[] currentTetro.p;
        currentTetro = temp;
        coord_x = new_x;
        coord_y = new_y;
        printGuide(p);
        printTetro("*");
    }
}
// void delete_guide(string **p)
// {
// printTetro("*",true,guide_x);
// }
int main()
{
    // Defining Tetrominos (:
    // Straight (attracted to members of the opposite sex)
    Tetromino tet_straight;
    tet_straight.p = new string *[1];
    tet_straight.p[0] = new string[4];
    tet_straight.height = 1;
    tet_straight.weigh = 4;
    tet_straight.pivot.x = 0;
    tet_straight.pivot.y = 1;
    for (int i = 0; i < 4; i++)
        tet_straight.p[0][i] = "1";
    // Square
    Tetromino tet_square;
    tet_square.p = new string *[2];
    tet_square.p[0] = new string[2];
    tet_square.p[1] = new string[2];
    tet_square.height = 2;
    tet_square.weigh = 2;
    tet_square.pivot.x = 0;
    tet_square.pivot.y = 0;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            tet_square.p[i][j] = "1";
    // T
    Tetromino tet_t;
    tet_t.p = new string *[2];
    for (int i = 0; i < 2; i++)
        tet_t.p[i] = new string[3];
    tet_t.height = 2;
    tet_t.weigh = 3;
    tet_t.pivot.x = 1;
    tet_t.pivot.y = 1;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++)
            tet_t.p[i][j] = "1";
    tet_t.p[1][0] = "*";
    tet_t.p[1][2] = "*";
    // L
    Tetromino tet_l;
    tet_l.p = new string *[3];
    for (int i = 0; i < 3; i++)
        tet_l.p[i] = new string[2];
    tet_l.height = 3;
    tet_l.weigh = 2;
    tet_l.pivot.x = 1;
    tet_l.pivot.y = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 2; j++)
            tet_l.p[i][j] = "1";
    tet_l.p[0][1] = "*";
    tet_l.p[1][1] = "*";
    // Skew
    Tetromino tet_skew;
    tet_skew.p = new string *[2];
    for (int i = 0; i < 3; i++)
        tet_skew.p[i] = new string[3];
    tet_skew.height = 2;
    tet_skew.weigh = 3;
    tet_skew.pivot.x = 1;
    tet_l.pivot.y = 1;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++)
            tet_skew.p[i][j] = "1";
    tet_skew.p[0][0] = "*";
    tet_skew.p[1][2] = "*";
    tetromino[0] = &tet_straight;
    tetromino[1] = &tet_square;
    tetromino[2] = &tet_t;
    tetromino[3] = &tet_l;
    tetromino[4] = &tet_skew;
    // cout<< tetromino[2]->p[1][1];
    // cout<< (*tetromino[2]).height;
    system("cls");
    cout << "Dimention?";
    cin >> n >> m;
    while (n < 5 || m < 5)
    {
        cout << "Dimention?";
        cin >> n >> m;
    }
    string **p = new string *[n];
    for (int i = 0; i < n; i++)
    {
        p[i] = new string[m];
        for (int j = 0; j < m; j++)
            p[i][j] = "*";
    }
    // p[0][m/2] = "\u001b[38;5;154m";
    system("cls");
    hidecursor();
    initialPrint(p);
    bool wentDown = false;
    bool game_continue = true;
    int input;
    while (true)
    {
        if (!wentDown)
            game_continue = spawn(p);
        if (!game_continue)
            break;
        Sleep(500);
        if (kbhit())
        {
        getinput:
            input = getch();

            if (input == 224)
            {
                input = getch();
                // Fushing the buffer
                //  FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
                //  Right
                if (input == 77)
                    goRigh(p);
                // Left
                if (input == 75)
                    goLeft(p);
                if (input == 72)
                    rotateRight(p);
                if (kbhit())
                    // Easy mode
                    goto getinput;
            }
            else
            {
                if (input == 32)
                {
                    fitDown(p);
                }
            }
        }
        wentDown = goDown(p);
    }
    cout << "done";
}