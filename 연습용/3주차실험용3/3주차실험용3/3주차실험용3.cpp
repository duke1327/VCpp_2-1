#include <iostream>
#include <string>
#include <conio.h>
#include <chrono>
#include <Windows.h>

//앞에 붙는 거 없게 설정
using namespace std;
using namespace std::chrono;

int main()
{ 
    while (1) {
        system_clock::time_point timer;
        string str = "";

        if (_kbhit()) {
            if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) { // esc키가 눌릴 시 바로 종료
                return 0;
            }
            if (GetAsyncKeyState(VK_DOWN )) { //아래쪽키 입력시 문자열에 ↓ 추가
                str += "↓";
            }
            if (GetAsyncKeyState(VK_UP)) { //위쪽키 입력시 문자열에 ↑ 추가
                str += "↑";
            }
            if (GetAsyncKeyState(VK_RIGHT)) { //오른쪽키 입력시 문자열에 → 추가
                str += "→";
            }
            if (GetAsyncKeyState(VK_LEFT)) { //왼쪽키 입력시 문자열에 ← 추가
                str += "←";
            }

            if (GetAsyncKeyState(0x41)) {
                str += "a";
            }
            if (GetAsyncKeyState(0x53)) {
                str += "s";
            }

            if (duration_cast<milliseconds>(system_clock::now() - timer).count() >= 300) { // 입력 후 0.3초가 지날시
                if (str.find("↓→a") != string::npos) { // 해당 커맨드 조사 맞으면 아래 내용 출력
                    cout << "↓→a" << endl;
                    cout << "아도겐! =o" << endl;
                    Sleep(1000); // 해당 커맨드 출력 후 쉬는 시간
                }else if (str.find("→↑s") != string::npos) { // 얘는 계속 안 나옴
                    cout << "→↑s" << endl;
                    cout << "소류겐!" << endl;
                    Sleep(2000); 
                }
            }
        }
    }
}
