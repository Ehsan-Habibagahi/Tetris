#include <iostream>
#include <windows.h>
#include <algorithm>
#include <vector>
using namespace std;
// Globals (:
int n, m;
struct Moving
{
    int X;
    int Y;
};
Moving moving[4];
const int offset = 10;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO buffer_info;

// Functions
void gotoxy(int x, int y)
{
    COORD position = {(short)x, (short)y};
    SetConsoleCursorPosition(hConsole, position);
}
void print(string **p)
{
    gotoxy(0, 0);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (j != 0)
            {
                GetConsoleScreenBufferInfo(hConsole, &buffer_info);
                gotoxy(++buffer_info.dwCursorPosition.X, buffer_info.dwCursorPosition.Y);
            }
            if (p[i][j] == "*")
            {
                cout << "*";
            }
            else
            {
                cout << p[i][j] << "*"
                     << "\u001b[0m";
            }
        }
        GetConsoleScreenBufferInfo(hConsole, &buffer_info);
        gotoxy(0, ++buffer_info.dwCursorPosition.Y);
    }
}
bool canShape1(int x, int y, string **p)
{
    if (p[x - 1][y] == "*" && p[x][y - 1] == "*" && p[x][y] == "*" && p[x][y + 1] == "*")
        if (x - 1 >= 0 && x < n && y - 1 >= 0 && y + 1 < m)
            return true;
    return false;
}
void spawn(string **p)
{
    srand(static_cast<unsigned int>(time(nullptr)));
    int randNum = rand() % 7;
    string color = "\u001b[38;5;" + to_string(rand() % 223) + "m";
    randNum = 0;
    vector <vector<string>> s1={{"0","1","0"},{"1","1","1"}};   
    if (randNum == 0)
    {
        // if (canShape1(1, m / 2, p))
        // {
        //     p[0][m / 2] = color;
        //     p[1][m / 2 - 1] = color;
        //     p[1][m / 2] = color;
        //     p[1][m / 2 + 1] = color;
        //     moving[0].X = 0;
        //     moving[0].Y = m / 2;
        //     moving[1].X = 1;
        //     moving[1].Y = m / 2 - 1;
        //     moving[2].X = 1;
        //     moving[2].Y = m / 2;
        //     moving[3].X = 1;
        //     moving[3].Y = m / 2 + 1;
        // }

    }
}
int main()
{
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
    print(p);
    while (true)
    {
        spawn(p);
        print(p);
        Sleep(500);
        break;
    }
}