#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct node
{
	struct node* pNext;
}NODE;

int isLoop(NODE* list)
{
	NODE* p1 = list;
	NODE* p2 = list;
	while (p2->pNext != NULL && p1->pNext != NULL)
	{
		p1 = p1->pNext;
		p2 = p2->pNext->pNext;
		if (p1 == p2) return 1;
	}
	return 0; //No loop
}

NODE* create_node(void)
{
	NODE* newNode = malloc(sizeof(NODE));
	if (newNode == NULL) return NULL;

	//init
	newNode->pNext = NULL;
	return newNode;
}

int add_node_front(NODE** pList)
{
	int success = 0;
	NODE* newNode = create_node();
	if (newNode == NULL) return 0;

	if ((*pList) != NULL) //Only do if there is 1 node in a list
	{
		newNode->pNext = *pList; //newNode next -> head pointer
	}

	*pList = newNode; //head pointer move to newNode
	success = 1;
	return success;
}

void makeLoop(NODE* list)
{
	NODE* pCur = list;
	if (pCur == NULL) {return; }
	while (pCur->pNext != NULL)
	{
		pCur = pCur->pNext;
	}
	pCur->pNext = list;

}

void makeLoop2(NODE* list)
{
	NODE* pCur = list;
	if (pCur == NULL) { return; }
	while (pCur->pNext != NULL)
	{
		pCur = pCur->pNext;
	}
	pCur->pNext = list->pNext->pNext;

}

int main1()
{
	NODE* pHead = NULL;
	for (int i = 0; i < 3; i++)
	{
		add_node_front(&pHead);
	}
	//have 3 nodes in a LL
	makeLoop(pHead);
	if (isLoop(pHead) == 1)
	{
		printf("Found loop");
	}
	else
	{
		printf("No loop");
	}
	return 0;
}

int main2()
{
	NODE* pHead = NULL;
	for (int i = 0; i < 12; i++)
	{
		add_node_front(&pHead);
	}
	//have 3 nodes in a LL
	//makeLoop2(pHead);
	if (isLoop(pHead) == 1)
	{
		printf("Found loop");
	}
	else
	{
		printf("No loop");
	}
	return 0;
}