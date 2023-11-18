#pragma once
#include <iostream>
using namespace std;

class y_stack {
public:
	y_stack();
	~y_stack();

	void push(int num);
	int pop();

private:
	struct Node {
		int data;
		Node* next;
	};

	Node* top;

	bool emptyFlag;
};