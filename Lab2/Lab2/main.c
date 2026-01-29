#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

typedef enum boolean
{
	FALSE, TRUE
} Boolean;
typedef struct contact
{
	char name[50];
	char phone[12]; // 18005557577
	char email[50];
	char title[20];
} Contact;
typedef struct node
{
	Contact data;
	struct node* pNext;
} Node;

Node* createNode(Contact newData)
{
	Node* node = malloc(sizeof(Node));
	if (node == NULL) return NULL;

	node->data = newData;  node->pNext = NULL;
	return node;
}

Boolean insertContactInOrder(Node** pList, Contact newData)
{
	Node* newNode = createNode(newData);
	if (pList == NULL || newNode == NULL) return FALSE;

	for (; *pList != NULL && strcmp(newData.name, (*pList)->data.name); pList = &((*pList)->pNext));

	newNode->pNext = *pList;
	*pList = newNode;
	return TRUE;
}

Boolean deleteContact(Node** pList, Contact searchContact)
{
	Node* prevNode = NULL;
	for (; *pList != NULL && (strcmp(searchContact.name, (*pList)->data.name) != 0); pList = &((*pList)->pNext))
	{
		prevNode = pList;
	}
	if (*pList == NULL) return FALSE;

	prevNode->pNext = (*pList)->pNext;
	free(*pList);
	return TRUE;
}

Boolean editContact(Node* pList, Contact searchContact)
{
	Node* prevNode = NULL;
	for (; pList != NULL && (strcmp(searchContact.name, (pList)->data.name) != 0); pList = &((pList)->pNext))
	{
		prevNode = pList;
	}
	if (pList == NULL) return FALSE;

	pList->data = searchContact;
	return TRUE;
}

void printList(Node* pList)
{
	printf("Name\tPhone\tEmail\tTitle:\n\n");
	for (; pList != NULL; pList = &((pList)->pNext))
	{
		printf("%s",pList->data.name);
		printf("%s", pList->data.phone);
		printf("%s", pList->data.email);
		printf("%s", pList->data.title);
	}
}

void reverseLinkedList(Node** pList)
{
	Node* headPtr = *pList;
	Node* prevNode = NULL;
	Node* prevprevNode = NULL;
	while (pList != NULL)
	{
		if (prevprevNode != NULL)
		{
			//Do actual reversing
			prevNode->pNext = prevprevNode;
		}
		prevprevNode = prevNode;
		prevNode = *pList; (*pList)->pNext = NULL;
		pList = &((*pList)->pNext);
	}
	(*pList)->pNext = prevprevNode;
	pList = prevNode;

}