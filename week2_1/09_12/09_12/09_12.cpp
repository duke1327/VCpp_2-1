#include <iostream>
#include <conio.h>
using namespace std;
#define ESC 27

int main()
{
    char c;
    cout << "     202007025\n";
    cout << "     김지민님의\n";
    cout << "     Application\n";   

    while (1) {
        c = _getch();
        if (c == ESC) {
            break;
        }

        cout << "command>";

        if (c == 'p') {
            cout << " p\n";
            cout << "나는 과제를 겁나 잘하는 학생이다.\n";
        }
        else if (c == 'f') {
            cout << " f\n";
            cout << "나는 과제가 너무 즐겁다.\n";
        }
        else if (c == 'j') {
            cout << " j\n";
            cout << "교수님 과제 더 내주세요.\n";
        }
        else {
            cout << "\n다시 입력해주세요.\n";
        }
    }

    return 0;
}