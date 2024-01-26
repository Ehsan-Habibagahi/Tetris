#include <windows.h>
#include<string>
int main_menu(int choice);
void gotoxy(int x, int y);
int level_menu(int choice);
int ingameMenu();
void printBoarder(int x, int y, int w, int h);
void update_leaderboard();
void leader_board(int level);
void goDownLine(int tetris_offset);
extern CONSOLE_SCREEN_BUFFER_INFO buffer_info;
extern HANDLE hConsole;
extern int x_offset;
extern int y_offset;
extern int m;
extern int n;
extern int level;
extern int period2;
extern std::string name;
extern int score;
extern int number_of_spoil;
extern const std::string reset;