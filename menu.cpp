#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cwchar>
#include "header.h"
using namespace std;
void goDownLine(int tetris_offset)
{
    GetConsoleScreenBufferInfo(hConsole, &buffer_info);
    gotoxy(tetris_offset, buffer_info.dwCursorPosition.Y + 1);
}
int main_menu(int choice)
{
    int input = -1;
    while (input != 13)
    {
        system("cls");
        GetConsoleScreenBufferInfo(hConsole, &buffer_info);
        int columns = buffer_info.srWindow.Right - buffer_info.srWindow.Left + 1;
        int rows = buffer_info.srWindow.Bottom - buffer_info.srWindow.Top + 1;
        int tetris_offset = (columns - 45) / 2;
        // goDownLine(tetris_offset);
        // GetConsoleScreenBufferInfo(hConsole, &buffer_info);
        gotoxy(tetris_offset, rows / 4);
        cout << "\u001b[38;5;48m";
        cout << "████████╗███████╗████████╗██████╗░██╗░██████╗";
        goDownLine(tetris_offset);
        cout << "╚══██╔══╝██╔════╝╚══██╔══╝██╔══██╗██║██╔════╝";
        goDownLine(tetris_offset);
        cout << "░░░██║░░░█████╗░░░░░██║░░░██████╔╝██║╚█████╗░";
        goDownLine(tetris_offset);
        cout << "░░░██║░░░██╔══╝░░░░░██║░░░██╔══██╗██║░╚═══██╗";
        goDownLine(tetris_offset);
        cout << "░░░██║░░░███████╗░░░██║░░░██║░░██║██║██████╔╝";
        goDownLine(tetris_offset);
        cout << "░░░╚═╝░░░╚══════╝░░░╚═╝░░░╚═╝░░╚═╝╚═╝╚═════╝░";
        cout << reset;
        // Printing boarder
        gotoxy(0, 0);
        cout << "╔";
        for (int i = 1; i <= columns - 2; i++)
            cout << "═";
        cout << "╗";
        for (int j = 1; j <= rows - 2; j++)
        {
            gotoxy(0, j);
            cout << "║";
            gotoxy(columns - 1, j);
            cout << "║";
        }
        gotoxy(0, rows - 1);
        cout << "╚";
        for (int i = 1; i <= columns - 2; i++)
            cout << "═";
        cout << "╝";
        // Ptrinting buttons;
        int x_buttons = (columns - 20) / 2;
        // int y_buttons = (rows - 12 - 6) / 2; // 5 for 3 buttons
        int y_buttons = (rows / 2);
        if (choice == 1)
        {
            gotoxy(x_buttons, y_buttons);
            cout << "\u001b[38;5;196m";
            cout << "╒══════════════════╕";
            gotoxy(x_buttons - 2, y_buttons + 1);
            cout << "➤ │";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(buffer_info.dwCursorPosition.X + 5, buffer_info.dwCursorPosition.Y);
            cout << "Nᴇᴡ Gᴀᴍᴇ";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(buffer_info.dwCursorPosition.X + 5, buffer_info.dwCursorPosition.Y);
            cout << "│";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(x_buttons, buffer_info.dwCursorPosition.Y + 1);
            cout << "╘══════════════════╛";
            cout << reset;

            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(x_buttons, buffer_info.dwCursorPosition.Y + 2);
            cout << "╒══════════════════╕";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(x_buttons, buffer_info.dwCursorPosition.Y + 1);
            cout << "│";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(buffer_info.dwCursorPosition.X + 4, buffer_info.dwCursorPosition.Y);
            cout << "LᴇᴀᴅᴇʀBᴏᴀʀᴅ";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(buffer_info.dwCursorPosition.X + 3, buffer_info.dwCursorPosition.Y);
            cout << "│";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(x_buttons, buffer_info.dwCursorPosition.Y + 1);
            cout << "╘══════════════════╛";

            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(x_buttons, buffer_info.dwCursorPosition.Y + 2);
            cout << "╒══════════════════╕";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(x_buttons, buffer_info.dwCursorPosition.Y + 1);
            cout << "│";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(buffer_info.dwCursorPosition.X + 7, buffer_info.dwCursorPosition.Y);
            cout << "Exɪᴛ";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(buffer_info.dwCursorPosition.X + 7, buffer_info.dwCursorPosition.Y);
            cout << "│";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(x_buttons, buffer_info.dwCursorPosition.Y + 1);
            cout << "╘══════════════════╛";
        }
        else if (choice == 2)
        {
            gotoxy(x_buttons, y_buttons);
            cout << "╒══════════════════╕";
            gotoxy(x_buttons, y_buttons + 1);
            cout << "│";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(buffer_info.dwCursorPosition.X + 5, buffer_info.dwCursorPosition.Y);
            cout << "Nᴇᴡ Gᴀᴍᴇ";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(buffer_info.dwCursorPosition.X + 5, buffer_info.dwCursorPosition.Y);
            cout << "│";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(x_buttons, buffer_info.dwCursorPosition.Y + 1);
            cout << "╘══════════════════╛";

            cout << "\u001b[38;5;196m";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(x_buttons, buffer_info.dwCursorPosition.Y + 2);
            cout << "╒══════════════════╕";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(x_buttons - 2, buffer_info.dwCursorPosition.Y + 1);
            cout << "➤ │";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(buffer_info.dwCursorPosition.X + 4, buffer_info.dwCursorPosition.Y);
            cout << "LᴇᴀᴅᴇʀBᴏᴀʀᴅ";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(buffer_info.dwCursorPosition.X + 3, buffer_info.dwCursorPosition.Y);
            cout << "│";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(x_buttons, buffer_info.dwCursorPosition.Y + 1);
            cout << "╘══════════════════╛";
            cout << reset;

            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(x_buttons, buffer_info.dwCursorPosition.Y + 2);
            cout << "╒══════════════════╕";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(x_buttons, buffer_info.dwCursorPosition.Y + 1);
            cout << "│";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(buffer_info.dwCursorPosition.X + 7, buffer_info.dwCursorPosition.Y);
            cout << "Exɪᴛ";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(buffer_info.dwCursorPosition.X + 7, buffer_info.dwCursorPosition.Y);
            cout << "│";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(x_buttons, buffer_info.dwCursorPosition.Y + 1);
            cout << "╘══════════════════╛";
        }
        else if (choice == 3)
        {
            gotoxy(x_buttons, y_buttons);
            cout << "╒══════════════════╕";
            gotoxy(x_buttons, y_buttons + 1);
            cout << "│";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(buffer_info.dwCursorPosition.X + 5, buffer_info.dwCursorPosition.Y);
            cout << "Nᴇᴡ Gᴀᴍᴇ";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(buffer_info.dwCursorPosition.X + 5, buffer_info.dwCursorPosition.Y);
            cout << "│";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(x_buttons, buffer_info.dwCursorPosition.Y + 1);
            cout << "╘══════════════════╛";

            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(x_buttons, buffer_info.dwCursorPosition.Y + 2);
            cout << "╒══════════════════╕";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(x_buttons, buffer_info.dwCursorPosition.Y + 1);
            cout << "│";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(buffer_info.dwCursorPosition.X + 4, buffer_info.dwCursorPosition.Y);
            cout << "LᴇᴀᴅᴇʀBᴏᴀʀᴅ";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(buffer_info.dwCursorPosition.X + 3, buffer_info.dwCursorPosition.Y);
            cout << "│";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(x_buttons, buffer_info.dwCursorPosition.Y + 1);
            cout << "╘══════════════════╛";

            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(x_buttons, buffer_info.dwCursorPosition.Y + 2);
            cout << "\u001b[38;5;196m";
            cout << "╒══════════════════╕";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(x_buttons - 2, buffer_info.dwCursorPosition.Y + 1);
            cout << "➤ │";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(buffer_info.dwCursorPosition.X + 7, buffer_info.dwCursorPosition.Y);
            cout << "Exɪᴛ";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(buffer_info.dwCursorPosition.X + 7, buffer_info.dwCursorPosition.Y);
            cout << "│";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(x_buttons, buffer_info.dwCursorPosition.Y + 1);
            cout << "╘══════════════════╛";
            cout << reset;
        }
        input = getch();
        // To handle special keys(arrows)
        if (input == 224 || input == 0)
        {
            input = getch();
            if (input == 80)
                ++choice;
            else if (input == 72)
                --choice;

            if (choice == 0)
                choice = 3;
            if (choice == 4)
                choice = 1;
        }
    }
    // Stop song
    // if (choice == 1)
    // PlaySound(NULL, NULL, 0);
    return choice;
}
int level_menu(int choice)
{
    int input = -1;
    while (input != 13)
    {
        system("cls");
        GetConsoleScreenBufferInfo(hConsole, &buffer_info);
        int columns = buffer_info.srWindow.Right - buffer_info.srWindow.Left + 1;
        int rows = buffer_info.srWindow.Bottom - buffer_info.srWindow.Top + 1;
        int tetris_offset = (columns - 23) / 2;
        // Ptrinting this beauty
        gotoxy(tetris_offset, rows / 4);
        cout << "\u001b[38;5;199m";
        cout << "▒█░░░ █▀▀ ▀█░█▀ █▀▀ █░░";
        goDownLine(tetris_offset);
        cout << "▒█░░░ █▀▀ ░█▄█░ █▀▀ █░░";
        goDownLine(tetris_offset);
        cout << "▒█▄▄█ ▀▀▀ ░░▀░░ ▀▀▀ ▀▀▀" << reset;
        int x_buttons = (columns - 20) / 2;
        int y_buttons = (rows / 2);
        // Buttons (:
        if (choice == 1)
        {
            gotoxy(x_buttons, y_buttons);
            cout << "\u001b[38;5;48m";
            cout << "╒══════════════════╕";
            gotoxy(x_buttons - 2, y_buttons + 1);
            cout << "➤ │";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(buffer_info.dwCursorPosition.X + 3, buffer_info.dwCursorPosition.Y);
            cout << "Pɪᴇᴄᴇ ᴏғ ᴄᴀᴋᴇ";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(buffer_info.dwCursorPosition.X + 2, buffer_info.dwCursorPosition.Y);
            cout << "│";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(x_buttons, buffer_info.dwCursorPosition.Y + 1);
            cout << "╘══════════════════╛";
            cout << reset;

            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(x_buttons, buffer_info.dwCursorPosition.Y + 2);
            cout << "╒══════════════════╕";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(x_buttons, buffer_info.dwCursorPosition.Y + 1);
            cout << "│";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(buffer_info.dwCursorPosition.X + 6, buffer_info.dwCursorPosition.Y);
            cout << "ᴍᴇᴅɪᴜᴍ";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(buffer_info.dwCursorPosition.X + 6, buffer_info.dwCursorPosition.Y);
            cout << "│";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(x_buttons, buffer_info.dwCursorPosition.Y + 1);
            cout << "╘══════════════════╛";

            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(x_buttons, buffer_info.dwCursorPosition.Y + 2);
            cout << "╒══════════════════╕";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(x_buttons, buffer_info.dwCursorPosition.Y + 1);
            cout << "│";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(buffer_info.dwCursorPosition.X + 2, buffer_info.dwCursorPosition.Y);
            cout << "Hᴀʀᴅ(Iʀᴀɴ ᴍᴏᴅᴇ)";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(buffer_info.dwCursorPosition.X + 1, buffer_info.dwCursorPosition.Y);
            cout << "│";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(x_buttons, buffer_info.dwCursorPosition.Y + 1);
            cout << "╘══════════════════╛";
        }
        else if (choice == 2)
        {
            gotoxy(x_buttons, y_buttons);
            cout << "╒══════════════════╕";
            gotoxy(x_buttons, y_buttons + 1);
            cout << "│";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(buffer_info.dwCursorPosition.X + 3, buffer_info.dwCursorPosition.Y);
            cout << "Pɪᴇᴄᴇ ᴏғ ᴄᴀᴋᴇ";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(buffer_info.dwCursorPosition.X + 2, buffer_info.dwCursorPosition.Y);
            cout << "│";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(x_buttons, buffer_info.dwCursorPosition.Y + 1);
            cout << "╘══════════════════╛";

            cout << "\u001b[38;5;220m";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(x_buttons, buffer_info.dwCursorPosition.Y + 2);
            cout << "╒══════════════════╕";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(x_buttons - 2, buffer_info.dwCursorPosition.Y + 1);
            cout << "➤ │";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(buffer_info.dwCursorPosition.X + 6, buffer_info.dwCursorPosition.Y);
            cout << "ᴍᴇᴅɪᴜᴍ";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(buffer_info.dwCursorPosition.X + 6, buffer_info.dwCursorPosition.Y);
            cout << "│";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(x_buttons, buffer_info.dwCursorPosition.Y + 1);
            cout << "╘══════════════════╛";
            cout << reset;

            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(x_buttons, buffer_info.dwCursorPosition.Y + 2);
            cout << "╒══════════════════╕";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(x_buttons, buffer_info.dwCursorPosition.Y + 1);
            cout << "│";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(buffer_info.dwCursorPosition.X + 2, buffer_info.dwCursorPosition.Y);
            cout << "Hᴀʀᴅ(Iʀᴀɴ ᴍᴏᴅᴇ)";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(buffer_info.dwCursorPosition.X + 1, buffer_info.dwCursorPosition.Y);
            cout << "│";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(x_buttons, buffer_info.dwCursorPosition.Y + 1);
            cout << "╘══════════════════╛";
        }
        else if (choice == 3)
        {
            gotoxy(x_buttons, y_buttons);
            cout << "╒══════════════════╕";
            gotoxy(x_buttons, y_buttons + 1);
            cout << "│";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(buffer_info.dwCursorPosition.X + 3, buffer_info.dwCursorPosition.Y);
            cout << "Pɪᴇᴄᴇ ᴏғ ᴄᴀᴋᴇ";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(buffer_info.dwCursorPosition.X + 2, buffer_info.dwCursorPosition.Y);
            cout << "│";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(x_buttons, buffer_info.dwCursorPosition.Y + 1);
            cout << "╘══════════════════╛";

            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(x_buttons, buffer_info.dwCursorPosition.Y + 2);
            cout << "╒══════════════════╕";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(x_buttons, buffer_info.dwCursorPosition.Y + 1);
            cout << "│";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(buffer_info.dwCursorPosition.X + 6, buffer_info.dwCursorPosition.Y);
            cout << "ᴍᴇᴅɪᴜᴍ";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(buffer_info.dwCursorPosition.X + 6, buffer_info.dwCursorPosition.Y);
            cout << "│";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(x_buttons, buffer_info.dwCursorPosition.Y + 1);
            cout << "╘══════════════════╛";

            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(x_buttons, buffer_info.dwCursorPosition.Y + 2);
            cout << "\u001b[38;5;196m";
            cout << "╒══════════════════╕";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(x_buttons - 2, buffer_info.dwCursorPosition.Y + 1);
            cout << "➤ │";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(buffer_info.dwCursorPosition.X + 2, buffer_info.dwCursorPosition.Y);
            cout << "Hᴀʀᴅ(Iʀᴀɴ ᴍᴏᴅᴇ)";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(buffer_info.dwCursorPosition.X + 1, buffer_info.dwCursorPosition.Y);
            cout << "│";
            GetConsoleScreenBufferInfo(hConsole, &buffer_info);
            gotoxy(x_buttons, buffer_info.dwCursorPosition.Y + 1);
            cout << "╘══════════════════╛";
            cout << reset;
        }
        gotoxy(0, rows - 1);
        cout << "[B]:Back";
        input = getch();
        // To handle special keys(arrows)
        if (input == 224 || input == 0)
        {
            input = getch();
            if (input == 80)
                ++choice;
            else if (input == 72)
                --choice;

            if (choice == 0)
                choice = 3;
            if (choice == 4)
                choice = 1;
        }
        if (input == 98)
            return 0;
    }
    return choice;
}
int ingameMenu()
{
    for (int i = 1; i <= 2 * m + 1; i++)
        for (int j = 1; j <= n; j++)
        {
            gotoxy(x_offset + i, y_offset + j);
            cout << " ";
        }
    // C0ntinue
    gotoxy(x_offset + (2 * m + 1) / 2 - 16, y_offset + n / 3);
    cout << "▄█ ░ █▀▀ █▀█ █▄░█ ▀█▀ █ █▄░█ █░█ █▀▀";
    gotoxy(x_offset + (2 * m + 1) / 2 - 16, y_offset + n / 3 + 1);
    cout << "░█ ▄ █▄▄ █▄█ █░▀█ ░█░ █ █░▀█ █▄█ ██▄";
    // Restart
    gotoxy(x_offset + (2 * m + 1) / 2 - 12, y_offset + n / 3 + 4);
    cout << "▀█ ░ █▀█ █▀▀ █▀ ▀█▀ ▄▀█ █▀█ ▀█▀";
    gotoxy(x_offset + (2 * m + 1) / 2 - 12, y_offset + n / 3 + 5);
    cout << "█▄ ▄ █▀▄ ██▄ ▄█ ░█░ █▀█ █▀▄ ░█░";
    // Save & quit
    gotoxy(x_offset + (2 * m + 1) / 2 - 12, y_offset + n / 3 + 8);
    cout << "█▀ ▄▀█ █░█ █▀▀ ▄▄ █▀█ █░█ █ ▀█▀";
    gotoxy(x_offset + (2 * m + 1) / 2 - 12, y_offset + n / 3 + 9);
    cout << "▄█ █▀█ ▀▄▀ ██▄ ░░ ▀▀█ █▄█ █ ░█░";
    while (1)
    {
        int input = getch();
        if (input == 49 || input == 27)
            return 1;
        if (input == 50)
            return 2;
        if(input == 51)
            return 3;
    }
}