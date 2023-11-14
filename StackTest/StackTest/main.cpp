#include "StackTest.h"

int main() {
    y_stack stack;

    stack.push(1);
    stack.push(2);
    stack.push(3);

    cout << "Pop : " << stack.pop() << endl;
    cout << "Pop : " << stack.pop() << endl;
    cout << "Pop : " << stack.pop() << endl;

    return 0;
}