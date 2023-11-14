#include "StackTest.h"

y_stack::y_stack() : top(nullptr) {}

y_stack::~y_stack() {
    while (top != nullptr) {
        Node* temp = top;
        top = top->next;
        delete temp;
    }
}

void y_stack::push(int num) {
    Node* newNode = new Node;
    newNode->data = num;
    newNode->next = top;
    top = newNode;
}

int y_stack::pop() {
    if (top == nullptr) {
        cout << "스택이 비었습니다!" << endl;
        return -1;
    }

    int num = top->data;
    Node* temp = top;
    top = top->next;
    delete temp;

    return num;
}