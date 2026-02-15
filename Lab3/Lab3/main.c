#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	struct node* pPrev; // this lab is now using two links
} Node;


Node* makeNode(Contact data)
{
	Node* pNew = (Node*)malloc(sizeof(Node));
	if (pNew != NULL)
	{
		pNew->data = data;
		pNew->pNext = NULL;
		pNew->pPrev = NULL;
	}
	return pNew;
}

Boolean insertContactAtFront(Node** pList, Contact newData)
{

	Node* pNew = makeNode(newData);
	if (pNew == NULL)
	{
		return FALSE;
	}
	if (*pList == NULL)
	{
		*pList = pNew;
	}
	else
	{
		pNew->pNext = *pList;
		(*pList)->pPrev = pNew;
		*pList = pNew;
	}
	return TRUE;
}

Boolean deleteContact(Node** pList, Contact searchContact)
{
	Node* pCur = *pList;
	while (pCur != NULL)
	{
		if (strcmp(pCur->data.name, searchContact.name) == 0)
		{
			// found it
			if (pCur->pPrev != NULL) pCur->pPrev->pNext = pCur->pNext;
			else *pList = pCur->pNext;
			if (pCur->pNext != NULL) pCur->pNext->pPrev = pCur->pPrev;
			free(pCur);
			return TRUE;
		}
		pCur = pCur->pNext;
	}
	return FALSE; // not found
}

Boolean editContact(Node* pList, Contact searchContact)
{
	Node* pCur = pList;
	while (pCur != NULL)
	{
		if (strcmp(pCur->data.name, searchContact.name) == 0)
		{
			// found it
			printf("Enter new phone: ");
			scanf("%11s", pCur->data.phone);
			printf("Enter new email: ");
			scanf("%49s", pCur->data.email);
			printf("Enter new title: ");
			scanf("%19s", pCur->data.title);
			return TRUE;
		}
		pCur = pCur->pNext;
	}
	return FALSE; // not found
}

Boolean loadContacts(FILE* infile, Node** pList)
{
	Contact temp;
	char line[500] = { 0 };
	char token[50] = { 0 };
	char c = 0;
	while (!feof(infile))
	{
		fgets(line, 500, infile);
		int j = 0;
		int i = 0;
		int index = 0;
		while (c != '\n')
		{
			switch (c)
			{
			case '\n': continue; break;
			case ',':
				token[i] = 0;
				switch (index)
				{
				case 0: strcpy(, token)break;
				case 1: break;
				case 2: break;
				case 3: break;
				}
			default: token[i] = line[j];
			}
			j++;
			i++;
		}
	}
	return TRUE;
}


