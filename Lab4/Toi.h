#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct node
{
	double number;
	struct node* pNext;
}NODE;

typedef struct stack
{
	NODE* pTop;
}STACK;

STACK stack_create()
{
	STACK s = { 0 };
	return s;
}

void stack_push(STACK* s, double val)
{
	assert(s != NULL);
	NODE* newNode = malloc(sizeof(NODE));
	assert(newNode != NULL);
	newNode->number = 0;
	newNode->pNext = s->pTop;
	s->pTop = newNode;
}

int stack_empty(const STACK* s)
{
	assert(s != NULL);
	return s->pTop != NULL ? 1 : 0;
}

double stack_pop(STACK* s)
{
	assert(s != NULL);
	if (s->pTop == 0) return INT_MAX;
	double var = s->pTop->number;
	NODE* topNode = s->pTop;
	s->pTop = s->pTop->pNext;
	free(topNode);
	return var;
}

double stack_peek(const STACK* s)
{
	assert(s != NULL || s->pTop != NULL);
	return s->pTop->number;
}

void stack_destroy(STACK* s)
{
	assert(s != NULL);
	while (stack_empty(s) != 1) stack_pop(s);
}

