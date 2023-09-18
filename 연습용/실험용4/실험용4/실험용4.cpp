#include <iostream>
#include <conio.h>
using namespace std;
#define ESC 27
#define ENTER 13

int main()
{
    char c;
    char t[100]{ 0, };
    int i = 0;
    cout << "202007025 김지민 2주차 과제 \n\n";

    while (1) {
        for (int j = 0; j < 100; j++) {
            t[j] = 0;
        }

        cout << "command>";
        i = 0;

        while (1) {
            c = _getch();

            if (c == ESC) {
                return 0;
            }
            else if (c == ENTER) {
                cout << endl;
                break;
            }
            else {
                cout << c;
                t[i] = c;
                i++;
            }
        }

        if (i == 1) {
            if (t[0] == 'q') {
                cout << "qwer 화이팅!" << endl;
            }
            else if (t[0] == 'w') {
                cout << "과제 너무 좋다." << endl;
            }
            else if (t[0] == 'e') {
                cout << "담주부턴 과제량 3배다." << endl;
            }
            else if (t[0] == 'r') {
                cout << "행복합니다." << endl;
            }
            else {
                cout << "다시 입력해주세요." << endl;
            }
        }
        else {
            cout << "다시 입력해주세요." << endl;
        }
    }
    return 0;
}