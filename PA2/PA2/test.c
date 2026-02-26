#include "test.h"

void insert_test()
{
	char arr[7][49] = { "Perry, Katy","Witness","Chained to the Rhythm","pop","4:36","-1","5" };
	NODE* pHead = NULL;
	insert(&pHead, arr);
}

void delete_test()
{
	NODE* pHead = NULL;
	RECORD newRecord = { 0 };
	DURATION time = { 0 };
	time.minutes = 4;
	time.seconds = 36;
	strcpy(newRecord.artist, "Perry, Katy");
	strcpy(newRecord.album, "Witness");
	strcpy(newRecord.song, "Chained to the Rhythm");
	strcpy(newRecord.genre, "pop");
	newRecord.songLength = time;
	newRecord.numPlayed = 3;
	newRecord.rating = 5;
	add_node_front(&pHead, newRecord);

	char str[49] = "Chained to the Rhythm";
	delete_song(&pHead, str);
	//should see it in console if deleted
}

void shuffle_test()
{
	char arr1[7][49] = { "A1","Witness","Song 1","pop","4:36","-1","5" };
	char arr2[7][49] = { "A2","Witness","Song 2","pop","4:36","-1","5" };
	char arr3[7][49] = { "A3","Witness","Song 3","pop","4:36","-1","5" };
	int order[3] = { 0,2,1 }; //Goes to end then backwords; so 3-0 = 3; 3-2 = 1; 3-1 = 2 >> {3,1,2} order for the test
	NODE* pHead = NULL;
	insert(&pHead, arr1);
	insert(&pHead, arr2);
	insert(&pHead, arr3);
	shuffle(&pHead, order);
}

void main_test()
{
	system("cls");
	int tmp = -1;
	while (tmp != 0)
	{
		printf("pick test:\n(1)Insert\n(2)Delete\n(3)Shuffle\n(0)Exit\n");
		if (scanf("%d", &tmp) != 1) //Fixing scanf being bad
		{
			while (getchar() != '\n');
			tmp = -1;
		}
		switch (tmp) 
		{
		case 1: insert_test(); break;
		case 2: delete_test(); break;
		case 3: shuffle_test(); break;
		case 0: return; break;	
		default: system("cls"); break;
		}
	}
}