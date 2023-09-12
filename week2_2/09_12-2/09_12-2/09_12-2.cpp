#include <iostream>
#include <conio.h>
using namespace std;
#define ESC 27

int main()
{
    char c;
    cout << "202007025 김지민 2주차 과제 \n\n";

    while (1) {
        c = _getch();
        if (c == ESC) {
            break;
        }

        cout << "command>";

        if (c == 'q') {
            cout << " q\n";
            cout << "qwer 화이팅!\n";
        }
        else if (c == 'w') {
            cout << " w\n";
            cout << "과제 너무 좋다.\n";
        }
        else if (c == 'e') {
            cout << " e\n";
            cout << "담주부턴 과제량 3배다.\n";
        }
        else if (c == 'r') {
            cout << " r\n";
            cout << "행복합니다.\n";
        }
        else {
            cout << " 다시 입력해주세요.\n";
        }
    }

    return 0;
}