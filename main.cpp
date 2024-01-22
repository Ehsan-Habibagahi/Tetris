#include <iostream>
#include <windows.h>
#include <vector>
#include <random>
#include <conio.h>
#include "header.h"
using namespace std;
// Globals
int n, m;
int tetNum;
bool inHold = false;
vector<int> complete_lines;
const string reset = "\u001b[0m";
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
    int weigh;
    int height;
    string color;
};
Tetromino *tetromino[5];
Tetromino currentTetro;
Tetromino pendingTetro;
Tetromino holdTetro;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO buffer_info;
// Prototype
void printGuide(string **p, Tetromino tetro = currentTetro);
void updateMap(int i, int j, string color, string shape);
// Functions
void gotoxy(int x, int y)
{
    COORD position = {(short)x, (short)y};
    SetConsoleCursorPosition(hConsole, position);
}
void hideCursor()
{
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &info);
}
void showCursor()
{
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = TRUE;
    SetConsoleCursorInfo(hConsole, &info);
}
void initialPrint(string **p)
{
    gotoxy(0, 1);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            if (j != 0)
            {
                gotoxy(buffer_info.dwCursorPosition.X + 1, buffer_info.dwCursorPosition.Y);
            }
            else
            {
                gotoxy(buffer_info.dwCursorPosition.X + 2, buffer_info.dwCursorPosition.Y);
            }
            if (p[i][j] == "*")
            {
                cout << "◼";
            }
            else
            {
                cout << p[i][j] << "◼"
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
                    return false;
                if (p[x + i][y + j] != "*")
                    return false;
            }
        }
    }
    return true;
}
void printTetro(string shape, bool deleting = false, int x = coord_x, int y = coord_y, Tetromino tetro = currentTetro)
{
    gotoxy(200, 100);
    // cout << "print tetro in " << x << " "
    //  << "y: " << y;
    for (int i = 0; i < tetro.height; i++)
        for (int j = 0; j < tetro.weigh; j++)
        {
            if (tetro.p[i][j] != "*")
            {
                if (deleting == false)
                    updateMap(x + i, y + j, tetro.color, shape);
                else
                    updateMap(x + i, y + j, "", shape);
            }
        }
}
void print_outside_tetro(int x, int y, Tetromino tetro)
{
    gotoxy(x, y);
    for (int i = 0; i < tetro.height; i++)
        for (int j = 0; j < tetro.weigh; j++)
            if (tetro.p[i][j] != "*")
            {
                gotoxy(x + (j * 2), y + i);
                cout << tetro.color << "◼" << reset;
            }
}
void delete_outside_tetro(int x, int y)
{
    for (int i = 1; i < 11; i++)
        for (int j = 1; j < 5; j++)
        {
            gotoxy(x + i, y + j);
            cout << " ";
        }
}
void printB(int x, int y, int w, int h)
{
    gotoxy(x, y);
    cout << "╔";
    for (int i = 0; i < w; i++)
        cout << "═";
    cout << "╗";
    for (int j = 0; j < h; j++)
    {
        gotoxy(x, y + j + 1);
        cout << "║";
        gotoxy(x + w + 1, y + j + 1);
        cout << "║";
    }
    gotoxy(x, y + h + 1);
    cout << "╚";
    for (int i = 0; i < w; i++)
        cout << "═";
    gotoxy(x + w + 1, y + h + 1);
    cout << "╝";
}
void updateMap(int i, int j, string color, string shape)
{
    gotoxy(2 * j + 2, i + 1);
    if (color != "")
        cout << color << shape << reset;
    else
        cout << shape;
}
bool spawn(string **p)
{
    if (!inHold)
    {
        currentTetro = pendingTetro;
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(0, 100);
        int randNum = distrib(gen);
        tetNum = randNum % 5;
        string color = "\u001b[38;5;" + to_string((randNum % 16) + 120) + "m";
        pendingTetro = *tetromino[tetNum];
        pendingTetro.color = color;
        delete_outside_tetro(2 * n + 4, 6);
        print_outside_tetro(2 * n + 5 + (10 - pendingTetro.weigh * 2) / 2, (4 - pendingTetro.height) / 2 + 7, pendingTetro);
    }
    else
    {
        currentTetro = holdTetro;
        inHold = false;
        delete_outside_tetro(2 * n + 4, 0);
    }
    coord_x = 0;
    coord_y = (m - currentTetro.weigh) / 2;
    if (canShape(p, currentTetro, coord_x, coord_y))
    {
        printGuide(p);
        printTetro("◼");
        return true;
    }
    return false;
}
bool goDown(string **p)
{
    if (canShape(p, currentTetro, coord_x + 1, coord_y))
    {
        printTetro("◼", true);
        ++coord_x;
        printTetro("◼");
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
    return false;
}
void hold_tet(string **p)
{
    if (inHold == false && canShape(p, pendingTetro, coord_x, coord_y))
    {
        inHold = true;
        // Delete last tetro
        printTetro("◼", true, coord_x, coord_y, currentTetro);
        // Delete last guide
        printTetro("◼", true, guide_x, coord_y, currentTetro);
        holdTetro = currentTetro;
        currentTetro = pendingTetro;
        // Print hold
        print_outside_tetro(2 * n + 5 + (10 - holdTetro.weigh * 2) / 2, (4 - holdTetro.height) / 2 + 1, holdTetro);
        // Print new tetro
        printTetro("◼");
        // print new guide
        printGuide(p);
        // for show the next tet in another box
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(1, 100);
        int randNum = distrib(gen);
        tetNum = randNum % 5;
        string color = "\u001b[38;5;" + to_string((randNum % 16) + 120) + "m";
        pendingTetro = *tetromino[tetNum];
        pendingTetro.color = color;
        // Delete pending
        delete_outside_tetro(2 * n + 4, 6);
        // Print new pending
        print_outside_tetro(2 * n + 5 + (10 - pendingTetro.weigh * 2) / 2, (4 - pendingTetro.height) / 2 + 7, pendingTetro);
    }
}
void goRight(string **p)
{
    if (canShape(p, currentTetro, coord_x, coord_y + 1))
    {
        printTetro("◼", true);
        // Remove Guide
        printTetro("◼", true, guide_x);
        ++coord_y;
        printGuide(p);
        printTetro("◼");
    }
}
void fitDown(string **p)
{
    printTetro("◼", true);
    printTetro("◼", false, guide_x);
    coord_x = guide_x;
}
void goLeft(string **p)
{
    if (canShape(p, currentTetro, coord_x, coord_y - 1))
    {
        printTetro("◼", true);
        // Remove Guide
        printTetro("◼", true, guide_x);
        --coord_y;
        printGuide(p);
        printTetro("◼");
    }
}
void printGuide(string **p, Tetromino tetro)
{
    guide_x = coord_x;
    while (canShape(p, tetro, guide_x + 1, coord_y))
    {
        ++guide_x;
    }
    printTetro("⛶", false, guide_x);
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

    // int new_x = coord_x + currentTetro.height / 2;
    int new_x = coord_x;
    int new_y = coord_y;
    switch (tetNum)
    {
    case 0:
        if (currentTetro.height == tetromino[0]->height)
            ++new_y;
        else
            new_y--;
        break;
    case 4:
        if (currentTetro.height == tetromino[4]->height)
            new_y++;
        else
            new_y--;

        break;
    default:
        break;
    }

    if (canShape(p, temp, new_x, new_y))
    {
        printTetro("◼", true);
        printTetro("◼", true, guide_x);
        // for(int i =0;i<h;i++)
        // delete[] currentTetro.p[i];
        // delete[] currentTetro.p;
        currentTetro = temp;
        coord_x = new_x;
        coord_y = new_y;
        printGuide(p);
        printTetro("◼");
    }
}
void rotateLeft(string **p)
{
    if (tetNum == 1)
        return;
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
            temp.p[w - j - 1][i] = currentTetro.p[i][j];
    int new_x = coord_x;
    int new_y = coord_y;
    switch (tetNum)
    {
    case 0:
        if (currentTetro.height == tetromino[0]->height)
            ++new_y;
        else
            new_y--;
        break;
    case 2:
        if (currentTetro.height == tetromino[2]->height)
            ++new_y;
        else
            --new_y;

        break;
    case 4:
        if (currentTetro.height == tetromino[4]->height)
            new_y++;
        else
            new_y--;

        break;
    default:
        break;
    }
    if (canShape(p, temp, new_x, new_y))
    {
        printTetro("◼", true);
        printTetro("◼", true, guide_x);
        // for(int i =0;i<h;i++)
        // delete[] currentTetro.p[i];
        // delete[] currentTetro.p;
        currentTetro = temp;
        coord_x = new_x;
        coord_y = new_y;
        printGuide(p);
        printTetro("◼");
    }
}
void flashLine(string **p)
{
    for (int k = 1; k <= 3; k++)
    {
        if (k != 1)
        {
            // Coloring
            for (int i = 0; i < complete_lines.size(); i++)
                for (int j = 0; j < m; j++)
                    updateMap(complete_lines[i], j, p[complete_lines[i]][j], "◼");
        }
        Sleep(300);
        // Whiten
        for (int i = 0; i < complete_lines.size(); i++)
            for (int j = 0; j < m; j++)
                updateMap(complete_lines[i], j, "", "◼");
        Sleep(300);
    }
}
void checkRow(string **p)
{
    complete_lines.clear();
    complete_lines.shrink_to_fit();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (p[i][j] == "*")
                break;
            if (j == m - 1)
                complete_lines.push_back(i);
        }
    }
    // Flashing the lines
    if (complete_lines.size() != 0)
        flashLine(p);
    // Clearing the main board
    for (int i = 0; i < complete_lines.size(); i++)
    {
        for (int j = 0; j < m; j++)
        {
            p[complete_lines[complete_lines.size() - 1 - i]][j] = "*";
        }
    }
    // Pushing the upper rows down↓
    if (complete_lines.size() != 0)
        for (int i = complete_lines[complete_lines.size() - 1]; i > 0; i--)
        {
            for (int j = 0; j < m; j++)
            {
                if (p[i - 1][j] != "*")
                {
                    p[i][j] = p[i - 1][j];
                    p[i - 1][j] = "*";
                    // Whiten
                    updateMap(i-1,j,"","◼");
                    // Coloring
                    updateMap(i,j,p[i][j],"◼");
                }
            }
        }
}
int main()
{
    hideCursor();
    int result = main_menu(1);
    // Exit
    if (result == 3)
    {
        for (int i = 0; i <= 1; i++)
        {
            system("cls");
            cout << "\u001b[38;5;124m";
            cout << "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⢛⣭⣭⣝⡻⢿⣿⣿⡟⢰⣶⣶⣶⣮⣭⣛⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⢡⣿⣿⣿⣿⣿⣦⡙⣿⢸⢸⣿⣿⣿⣿⣿⣿⣷⣎⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⣵⣶⣶⣦⣭⡛⢿⣿⠃⣿⣿⡿⠉⠛⣿⣿⣿⡜⢸⢸⣿⣿⡋⠉⠙⣿⣿⣿⡌⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n⣿⣿⣿⡿⠟⣛⡻⣿⣿⡏⢸⣿⣿⠟⠿⣿⣿⣷⡙⢀⢿⣿⣷⢠⠠⢸⣿⣿⡇⢸⢹⣿⣿⢃⡄⠟⣿⣿⣿⠇⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n⣿⡿⣩⣶⣿⣿⣿⠎⢿⢡⢸⣿⣿⠀⠀⡜⣿⣿⣷⠘⠜⣿⣿⣶⣴⣿⣿⣿⠇⢸⣸⣿⣿⣷⣶⣿⣿⣿⡿⢰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n⠟⣰⣿⣿⠋⡋⠀⠀⣨⡈⢆⢿⣿⣧⣁⣁⣿⣿⣿⠀⠀⠘⢿⣿⣿⣿⡿⠋⣸⠸⠹⠿⡿⠿⠿⠿⠿⠛⣠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n⠀⣿⣿⡇⡄⢡⣴⣿⣿⣿⡀⠈⠻⣿⣿⣿⣿⣿⠟⢸⣦⡀⠂⠈⠉⠉⠀⣴⡏⠀⠀⠀⠀⠀⠀⣀⣤⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n⢀⢻⣿⣷⡄⠢⠉⠉⣿⣿⣿⠀⠀⠎⠉⠉⠉⠁⢠⣿⣿⣿⡷⢶⣶⡖⢩⣭⣷⣶⢰⢋⢰⣶⣶⣶⣶⣶⣶⣶⣶⢸⣿⣿⡿⠋⣭⣝⣛⠿\n⡜⠇⠹⢿⣿⣷⣶⣾⣿⣿⠟⠈⣷⣦⣤⣤⣤⣶⡿⠋⢵⣶⣾⣷⡝⠀⣿⣿⣿⡇⣞⣿⣾⣿⣿⣿⠟⠿⠿⠿⠿⢸⣿⡏⡾⢸⣿⣿⣿⡟\n⣿⣄⠀⠠⡙⠛⢛⠛⠋⠁⢀⡼⢟⣫⣭⣶⣤⣝⠁⡀⠀⠙⢿⣿⣿⣶⣿⣿⡿⢸⡇⣿⣿⣿⣿⣿⣀⣀⣀⠀⢠⣿⡿⣸⡇⣿⣿⣿⣿⣧\n⣿⣿⣷⣦⣤⣀⣀⣀⣤⣴⡏⢴⣿⣿⡟⠛⢻⣿⣷⢹⣦⡀⠀⠙⠿⣿⣿⣿⠣⣿⡇⣿⣿⣿⣿⣿⣿⣿⣿⡿⣼⣿⢇⣿⣸⣿⣿⣿⣿⣿\n⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢸⡜⣿⣿⣷⣤⣾⣿⡋⣚⢿⣿⣦⡀⢀⢹⣿⣿⡇⣿⡇⡏⣿⣿⣿⡿⠀⠉⠉⢁⣿⡿⣸⠇⣿⣿⣿⣿⣿⣿\n⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⢿⡸⣿⣿⣿⡿⢿⣿⣿⣷⡝⣿⣿⡼⡎⣿⣿⣿⢸⡇⡇⣿⣿⣿⣷⣶⣶⣶⡎⣿⣃⠁⠀⠀⠈⠙⣋⣿⣿\n⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡎⣧⢻⣿⣿⡆⠀⢸⣿⣿⣷⢹⣿⡇⣷⢸⡿⠿⠊⡗⠇⠙⠛⠛⠻⠿⠿⠿⢡⣿⠟⢡⣶⣷⣶⡜⢿⣿⣿\n⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡼⣧⢻⣿⣿⣶⣿⣿⠟⠁⣾⣿⣿⠘⠀⠀⢀⣼⣇⣀⠀⠀⠀⠀⠀⠀⣠⣾⠃⠁⣿⣿⣿⣿⡟⣸⣿⣿\n⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⢻⣆⠿⠿⠛⠉⠀⢀⣼⣿⣿⣿⣷⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣾⣿⣿⡄⠀⠈⠙⠛⠛⣱⣿⣿⣿\n⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⠛⠀⢀⣠⣤⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣶⣶⣶⣿⣿⣿⣿⣿";
            Sleep(300);
            system("cls");
            cout << "\u001b[38;5;123m";
            cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡤⠒⠒⠢⢄⡀⠀⠀⢠⡏⠉⠉⠉⠑⠒⠤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡞⠀⠀⠀⠀⠀⠙⢦⠀⡇⡇⠀⠀⠀⠀⠀⠀⠈⠱⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⠊⠉⠉⠙⠒⢤⡀⠀⣼⠀⠀⢀⣶⣤⠀⠀⠀⢣⡇⡇⠀⠀⢴⣶⣦⠀⠀⠀⢳⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n⠀⠀⠀⢀⣠⠤⢄⠀⠀⢰⡇⠀⠀⣠⣀⠀⠀⠈⢦⡿⡀⠀⠈⡟⣟⡇⠀⠀⢸⡇⡆⠀⠀⡼⢻⣠⠀⠀⠀⣸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n⠀⢀⠖⠉⠀⠀⠀⣱⡀⡞⡇⠀⠀⣿⣿⢣⠀⠀⠈⣧⣣⠀⠀⠉⠋⠀⠀⠀⣸⡇⠇⠀⠀⠈⠉⠀⠀⠀⢀⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n⣠⠏⠀⠀⣴⢴⣿⣿⠗⢷⡹⡀⠀⠘⠾⠾⠀⠀⠀⣿⣿⣧⡀⠀⠀⠀⢀⣴⠇⣇⣆⣀⢀⣀⣀⣀⣀⣤⠟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n⣿⠀⠀⢸⢻⡞⠋⠀⠀⠀⢿⣷⣄⠀⠀⠀⠀⠀⣠⡇⠙⢿⣽⣷⣶⣶⣿⠋⢰⣿⣿⣿⣿⣿⣿⠿⠛⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n⡿⡄⠀⠈⢻⣝⣶⣶⠀⠀⠀⣿⣿⣱⣶⣶⣶⣾⡟⠀⠀⠀⢈⡉⠉⢩⡖⠒⠈⠉⡏⡴⡏⠉⠉⠉⠉⠉⠉⠉⠉⡇⠀⠀⢀⣴⠒⠢⠤⣀\n⢣⣸⣆⡀⠀⠈⠉⠁⠀⠀⣠⣷⠈⠙⠛⠛⠛⠉⢀⣴⡊⠉⠁⠈⢢⣿⠀⠀⠀⢸⠡⠀⠁⠀⠀⠀⣠⣀⣀⣀⣀⡇⠀⢰⢁⡇⠀⠀⠀⢠\n⠀⠻⣿⣟⢦⣤⡤⣤⣴⣾⡿⢃⡠⠔⠒⠉⠛⠢⣾⢿⣿⣦⡀⠀⠀⠉⠀⠀⢀⡇⢸⠀⠀⠀⠀⠀⠿⠿⠿⣿⡟⠀⢀⠇⢸⠀⠀⠀⠀⠘\n⠀⠀⠈⠙⠛⠿⠿⠿⠛⠋⢰⡋⠀⠀⢠⣤⡄⠀⠈⡆⠙⢿⣿⣦⣀⠀⠀⠀⣜⠀⢸⠀⠀⠀⠀⠀⠀⠀⠀⢀⠃⠀⡸⠀⠇⠀⠀⠀⠀⠀\n⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⢣⠀⠀⠈⠛⠁⠀⢴⠥⡀⠀⠙⢿⡿⡆⠀⠀⢸⠀⢸⢰⠀⠀⠀⢀⣿⣶⣶⡾⠀⢀⠇⣸⠀⠀⠀⠀⠀⠀\n⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠹⡀⢇⠀⠀⠀⢀⡀⠀⠀⠈⢢⠀⠀⢃⢱⠀⠀⠀⡇⢸⢸⠀⠀⠀⠈⠉⠉⠉⢱⠀⠼⣾⣿⣿⣷⣦⠴⠀⠀\n⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢱⠘⡄⠀⠀⢹⣿⡇⠀⠀⠈⡆⠀⢸⠈⡇⢀⣀⣵⢨⣸⣦⣤⣤⣄⣀⣀⣀⡞⠀⣠⡞⠉⠈⠉⢣⡀⠀⠀\n⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢃⠘⡄⠀⠀⠉⠀⠀⣠⣾⠁⠀⠀⣧⣿⣿⡿⠃⠸⠿⣿⣿⣿⣿⣿⣿⠟⠁⣼⣾⠀⠀⠀⠀⢠⠇⠀⠀\n⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⡄⠹⣀⣀⣤⣶⣿⡿⠃⠀⠀⠀⠈⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠁⠀⠀⢻⣿⣷⣦⣤⣤⠎⠀⠀⠀\n⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣤⣿⡿⠟⠛⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠉⠉⠀⠀⠀⠀⠀";
            Sleep(300);
            system("cls");
            cout << "\u001b[38;5;124m";
            cout << "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⢛⣭⣭⣝⡻⢿⣿⣿⡟⢰⣶⣶⣶⣮⣭⣛⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⢡⣿⣿⣿⣿⣿⣦⡙⣿⢸⢸⣿⣿⣿⣿⣿⣿⣷⣎⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⣵⣶⣶⣦⣭⡛⢿⣿⠃⣿⣿⡿⠉⠛⣿⣿⣿⡜⢸⢸⣿⣿⡋⠉⠙⣿⣿⣿⡌⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n⣿⣿⣿⡿⠟⣛⡻⣿⣿⡏⢸⣿⣿⠟⠿⣿⣿⣷⡙⢀⢿⣿⣷⢠⠠⢸⣿⣿⡇⢸⢹⣿⣿⢃⡄⠟⣿⣿⣿⠇⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n⣿⡿⣩⣶⣿⣿⣿⠎⢿⢡⢸⣿⣿⠀⠀⡜⣿⣿⣷⠘⠜⣿⣿⣶⣴⣿⣿⣿⠇⢸⣸⣿⣿⣷⣶⣿⣿⣿⡿⢰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n⠟⣰⣿⣿⠋⡋⠀⠀⣨⡈⢆⢿⣿⣧⣁⣁⣿⣿⣿⠀⠀⠘⢿⣿⣿⣿⡿⠋⣸⠸⠹⠿⡿⠿⠿⠿⠿⠛⣠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n⠀⣿⣿⡇⡄⢡⣴⣿⣿⣿⡀⠈⠻⣿⣿⣿⣿⣿⠟⢸⣦⡀⠂⠈⠉⠉⠀⣴⡏⠀⠀⠀⠀⠀⠀⣀⣤⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n⢀⢻⣿⣷⡄⠢⠉⠉⣿⣿⣿⠀⠀⠎⠉⠉⠉⠁⢠⣿⣿⣿⡷⢶⣶⡖⢩⣭⣷⣶⢰⢋⢰⣶⣶⣶⣶⣶⣶⣶⣶⢸⣿⣿⡿⠋⣭⣝⣛⠿\n⡜⠇⠹⢿⣿⣷⣶⣾⣿⣿⠟⠈⣷⣦⣤⣤⣤⣶⡿⠋⢵⣶⣾⣷⡝⠀⣿⣿⣿⡇⣞⣿⣾⣿⣿⣿⠟⠿⠿⠿⠿⢸⣿⡏⡾⢸⣿⣿⣿⡟\n⣿⣄⠀⠠⡙⠛⢛⠛⠋⠁⢀⡼⢟⣫⣭⣶⣤⣝⠁⡀⠀⠙⢿⣿⣿⣶⣿⣿⡿⢸⡇⣿⣿⣿⣿⣿⣀⣀⣀⠀⢠⣿⡿⣸⡇⣿⣿⣿⣿⣧\n⣿⣿⣷⣦⣤⣀⣀⣀⣤⣴⡏⢴⣿⣿⡟⠛⢻⣿⣷⢹⣦⡀⠀⠙⠿⣿⣿⣿⠣⣿⡇⣿⣿⣿⣿⣿⣿⣿⣿⡿⣼⣿⢇⣿⣸⣿⣿⣿⣿⣿\n⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢸⡜⣿⣿⣷⣤⣾⣿⡋⣚⢿⣿⣦⡀⢀⢹⣿⣿⡇⣿⡇⡏⣿⣿⣿⡿⠀⠉⠉⢁⣿⡿⣸⠇⣿⣿⣿⣿⣿⣿\n⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⢿⡸⣿⣿⣿⡿⢿⣿⣿⣷⡝⣿⣿⡼⡎⣿⣿⣿⢸⡇⡇⣿⣿⣿⣷⣶⣶⣶⡎⣿⣃⠁⠀⠀⠈⠙⣋⣿⣿\n⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡎⣧⢻⣿⣿⡆⠀⢸⣿⣿⣷⢹⣿⡇⣷⢸⡿⠿⠊⡗⠇⠙⠛⠛⠻⠿⠿⠿⢡⣿⠟⢡⣶⣷⣶⡜⢿⣿⣿\n⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡼⣧⢻⣿⣿⣶⣿⣿⠟⠁⣾⣿⣿⠘⠀⠀⢀⣼⣇⣀⠀⠀⠀⠀⠀⠀⣠⣾⠃⠁⣿⣿⣿⣿⡟⣸⣿⣿\n⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⢻⣆⠿⠿⠛⠉⠀⢀⣼⣿⣿⣿⣷⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣾⣿⣿⡄⠀⠈⠙⠛⠛⣱⣿⣿⣿\n⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⠛⠀⢀⣠⣤⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣶⣶⣶⣿⣿⣿⣿⣿";
            Sleep(300);
        }
        cout << reset;
        exit(0);
    }
    else if (result == 2)
    {
        exit(0);
    }
    else if (result == 1)
    {
        // Defining Tetrominos (:
        // 0 Straight (attracted to members of the opposite sex)
        Tetromino tet_straight;
        tet_straight.p = new string *[1];
        tet_straight.p[0] = new string[4];
        tet_straight.height = 1;
        tet_straight.weigh = 4;
        tet_straight.pivot.x = 0;
        tet_straight.pivot.y = 1;
        for (int i = 0; i < 4; i++)
            tet_straight.p[0][i] = "1";
        // 1 Square
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
        // 2 T
        Tetromino tet_t;
        tet_t.p = new string *[2];
        for (int i = 0; i < 2; i++)
            tet_t.p[i] = new string[3];
        tet_t.height = 2;
        tet_t.weigh = 3;
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 3; j++)
                tet_t.p[i][j] = "1";
        tet_t.p[1][0] = "*";
        tet_t.p[1][2] = "*";
        // 3 L
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
        // 4 Skew
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
        system("cls");
        showCursor();
        cout << "Gɪᴠᴇ ᴍᴇ ᴅɪᴍᴇɴᴛɪᴏɴs: ";
        cin >> n >> m;
        while (n < 5 || m < 5)
        {
            cout << "Gɪᴠᴇ ᴍᴇ ᴅɪᴍᴇɴᴛɪᴏɴs: ";
            cin >> n >> m;
        }
        hideCursor();
        string **p = new string *[n];
        for (int i = 0; i < n; i++)
        {
            p[i] = new string[m];
            for (int j = 0; j < m; j++)
                p[i][j] = "*";
        }
        system("cls");
        initialPrint(p);
        // Printing boarders
        // Main boarder
        printB(0, 0, 2 * n + 1, m);
        // Hold Boarder
        printB(2 * n + 4, 0, 10, 4);
        // Pending Boarder
        printB(2 * n + 4, 6, 10, 4);
        bool wentDown = false;
        bool game_continue = true;
        int input;
        // Generating first pending tetro
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(1, 100);
        int randNum = distrib(gen);
        tetNum = randNum % 5;
        string color = "\u001b[38;5;" + to_string((randNum % 16) + 120) + "m";
        pendingTetro = *tetromino[tetNum];
        pendingTetro.color = color;
        int count_move = 0;
        while (true)
        {
            if (!wentDown)
            {
                checkRow(p);
                game_continue = spawn(p);
                FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
            }
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
                        goRight(p);
                    // Left
                    if (input == 75)
                        goLeft(p);
                    // Rotate right
                    if (input == 72)
                        rotateRight(p);
                    if (kbhit() && count_move < 1)
                    {
                        // Easy mode
                        goto getinput;
                        ++count_move;
                    }
                    else
                        count_move = 0;
                }
                else
                {
                    if (input == 32)
                    {
                        fitDown(p);
                    }
                    if (input == 104 && inHold == false)
                        hold_tet(p);
                    if (input == 122)
                        rotateLeft(p);
                }
            }
            wentDown = goDown(p);
            // hidecursor();
        }

        cout << "done";
    }
}