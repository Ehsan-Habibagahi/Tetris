/*==================================================================+
 |~-~-~-~-~-~-~-~-~-~-~-بسم الله الرحمن الرحیم-~-~-~-~-~-~-~-~-~-~-~|
 |که پاداش هر زخمه سنگی را دستان کریم تو میوه ای چند شیرین ایثار کند|
 |~-~-~-~-~-~-~-~-~-~-~-~-TETRIS SIMPLE GAME-~-~-~-~-~-~-~-~-~-~-~-~|
 |~-~-~-~-~-~-~-~-~-~-AUTHOR: L4M3R BU7 WR3CK3R~-~-~-~-~-~-~-~-~-~-~|
 |~-~-~-~-~-~-~-~-~-~-CREATED WITH LOTS OF LOVE!-~-~-~-~-~-~-~-~-~-~|
 +==================================================================*/
#include <iostream>
#include <windows.h>
#include <vector>
#include <random>
#include <conio.h>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include "header.h"

using namespace std;
// Globals
string **p;
int n, m;
int tetNum;
int sleepTime;
bool isGuided = true;
int score = 0;
int start_time;
int period2 = 0;
int level;
int number_of_spoil = 0;
string name;
bool inHold = false;
vector<int> complete_lines;
const string reset = "\u001b[0m";
int coord_x, coord_y;
int spoiler_x, spoiler_y;
int x_offset, y_offset;
int guide_x;
bool wentDown = false;
struct Tetromino
{
    string **p;
    int width;
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
void spoilTetro(string **p);
bool spawn(string **p);
void addSpoiler(string **p);
void lost_game();
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
    gotoxy(0 + x_offset, 1 + y_offset);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            if (j != 0)
                cout << " ";
            // gotoxy(buffer_info.dwCursorPosition.X + 1, buffer_info.dwCursorPosition.Y);
            else
                gotoxy(buffer_info.dwCursorPosition.X + 2, buffer_info.dwCursorPosition.Y);
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
        gotoxy(0 + x_offset, buffer_info.dwCursorPosition.Y + 1);
    }
}
bool canShape(string **p, Tetromino tetro, int x, int y)
{
    for (int i = 0; i < tetro.height; i++)
    {
        for (int j = 0; j < tetro.width; j++)
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
    bool spoiled = false;
    for (int i = 0; i < tetro.height; i++)
        for (int j = 0; j < tetro.width; j++)
        {
            if (tetro.p[i][j] != "*")
            {
                if (shape == "◼" && deleting == false && x + i == spoiler_x && y + j == spoiler_y)
                {
                    spoiled = true;
                }
                if (deleting == false)
                    updateMap(x + i, y + j, tetro.color, shape);
                else
                    updateMap(x + i, y + j, "", shape);
            }
        }
    if (spoiled)
    {
        spoilTetro(p);
        addSpoiler(p);
        spawn(p);
    }
}
void print_outside_tetro(int x, int y, Tetromino tetro)
{
    gotoxy(x, y);
    for (int i = 0; i < tetro.height; i++)
        for (int j = 0; j < tetro.width; j++)
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
            gotoxy(x + i + x_offset, y_offset + y + j);
            cout << " ";
        }
}
void printBoarder(int x, int y, int w, int h)
{
    cout << "\u001b[38;5;245m";
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
    cout << reset;
}
void delete_score()
{
    for (int i = 0; i < 5; i++)
    {
        gotoxy(x_offset + 8 + i, 3);
        cout << ' ';
    }
}
void print_score()
{
    gotoxy(x_offset + 8, 3);
    cout << score;
}
void updateMap(int i, int j, string color, string shape)
{
    gotoxy(2 * j + 2 + x_offset, i + 1 + y_offset);
    if (color != "")
        cout << color << shape << reset;
    else
        cout << shape;
}
void randomRotation(Tetromino &tetro)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, 100);
    int randNum = distrib(gen);
    for (int k = 0; k < randNum % 3; k++)
    {
        int w = tetro.width;
        int h = tetro.height;
        Tetromino temp;
        temp.color = tetro.color;
        temp.height = w;
        temp.width = h;
        temp.p = new string *[w];
        for (int i = 0; i < w; i++)
            temp.p[i] = new string[h];
        for (int i = 0; i < h; i++)
            for (int j = 0; j < w; j++)
                temp.p[j][h - i - 1] = tetro.p[i][j];
        tetro = temp;
    }
}
void addSpoiler(string **p)
{
    do
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(0, 100);
        int randNum = distrib(gen);
        spoiler_x = randNum % n;
        spoiler_y = randNum % m;
    } while (p[spoiler_x][spoiler_y] != "*");
    updateMap(spoiler_x, spoiler_y, "", "🦆");
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
        // tetNum = randNum % 7;
        tetNum = 1;
        string color = "\u001b[38;5;" + to_string((randNum % 16) + 120) + "m";
        pendingTetro = *tetromino[tetNum];
        pendingTetro.color = color;
        randomRotation(pendingTetro);
        delete_outside_tetro(2 * m + 4, 8);
        print_outside_tetro(2 * m + 5 + (10 - pendingTetro.width * 2) / 2 + x_offset, (4 - pendingTetro.height) / 2 + 9 + y_offset, pendingTetro);
    }
    else
    {
        currentTetro = holdTetro;
        inHold = false;
        delete_outside_tetro(2 * m + 4, 1);
    }
    coord_x = 0;
    coord_y = (m - currentTetro.width) / 2;
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
            for (int j = 0; j < currentTetro.width; j++)
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
        print_outside_tetro(2 * m + 5 + (10 - holdTetro.width * 2) / 2 + x_offset, (4 - holdTetro.height) / 2 + 2 + y_offset, holdTetro);
        // Print new tetro
        printTetro("◼");
        // print new guide
        printGuide(p);
        // For show the next tet in another box
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(1, 100);
        int randNum = distrib(gen);
        // tetNum = randNum % 7;
        tetNum = 1;
        string color = "\u001b[38;5;" + to_string((randNum % 16) + 120) + "m";
        pendingTetro = *tetromino[tetNum];
        pendingTetro.color = color;
        // Delete pending
        delete_outside_tetro(2 * m + 4, 8);
        // Print new pending
        print_outside_tetro(2 * m + 5 + (10 - pendingTetro.width * 2) / 2 + x_offset, (4 - pendingTetro.height) / 2 + 9 + y_offset, pendingTetro);
    }
}
void goRight(string **p)
{
    if (canShape(p, currentTetro, coord_x, coord_y + 1))
    {
        PlaySound(TEXT("data/Tap.wav"), NULL, SND_FILENAME | SND_ASYNC);
        printTetro("◼", true);
        // Remove Guide

        printTetro("◼", true, guide_x);
        ++coord_y;
        printGuide(p);
        printTetro("◼");
    }
}
void down(string **p)
{
    if (canShape(p, currentTetro, coord_x + 1, coord_y))
    {
        PlaySound(TEXT("data/Tap.wav"), NULL, SND_FILENAME | SND_ASYNC);
        printTetro("◼", true);
        // Remove Guide
        printTetro("◼", true, guide_x);
        ++coord_x;
        printGuide(p);
        printTetro("◼");
        ++score;
        delete_score();
        print_score();
    }
}
void fitDown(string **p)
{
    PlaySound(TEXT("data/sonic2.wav"), NULL, SND_FILENAME | SND_ASYNC);
    printTetro("◼", true);
    printTetro("◼", false, guide_x);
    score += (guide_x - coord_x);
    coord_x = guide_x;
    delete_score();
    print_score();
}
void goLeft(string **p)
{
    if (canShape(p, currentTetro, coord_x, coord_y - 1))
    {
        PlaySound(TEXT("data/Tap.wav"), NULL, SND_FILENAME | SND_ASYNC);
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
    if (isGuided)
        printTetro("⛶", false, guide_x);
}
void rotateRight(string **p)
{
    int w = currentTetro.width;
    int h = currentTetro.height;
    Tetromino temp;
    temp.color = currentTetro.color;
    temp.height = w;
    temp.width = h;
    temp.p = new string *[w];
    for (int i = 0; i < w; i++)
        temp.p[i] = new string[h];
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            temp.p[j][h - i - 1] = currentTetro.p[i][j];

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
        PlaySound(TEXT("data/sonic.wav"), NULL, SND_FILENAME | SND_ASYNC);
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
    int w = currentTetro.width;
    int h = currentTetro.height;
    Tetromino temp;
    temp.color = currentTetro.color;
    temp.height = w;
    temp.width = h;
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
        PlaySound(TEXT("data/sonic.wav"), NULL, SND_FILENAME | SND_ASYNC);

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
            PlaySound(TEXT("data/Duck.wav"), NULL, SND_FILENAME | SND_ASYNC);
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
void spoilTetro(string **p)
{
    for (int k = 1; k <= 3; k++)
    {
        // Whiten
        for (int i = 0; i < currentTetro.height; i++)
            for (int j = 0; j < currentTetro.width; j++)
            {
                if (currentTetro.p[i][j] != "*")
                    updateMap(coord_x + i, coord_y + j, "", "▧");
            }
        Sleep(300);
        // coloring
        for (int i = 0; i < currentTetro.height; i++)
            for (int j = 0; j < currentTetro.width; j++)
            {
                if (currentTetro.p[i][j] != "*")
                    updateMap(coord_x + i, coord_y + j, currentTetro.color, "◼");
            }
        Sleep(300);
    }
    score -= 10;
    delete_score();
    print_score();
    gotoxy(x_offset + 2 * m - 2 * number_of_spoil + 12, 3);
    cout << "🦆";
    ++number_of_spoil;
    if (number_of_spoil >= 5)
        lost_game();
    // Delete tetro
    printTetro("◼", true);
    // Delete guide
    printTetro("◼", true, guide_x);
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
    // Giving the score
    score += complete_lines.size() * m;
    delete_score();
    print_score();
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
                    updateMap(i - 1, j, "", "◼");
                    // Coloring
                    updateMap(i, j, p[i][j], "◼");
                }
            }
        }
}
void lost_game()
{
    PlaySound(TEXT("data/lost.wav"), NULL, SND_FILENAME | SND_ASYNC);
    system("cls");
    cout << "\u001b[38;5;196m";
    cout << "░██████╗░░█████╗░███╗░░░███╗███████╗  ░█████╗░██╗░░░██╗███████╗██████╗░\n";
    cout << "██╔════╝░██╔══██╗████╗░████║██╔════╝  ██╔══██╗██║░░░██║██╔════╝██╔══██╗\n";
    cout << "██║░░██╗░███████║██╔████╔██║█████╗░░  ██║░░██║╚██╗░██╔╝█████╗░░██████╔╝\n";
    cout << "██║░░╚██╗██╔══██║██║╚██╔╝██║██╔══╝░░  ██║░░██║░╚████╔╝░██╔══╝░░██╔══██╗\n";
    cout << "╚██████╔╝██║░░██║██║░╚═╝░██║███████╗  ╚█████╔╝░░╚██╔╝░░███████╗██║░░██║\n";
    cout << "░╚═════╝░╚═╝░░╚═╝╚═╝░░░░░╚═╝╚══════╝  ░╚════╝░░░░╚═╝░░░╚══════╝╚═╝░░╚═╝";
    cout << reset;
    update_leaderboard();
    getch();
    exit(0);
}
void updateTime()
{
    int period = static_cast<unsigned int>(time(nullptr)) - start_time + period2;
    int min = 0;
    int sec = period;
    while (period / 60 > 0)
    {
        ++min;
        period /= 60;
    }
    sec -= min * 60;
    gotoxy(x_offset + 2 * m + 3, 1);
    printf("%02d:%02d", min, sec);
}
void saveGame()
{

    fstream fs("data/savegame.txt", ios::out | ios::trunc);
    fs << name << " " << n << " " << m << " " << level << " " << period2 << " " << tetNum << " " << sleepTime << " " << score << " " << number_of_spoil << " " << static_cast<int>(inHold) << " " << coord_x << " " << coord_y << " " << static_cast<int>(isGuided) << " " << spoiler_x << " " << spoiler_y;
    fs << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            fs << p[i][j];
            if (j != m - 1)
                fs << " ";
        }
        fs << endl;
    }
    fs.close();
    fstream fs2("data/savetetro.txt", ios::out | ios::trunc);
    fs2 << currentTetro.height << " " << currentTetro.width << " " << currentTetro.color;
    fs2 << endl;
    for (int i = 0; i < currentTetro.height; i++)
    {
        for (int j = 0; j < currentTetro.width; j++)
        {
            fs2 << currentTetro.p[i][j];
            if (j != currentTetro.width - 1)
                fs2 << " ";
        }
        fs2 << endl;
    }
    fs2.close();
    // Pending
    fstream fs3("data/savepending.txt", ios::out | ios::trunc);
    fs3 << pendingTetro.height << " " << pendingTetro.width << " " << pendingTetro.color;
    fs3 << endl;
    for (int i = 0; i < currentTetro.height; i++)
    {
        for (int j = 0; j < currentTetro.width; j++)
        {
            fs3 << currentTetro.p[i][j];
            if (j != currentTetro.width - 1)
                fs3 << " ";
        }
        fs3 << endl;
    }
    fs3.close();
}
int main()
{
    SetConsoleOutputCP(CP_UTF8);
    hideCursor();
main_menu_disp:
    // Main menu
    int result = main_menu(1);
    // Exit
    if (result == 4)
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
        }
        cout << reset;
        exit(0);
    }
    // Leaderboard
    else if (result == 3)
    {
        result = level_menu(1);
        if (result == 0)
            goto main_menu_disp;
        else
            leader_board(result);
        goto main_menu_disp;
    }
    else
    {
        // Defining Tetrominos (:
        // 0 Straight (attracted to members of the opposite sex)
        Tetromino tet_straight;
        tet_straight.p = new string *[1];
        tet_straight.p[0] = new string[4];
        tet_straight.height = 1;
        tet_straight.width = 4;
        for (int i = 0; i < 4; i++)
            tet_straight.p[0][i] = "1";
        // 1 Square
        Tetromino tet_square;
        tet_square.p = new string *[2];
        tet_square.p[0] = new string[2];
        tet_square.p[1] = new string[2];
        tet_square.height = 2;
        tet_square.width = 2;
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                tet_square.p[i][j] = "1";
        // 2 T
        Tetromino tet_t;
        tet_t.p = new string *[2];
        for (int i = 0; i < 2; i++)
            tet_t.p[i] = new string[3];
        tet_t.height = 2;
        tet_t.width = 3;
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
        tet_l.width = 2;
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
        tet_skew.width = 3;
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 3; j++)
                tet_skew.p[i][j] = "1";
        tet_skew.p[0][0] = "*";
        tet_skew.p[1][2] = "*";
        // 5 Skew(2)
        Tetromino tet_skew_2;
        tet_skew_2.p = new string *[2];
        for (int i = 0; i < 3; i++)
            tet_skew_2.p[i] = new string[3];
        tet_skew_2.height = 2;
        tet_skew_2.width = 3;
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 3; j++)
                tet_skew_2.p[i][j] = "1";
        tet_skew_2.p[0][2] = "*";
        tet_skew_2.p[1][0] = "*";
        // 6 L(2)
        Tetromino tet_l_2;
        tet_l_2.p = new string *[3];
        for (int i = 0; i < 3; i++)
            tet_l_2.p[i] = new string[2];
        tet_l_2.height = 3;
        tet_l_2.width = 2;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 2; j++)
                tet_l_2.p[i][j] = "1";
        tet_l_2.p[0][0] = "*";
        tet_l_2.p[1][0] = "*";
        tetromino[0] = &tet_straight;
        tetromino[1] = &tet_square;
        tetromino[2] = &tet_t;
        tetromino[3] = &tet_l;
        tetromino[4] = &tet_skew;
        tetromino[5] = &tet_skew_2;
        tetromino[6] = &tet_l_2;
        system("cls");
        GetConsoleScreenBufferInfo(hConsole, &buffer_info);
        int columns = buffer_info.srWindow.Right - buffer_info.srWindow.Left + 1;
        int rows = buffer_info.srWindow.Bottom - buffer_info.srWindow.Top + 1;
        x_offset = (columns - (2 * m + 14)) / 2;
        y_offset = 5;
        if (result == 1)
        {
            ifstream ifs("data/savegame.txt");
            string line;
            vector<string> lines;
            while (getline(ifs, line))
            {
                lines.push_back(line);
            }
            ifs.close();
            for (int i = 0; i <= lines.size() - 1; i++)
            {
                vector<string> elements;
                istringstream iss(lines[i]);
                string elem;
                while (getline(iss, elem, ' '))
                {
                    elements.push_back(elem);
                }
                if (i == 0)
                {
                    name = elements[0];
                    n = stoi(elements[1]);
                    m = stoi(elements[2]);
                    level = stoi(elements[3]);
                    period2 = stoi(elements[4]);
                    tetNum = stoi(elements[5]);
                    sleepTime = stoi(elements[6]);
                    score = stoi(elements[7]);
                    number_of_spoil = stoi(elements[8]);
                    inHold = stoi(elements[9]);
                    coord_x = stoi(elements[10]);
                    coord_y = stoi(elements[11]);
                    isGuided = stoi(elements[12]);
                    spoiler_x = stoi(elements[13]);
                    spoiler_y = stoi(elements[14]);
                    p = new string *[n];
                    for (int ii = 0; ii < n; ii++)
                    {
                        p[ii] = new string[m];
                        for (int j = 0; j < m; j++)
                            p[ii][j] = "*";
                    }
                }
                else
                {
                    for (int j = 0; j < m; j++)
                        p[i - 1][j] = elements[j];
                }
            }
            lines.clear();
            lines.shrink_to_fit();
            ifstream ifs2("data/savetetro.txt");
            while (getline(ifs2, line))
            {
                lines.push_back(line);
            }
            ifs2.close();
            for (int i = 0; i < lines.size(); i++)
            {
                vector<string> elements;
                istringstream iss(lines[i]);
                string elem;
                while (getline(iss, elem, ' '))
                {
                    elements.push_back(elem);
                }
                if (i == 0)
                {
                    currentTetro.height = stoi(elements[0]);
                    currentTetro.width = stoi(elements[1]);
                    currentTetro.color = elements[2];
                    currentTetro.p = new string *[currentTetro.height];
                    for (int k = 0; k < currentTetro.height; k++)
                        currentTetro.p[k] = new string[currentTetro.width];
                }
                else
                {
                    for (int j = 0; j < currentTetro.width; j++)
                        currentTetro.p[i - 1][j] = elements[j];
                }
            }
        }
        if (result == 2)
        {
            result = level_menu(1);
            if (result == 0)
                goto main_menu_disp;
            else if (result == 1)
                sleepTime = 650;
            else if (result == 2)
                sleepTime = 450;
            else if (result == 3)
            {
                sleepTime = 100;
                isGuided = false;
            }
            level = result;
            system("cls");
            showCursor();
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            int columns = buffer_info.srWindow.Right - buffer_info.srWindow.Left + 1;
            int rows = buffer_info.srWindow.Bottom - buffer_info.srWindow.Top + 1;
            // Ask name
            gotoxy(columns / 2 - 5, 2);
            cout << "\u001b[38;5;196m";
            cout << "Wʜᴀᴛ's ʏᴏᴜʀ ɴᴀᴍᴇ ᴍᴀᴛᴇ?" << reset;
            gotoxy(columns / 2 + 2, 3);
            cin >> name;
            system("cls");
            gotoxy(columns / 2 - 10, 2);
            cout << "\u001b[38;5;196m";
            cout << "Gɪᴠᴇ ᴍᴇ ᴅɪᴍᴇɴᴛɪᴏɴs: " << reset;
            gotoxy(columns / 2 - 3, 3);
            cin >> n >> m;
            while (n < 5 || m < 5)
            {
                GetConsoleScreenBufferInfo(hConsole, &buffer_info);
                int columns = buffer_info.srWindow.Right - buffer_info.srWindow.Left + 1;
                int rows = buffer_info.srWindow.Bottom - buffer_info.srWindow.Top + 1;
                gotoxy(columns / 2 - 10, 2);
                cout << "\u001b[38;5;196m";
                cout << "Gɪᴠᴇ ᴍᴇ ᴅɪᴍᴇɴᴛɪᴏɴs: " << reset;
                gotoxy(columns / 2 - 3, 3);
                cin >> n >> m;
            }
            hideCursor();
            p = new string *[n];
            for (int i = 0; i < n; i++)
            {
                p[i] = new string[m];
                for (int j = 0; j < m; j++)
                    p[i][j] = "*";
            }
            system("cls");
            // Generating first pending tetro
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> distrib(1, 100);
            int randNum = distrib(gen);
            // tetNum = randNum % 7;
            tetNum = 1;
            string color = "\u001b[38;5;" + to_string((randNum % 16) + 120) + "m";
            pendingTetro = *tetromino[tetNum];
            pendingTetro.color = color;
        }
        GetConsoleScreenBufferInfo(hConsole, &buffer_info);
        columns = buffer_info.srWindow.Right - buffer_info.srWindow.Left + 1;
        rows = buffer_info.srWindow.Bottom - buffer_info.srWindow.Top + 1;
        x_offset = (columns - (2 * m + 14)) / 2;
        y_offset = 5;
        initialPrint(p);
        addSpoiler(p);
        // Printing boarders
        // Main boarder
        printBoarder(x_offset, y_offset, 2 * m + 1, n);
        // Hold Boarder
        gotoxy(2 * m + 8 + x_offset, y_offset);
        cout << "Hᴏʟᴅ";
        printBoarder(2 * m + 4 + x_offset, y_offset + 1, 10, 4);
        gotoxy(2 * m + 7 + x_offset, y_offset + 7);
        cout << "Pᴇɴᴅɪɴɢ";
        // Pending Boarder
        printBoarder(2 * m + 4 + x_offset, 6 + y_offset + 2, 10, 4);
        // Status Boarder
        printBoarder(x_offset, 0, 2 * m + 14, 3);
        gotoxy(x_offset + 1, 1);
        cout << "Nᴀᴍᴇ: " << name;
        gotoxy(x_offset + 1, 3);
        cout << "Sᴄᴏʀᴇ: " << score;
        gotoxy(x_offset, y_offset + n + 2);
        cout << "[Esp]:Menu";
        if (level == 1)
        {
            gotoxy(x_offset + 2 * m + 10, 1);
            cout << "\u001b[48;5;48m"
                 << "Easy" << reset;
        }
        else if (level == 2)
        {
            gotoxy(x_offset + 2 * m + 8, 1);
            cout << "\u001b[48;5;220m"
                 << "Medium" << reset;
        }
        else
        {
            gotoxy(x_offset + 2 * m + 10, 1);
            cout << "\u001b[48;5;196m"
                 << "Hard" << reset;
        }
        gotoxy(x_offset + 2 * m, 1);
        cout << "⏱";
        bool game_continue = true;
        int input;
        int count_move = 0;
        start_time = static_cast<unsigned int>(time(nullptr));
        // Stop sound
        PlaySound(NULL, NULL, 0);
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
            Sleep(sleepTime);
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
                    // Down
                    if (input == 80)
                        down(p);
                    if (kbhit() && count_move < 1)
                    {
                        goto getinput;
                        ++count_move;
                    }
                    else
                        count_move = 0;
                }
                else
                {
                    // Hold
                    if (input == 119 && !inHold)
                        hold_tet(p);
                    // Left
                    if (input == 97)
                        goLeft(p);
                    // Down
                    if (input == 115)
                        down(p);
                    // Right
                    if (input == 100)
                        goRight(p);
                    // Space
                    if (input == 32)
                    {
                        fitDown(p);
                    }
                    // Hold
                    if (input == 104 && !inHold)
                        hold_tet(p);
                    if (input == 122)
                        rotateLeft(p);
                    // Ingame menu
                    if (input == 27)
                    {
                        PlaySound(TEXT("data/Gravity2.wav"), NULL, SND_FILENAME | SND_ASYNC);
                        period2 += static_cast<unsigned int>(time(nullptr)) - start_time;
                        result = ingameMenu();
                        // Continue
                        if (result == 1)
                        {
                            PlaySound(NULL, NULL, 0);
                            initialPrint(p);
                            printTetro("◼");
                            printGuide(p);
                            updateMap(spoiler_x, spoiler_y, "", "🦆");
                            start_time = static_cast<unsigned int>(time(nullptr));
                        }
                        // Restart
                        if (result == 2)
                        {
                            gotoxy(0, 0);
                            score = 0;
                            inHold = false;
                            number_of_spoil = 0;
                            period2 = 0;
                            start_time = static_cast<unsigned int>(time(nullptr));
                            for (int i = 0; i < n; i++)
                                for (int j = 0; j < m; j++)
                                    p[i][j] = "*";
                            // Delete pending
                            delete_outside_tetro(2 * m + 4, 8);
                            // Delete hold
                            delete_outside_tetro(2 * m + 4, 1);
                            delete_score();
                            print_score();
                            initialPrint(p);
                            spawn(p);
                            addSpoiler(p);
                        }
                        // Save and quit
                        if (result == 3)
                        {
                            saveGame();
                            goto main_menu_disp;
                        }
                    }
                }
            }
            wentDown = goDown(p);
            // Time...
            updateTime();
        }
        // GameOver
        period2 += (static_cast<unsigned int>(time(nullptr)) - start_time);
        update_leaderboard();
        lost_game();
        // cout << "done";
    }
}
