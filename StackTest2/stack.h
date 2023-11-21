#pragma once

#include <stdio.h>

struct Data {
	int contentID;

	int startCoordX;
	int startCoordY;

	int endCoordX;
	int endCoordY;

	struct Data* prevData;
};

void push(struct Data* data);

struct Data* pop();