#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <conio.h>
#include "header.h"
using namespace std;
string address[3] = {"data/easy.txt", "data/medium.txt", "data/hard.txt"};
struct Player
{
    string name;
    int score;
    int time;
    int n;
    int m;
    int spoil;
};
void bubbleSort(int arr[], int n)
{
    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++)
    {
        swapped = false;
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (swapped == false)
            break;
    }
}
void update_leaderboard()
{
    fstream fs(address[level - 1], ios::out | ios::app);
    fs << name << " " << score << " " << number_of_spoil << " " << n << " " << m;
    fs.close();
    ifstream ifs(address[level - 1]);
    string line;
    vector<string> lines;
    while (getline(ifs, line))
    {
        lines.push_back(line);
    }
    ifs.close();
    lines[0] = to_string(stoi(lines[0]) + 1);
    ofstream ofs(address[level - 1]);
    for (int i = 0; i < lines.size(); i++)
        ofs << lines[i] << endl;
    ofs.close();
}
void leader_board(int level)
{
    ifstream ifs(address[level - 1]);
    string line;
    vector<string> lines;
    while (getline(ifs, line))
    {
        lines.push_back(line);
    }
    ifs.close();
    Player player[lines.size() - 1];
    for (int i = 0; i < lines.size() - 1; i++)
    {
        vector<string> elements;
        istringstream iss(lines[i + 1]);
        string elem;
        while (getline(iss, elem, ' '))
        {
            elements.push_back(elem);
        }
        player[i].name = elements[0];
        player[i].spoil = stoi(elements[2]);
        player[i].score = stoi(elements[1]);
        player[i].n =stoi( elements[3]);
        player[i].m =stoi( elements[4]);
        player[i].time = stoi(elements[5]);
    }
       int i, j;
    bool swapped;
    for (i = 0; i < line.size() - 1; i++)
    {
        swapped = false;
        for (j = 0; j < lines.size() - i - 2; j++)
        {
            if (player[j].score < player[j + 1].score || (player[j].score == player[j+1].score && player[j].time>player[j+1].time))
            {
                swap(player[j], player[j + 1]);
                swapped = true;
            }
        }
        if (swapped == false)
            break;
    }
    system("cls");
    GetConsoleScreenBufferInfo(hConsole, &buffer_info);
    int columns = buffer_info.srWindow.Right - buffer_info.srWindow.Left + 1;
    int rows = buffer_info.srWindow.Bottom - buffer_info.srWindow.Top + 1;
    int leader_board_offset = (columns - 43) / 2;
    gotoxy(leader_board_offset, 0);
    cout << "█░░ █▀▀ ▄▀█ █▀▄ █▀▀ █▀█ █▄▄ █▀█ ▄▀█ █▀█ █▀▄";
    goDownLine(leader_board_offset);
    cout << "█▄▄ ██▄ █▀█ █▄▀ ██▄ █▀▄ █▄█ █▄█ █▀█ █▀▄ █▄▀";
    gotoxy(0, 3);
    cout << "Tᴏᴛᴀʟ ᴘʟᴀʏᴇʀs: " << lines[0];
    switch (level)
    {
    case 1:
        gotoxy(columns - 4, 3);
        cout << "\u001b[48;5;48m"
             << "Easy" << reset;
        break;
    case 2:
        gotoxy(columns - 6, 3);
        cout << "\u001b[48;5;220m"
             << "Medium" << reset;
        break;
    case 3:
        gotoxy(columns - 4, 3);
        cout << "\u001b[48;5;196m"
             << "Hard" << reset;
        break;
    default:
        break;
    }
    int col_offset = (columns - 33) / 6;
    // Green color
    cout << "\u001b[38;5;49m";
    gotoxy(0, 5);
    cout << "No.";
    gotoxy(col_offset, 5);
    cout << "Nᴀᴍᴇ";
    gotoxy(2 * col_offset + 4, 5);
    cout << "Sᴄᴏʀᴇ";
    gotoxy(3 * col_offset + 9, 5);
    cout << "Tɪᴍᴇ";
    gotoxy(4 * col_offset + 13, 5);
    cout << "Dɪᴍᴇɴᴛɪᴏɴ";
    gotoxy(5 * col_offset + 22, 5);
    cout << "Sᴘᴏɪʟ";
    gotoxy(6 * col_offset + 27, 5);
    cout << "Sᴛᴀᴛᴜs" << reset;
     i = 1;
    for (; i < lines.size(); i++)
    {
        // vector<string> elements;
        // istringstream iss(lines[i]);
        // string elem;
        // while (getline(iss, elem, ' '))
        // {
        //     elements.push_back(elem);
        // }
        int color = 159 + i;
        gotoxy(0, 5 + i);
        cout << "\u001b[38;5;" << color << "m"
             << "[" << i << "].";
        //Name
        gotoxy(col_offset - 1, 5 + i);
        cout << player[i-1].name;
        //Score
        gotoxy(2 * col_offset + 5, 5 + i);
        cout << player[i-1].score;
        //Dimention
        gotoxy(4 * col_offset + 15, 5 + i);
        cout << player[i-1].n << "*" << player[i-1].m;
        //Spoiler
        gotoxy(5 * col_offset + 22, 5 + i);
        for (int ii = 1; ii <= player[i-1].spoil; ii++)
            cout << "🖕";
        
        //Status
        gotoxy(6 * col_offset + 27, 5 + i);
        if ((player[i-1].spoil) >= 5)
            cout << "F-lost";
        else
        {
            gotoxy(6 * col_offset + 24, 5 + i);
            cout << "Tetris-lost";
        }
        //Time
        gotoxy(3 * col_offset + 9, 5 + i);
        int min = 0;
        int sec = (player[i-1].time);
        while (sec / 60 > 0)
        {
            ++min;
            sec /= 60;
        }
        sec = (player[i-1].time) - min * 60;
        printf("%02d:%02d", min, sec);
        if (i == 10)
            break;
    }
    cout << reset;
    gotoxy(0, 6 + i);
    cout << "[B]: Back";
    while (1)
    {
        if (getch() == 'b')
            return;
    }
}