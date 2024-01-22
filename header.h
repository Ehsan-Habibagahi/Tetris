#include <windows.h>
#include<string>
int main_menu(int choice);
void gotoxy(int x, int y);
extern CONSOLE_SCREEN_BUFFER_INFO buffer_info;
extern HANDLE hConsole;
extern const std::string reset;