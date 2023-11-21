#include "stack.h"

struct Data* Top;

void push(struct Data* data) {
	data->prevData = Top;
	Top = data;
}

struct Data* pop() {
	struct Data* result = Top;
	Top = result->prevData;

	return result;
}