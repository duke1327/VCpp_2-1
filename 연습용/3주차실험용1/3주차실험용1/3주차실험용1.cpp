#include <iostream>
#include <chrono>
#include <thread>

int main() {
    using namespace std;
    using namespace std::chrono;

    int i = 0;
    // 대기할 시간 설정 (300ms)
    milliseconds waitTime(300);

    while (i < 3) {
        cout << "300ms 동안 입력을 기다립니다..." << std::endl;

        // 300ms 동안 대기
        this_thread::sleep_for(waitTime);

        // 입력 받기
        string input;
        cout << "입력을 기다립니다: ";
        cin >> input;

        // 입력 출력
        cout << "입력된 값: " << input << std::endl;
        i++;
    }

    return 0;

}