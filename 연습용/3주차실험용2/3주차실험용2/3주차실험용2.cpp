#include <iostream>
#include <string>	//string::find()

using namespace std;

int main() {
	string s;

	cout << "문자 입력 : ";
	cin >> s;

	//rich 문자 유무 판단
	if (s.find("rich") != string::npos) {
		cout << "찾는 문자가 존재합니다" << endl;

		int index = s.find("rich");   //해당 문자의 시작 인덱스 반환

		cout << index;
	}
}