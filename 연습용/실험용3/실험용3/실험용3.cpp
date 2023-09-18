#include <iostream>
#include <string>

using namespace std;
#define ESC 27

int main() {
    cout << "202007025 김지민 2주차 과제" << endl;

    while (true) {
        string command;

        cout << "command>";
        getline(cin, command);
        char cmd = command[0];

        if (cmd == ESC) {
            break;
        }
        if (cmd == 'q') {
            cout << "qwer 화이팅" << endl;
        }
        else if (cmd == 'w') {
            cout << "과제 너무 좋다" << endl;
        }
        else if (cmd == 'e') {
            cout << "담주부턴 과제량 3배다" << endl;
        }
        else if (cmd == 'r') {
            cout << "행복합니다." << endl;
        }

        else {
            cout << "오류: 올바른 명령어를 입력하세요." << endl;
        }
    }

    return 0;
}