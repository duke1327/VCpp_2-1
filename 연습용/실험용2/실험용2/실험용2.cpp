#include <iostream>
using namespace std;

char PrintCommand(void) {
    char test[100] = { 0, };
    cout << "command>";
    cin.getline(test, 100);
    if (test[1] == '\n') {
        return test[0];
    }
    else {
        cout << "올바른 커맨드를 입력하세요" << endl;
        return 0;
    }
}

int main() {
    cout << "202007025 김지민 2주차 과제" << endl;

    while (true) {
        char cmd = PrintCommand();

        if (cmd == 27) {  // 27은 ESC 키의 ASCII 코드입니다.
            cout << "프로그램을 종료합니다." << endl;
            break; // 프로그램 종료
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
