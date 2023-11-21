#include "stack.h"

int main() {
	struct Data* Content = (void*)0;
	Content = (struct Data*)malloc(sizeof(struct Data));
	Content->contentID = 1;

	push(Content);

	Content = (void*)0;

	Content = (struct Data*)malloc(sizeof(struct Data));
	Content->contentID = 2;

	push(Content);

	Content = pop();
	printf("Content ID : %d\n", Content->contentID);

	Content = pop();
	printf("Content ID : %d\n", Content->contentID);

	free(Content);

	return 0;
}