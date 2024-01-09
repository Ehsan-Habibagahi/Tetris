#include <iostream>
#include <windows.h>
#include <conio.h>
#include <algorithm>
#include <vector>
using namespace std;
int main()
{
    // char ch;
    // while(ch !='/')
    // {
    // Sleep(1000);
    // ch = getch();
    // cout<<endl<<ch;
    // }
    //////////////////////////////
    // HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // COORD pos = {10, 0};
    // system("cls");
    // CONSOLE_SCREEN_BUFFER_INFO inf;
    // SetConsoleCursorPosition(hConsole, pos);
    // GetConsoleScreenBufferInfo(hConsole,&inf);
    // int x = inf.dwCursorPosition.X;
    // // WriteConsole(hConsole, "Hello", 5, NULL, NULL);
    // cout<<"Hi";
    // cout<<x; 
    // GetConsoleScreenBufferInfo(hConsole,&inf);
    //  x = inf.dwCursorPosition.X;
    // cout<<x;
    // getch();
    //\u001b[48;5;162m
    cout<<"\u001b[38;5;80m"<<"hey"<<endl;
    cout<<"\u001b[0m";
    // for(int i =0;i<=100;i++)
    // {
    //     Sleep(50);
    //     cout<<"\u001b[1000D"<<i<<"%";
    //     // cout.flush();
    // }
    ////////////////////////////////////////////////////////
    // cout<<"  ◼ \n◼ ◼ ◼ ◼ ◼ ◼\n⛶ ⛶ ⛶ ⛶ ⛶ ⛶";
    // cout<<"\n ";
    // cout<<"\u001b[0m"<<endl;
    // char ch;
    // while(true)
    // {
    // Sleep(5000);
    // if(kbhit())
    // cout<<getch();
    // else
    // {
    //     cout<<"No key hit!";
    // break;
    // }
    // }
int a[3] = {0,1,2};
int *point = find(begin(a),end(a),32);
if(point == end(a))
cout<<"no";
else
cout<<"yes";
    vector<vector <string>> v = {{"X","0"},{"01","0"}};
    v.clear();
    // v = {{"01"}};
    cout<<v[0][0]<<endl<<v.size();
    cout<<"⬛️▪️◾️";

}