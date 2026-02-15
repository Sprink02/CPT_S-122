/*
Author: Johnathan Emanuelli
Date: 1/31/2026
Class: CPT_S 122
Assignment: PA2
Task: C file that contains function prototypes to complete PA2
*/
#include "func.h"

/*
Function: create_node
Date Created: 1/31/2026
Description: creates a single node
Input: Record to add
Returns: NODE* of new Node
PreCondition:  none
PostCondition: none
*/
NODE* create_node(RECORD newSong)
{
	NODE* newNode = malloc(sizeof(NODE));
	if (newNode == NULL) return NULL;

	//init
	newNode->record = newSong;
	newNode->prevNode = NULL; newNode->nextNode = NULL;
	return newNode;
}

/*
Function: add_node_front
Date Created: 1/31/2026
Description: creates a single node and adds it to the front of adoubly linked list
Input: pointer to headpointer, Record of what to add
Returns: success as 1, failure as 0
PreCondition:  none
PostCondition: none
*/
int add_node_front(NODE** pList, RECORD newSong)
{
	int success = 0;
	NODE* newNode = create_node(newSong);
	if (newNode == NULL) return 0;

	if ((*pList) != NULL) //Only do if there is 1 node in a list
	{
		(*pList)->prevNode = newNode; //Set oldNode's prev -> &newNode
		newNode->nextNode = *pList; //newNode next -> head pointer
	}

	*pList = newNode; //head pointer move to newNode
	success = 1;
	return success;
}

/*
Function: load
Date Created: 1/31/2026
Description: reads and stores csv data into d-linked list
Input: pointer to headpointer, inputstream
Returns: none
PreCondition:  inputstream exists and is open
PostCondition: none
*/
void load(NODE** pList, FILE* input)
{
	int c = 0;
	int quotes = 0;
	char cell[50] = { 0 };
	int i = 0;
	int rIndex = 0;
	/*
	typedef struct
	{
		char artist[50]; 0
		char album[50]; 1
		char song[50]; 2
		char genre[50]; 3
		DURATION songLength; 4
		int numPlayed; 5
		int rating; 6
	}RECORD;
	*/
	RECORD newRecord = { 0 };
	NODE* newNode = NULL;

	rewind(input); //
	while ((c = getc(input)) != EOF && !feof(input))
	{
		switch (c) {
		case ',': case '\n':
			if (quotes == 1) {
				cell[i] = c;
			}
			else {
				cell[i] = '\0';
				//handling putting Cell into Record
				switch (rIndex) {
				case 0: strcpy(newRecord.artist, cell); break;
				case 1: strcpy(newRecord.album, cell); break;
				case 2: strcpy(newRecord.song, cell); break;
				case 3: strcpy(newRecord.genre, cell); break;
				case 4: newRecord.songLength = strtodur(cell); break;
				case 5: newRecord.numPlayed = atoi(cell); break;
				case 6: newRecord.rating = atoi(cell); break;
				}
				rIndex++;
				i = -1;
			}
			if (c == '\n')
			{
				add_node_front(pList, newRecord);
				newRecord = (RECORD){ 0 };
				i = -1;
				rIndex = 0;
			}
			break;
		case '"':
			(quotes == 0) ? (quotes = 1) : (quotes = 0);
			i--;
			break;
		default:
			cell[i] = c;
			break;
		}
		i++;
	}
	system("cls");
	printf("loaded file\n");
	system("pause");
}

/*
Function: strtodur
Date Created: 1/31/2026
Description: converts string into DURATION struct
Input: string of size 50
Returns: none
PreCondition:  DURATION struct is defined well
PostCondition: none
*/
DURATION strtodur(char cell[50])
{
	int i = 0, j = 0;
	char min[3] = { 0 }; //limit of 99:99; if this is reached what file do you own?
	char sec[3] = { 0 };
	int sCol = 0; //seen Colon
	DURATION time = { 0 };
	while (cell[i] != NULL)
	{
		if (cell[i] == ':')
		{
			sCol = 1;
			j = -1;
		}
		else if (sCol == 0)
		{
			//Minutes
			min[j] = cell[i];
		}
		else
		{
			//seconds
			sec[j] = cell[i];
		}

		j++;  i++;
	}
	time.minutes = atoi(min); time.seconds = atoi(sec);
	return time;
}

/*
Function: store
Date Created: 2/1/2026
Description: Writes the contents of the doubly linked list to a CSV file.
Input: pointer to the head of the list, output stream
Returns: none
PreCondition: output stream is open for writing
PostCondition: none
*/
void store(NODE* pList)
{
	FILE* output = fopen("musicPlayList.csv", "w");
	NODE* pCur = pList;
	while (pCur != NULL)
	{
		RECORD r = pCur->record;

		// Array of pointers to the four string fields for easier looping
		char* fields[] = { r.artist, r.album, r.song, r.genre };

		for (int i = 0; i < 4; i++)
		{
			if (comma_check(fields[i]))
			{
				fprintf(output, "\"%s\",", fields[i]);
			}
			else
			{
				fprintf(output, "%s,", fields[i]);
			}
		}
		// %02d ensures seconds like 5 appear as 05
		fprintf(output, "%d:%02d,", r.songLength.minutes, r.songLength.seconds);
		fprintf(output, "%d,", r.numPlayed);
		fprintf(output, "%d\n", r.rating);

		pCur = pCur->nextNode;
	}

	fclose(output);
	system("cls");
	printf("Stored file\n");
	system("pause");
	return;
}

/*
Function: comma_check
Date Created: 2/1/2026
Description: returns a value if a comma is found withen a string
Input: string of size 50
Returns: 1 if found, 0 if not
PreCondition:  none
PostCondition: none
*/
int comma_check(char cell[50])
{
	for (int i = 0; i < 50; i++)
	{
		if (cell[i] == ',') return 1;
		if (cell[i] == '\0') return 0;
	}
	return 0;
}

/*
Function: display()
Date Created: 2/2/2026
Description: prints to console all records or matching records
Input: NODE** headpointer
Returns: none
PreCondition:  none
PostCondition: none
*/
void display(NODE** pList)
{
	int ans = 0;
	char str[50] = { 0 };
	do
	{
		system("cls");
		printf("Display:\n(1) Print all Records.\n(2) Print all that match an artist\n");
		scanf(" %d", &ans);
	} while (ans < 1 || ans > 2);
	if (ans == 2)
	{
		system("cls");
		printf("Display:\nArtist's Name (Case sensative)(Mars, Bruno):");
		//scanf(" %s", str);
		while (getchar() != '\n');
		fgets(str, 49, stdin);
		str[strcspn(str, "\n")] = '\0';
		system("cls");
		ans = 0;
		NODE* temp = *pList;
		while (temp != NULL)
		{
			if (strcmp(temp->record.artist, str) == 0)
			{
				print_record(temp);
				ans = 1;
			}
			temp = temp->nextNode;
		}
		if (ans == 0) { printf("No matching records\n"); system("pause"); return; }
	}
	else
	{
		NODE* temp = *pList;
		while (temp != NULL)
		{
			print_record(temp);
			temp = temp->nextNode;
		}
	}
	system("pause");
	return;
}

//Helper function for display and other printing record functions()
void print_record(NODE* node)
{
	printf("Artist: %s;  ", node->record.artist);
	printf("Album: %s;  ", node->record.album);
	printf("Song: %s;  ", node->record.song);
	printf("Genre: %s;  ", node->record.genre);
	printf("NumPlayed: %d;  ", node->record.numPlayed);
	printf("Rating: %d;  ", node->record.rating);
	printf("Song Length: %d:%02d\n\n", node->record.songLength.minutes, node->record.songLength.seconds);
}

/*
Function: insert()
Date Created: 2/9/2026
Description: prompts user for new record details and inserts at front of list
Input: NODE** headpointer
Returns: none
PreCondition: none
PostCondition: new record added to front of list
*/
void insert(NODE** pList, char arr[7][49])
{
	RECORD newRecord = { 0 };
	int min = 0, sec = 0, rating = 0;

	system("cls");
	printf("Insert New Record:\n\n");
	if (arr != NULL) //For testing
	{
		strcpy(newRecord.artist, arr[0]);
		strcpy(newRecord.album, arr[1]);
		strcpy(newRecord.song, arr[2]);
		strcpy(newRecord.genre, arr[3]);
		char* tok;
		tok = strtok(arr[4], ":");
		newRecord.songLength.minutes = min;
		tok = strtok(NULL, ":");
		newRecord.songLength.seconds = sec;

		newRecord.numPlayed = atoi(arr[5]);
		if (atoi(arr[6]) < 1 || atoi(arr[6]) > 5) printf("Rating bad; Test Failed");
		newRecord.rating = atoi(arr[6]);

		goto insert_test_goto; //Programming Taboo
	}

	// Clear input buffer
	while (getchar() != '\n');

	printf("Artist Name: ");
	fgets(newRecord.artist, 49, stdin);
	newRecord.artist[strcspn(newRecord.artist, "\n")] = '\0'; // Remove newline

	printf("Album Title: ");
	fgets(newRecord.album, 49, stdin);
	newRecord.album[strcspn(newRecord.album, "\n")] = '\0';

	printf("Song Title: ");
	fgets(newRecord.song, 49, stdin);
	newRecord.song[strcspn(newRecord.song, "\n")] = '\0';

	printf("Genre: ");
	fgets(newRecord.genre, 49, stdin);
	newRecord.genre[strcspn(newRecord.genre, "\n")] = '\0';

	int val = 0;
	do {
		printf("Song Length (1:06): ");
		val = scanf("%d:%d", &min, &sec);
		while (getchar() != '\n');
	} while (val == 0);
	newRecord.songLength.minutes = min;
	newRecord.songLength.seconds = sec;

	val = 0;
	do {
		printf("Number of Times Played: ");
		val = scanf("%d", &newRecord.numPlayed);
		while (getchar() != '\n');
	} while (val == 0);

	do {
		printf("Rating (1-5): ");
		val = scanf("%d", &rating);
		while (getchar() != '\n');
	} while (rating < 1 || rating > 5 || val == 0);
	newRecord.rating = rating;

insert_test_goto:
	// Insert at front of list
	if (add_node_front(pList, newRecord))
	{
		printf("\nRecord successfully added!\n");
	}
	else
	{
		printf("\nFailed to add record.\n");
	}

	system("pause");
	system("cls");
}

/*
Function: delete_song()
Date Created: 2/9/2026
Description: prompts for song title and removes matching record from list
Input: NODE** headpointer
Returns: none
PreCondition: none
PostCondition: matching record removed if found
*/
void delete_song(NODE** pList, const char* str)
{
	char songTitle[50] = { 0 };

	if (str == NULL)
	{
		system("cls");
		printf("Delete Record:\n\n");

		// Clear input buffer
		while (getchar() != '\n');

		printf("Enter Song Title to Delete: ");
		fgets(songTitle, 49, stdin);
		songTitle[strcspn(songTitle, "\n")] = '\0'; // Remove newline
	}
	else
	{
		strcpy(songTitle, str);
	}

	// Search for the song
	NODE* pCur = *pList;
	int found = 0;

	while (pCur != NULL)
	{
		if (strcmp(pCur->record.song, songTitle) == 0)
		{
			found = 1;

			// Case 1: Deleting the head node
			if (pCur == *pList)
			{
				*pList = pCur->nextNode;
				if (*pList != NULL)
				{
					(*pList)->prevNode = NULL;
				}
			}
			// Case 2: Deleting a middle or last node
			else
			{
				pCur->prevNode->nextNode = pCur->nextNode;
				if (pCur->nextNode != NULL)
				{
					pCur->nextNode->prevNode = pCur->prevNode;
				}
			}

			printf("\nDeleted: %s by %s\n", pCur->record.song, pCur->record.artist);
			free(pCur);
			break;
		}
		pCur = pCur->nextNode;
	}

	if (!found)
	{
		printf("\nSong '%s' not found in the playlist.\n", songTitle);
	}

	system("pause");
	system("cls");
}

/*
Function: edit()
Date Created: 2/2/2026
Description: prompts a search by artist and	allows editing of a records
Input: NODE ** headpointer
Returns: none
PreCondition:  none
PostCondition: none
*/
void edit(NODE** pList)
{
	int length = 0;
	char str[50] = { 0 };
	int ans = 0;

	system("cls");
	printf("Edit:\nArtist's Name (Case sensative)(Mars, Bruno):");
	//scanf(" %s", str);
	while (getchar() != '\n');
	fgets(str, 49, stdin);
	str[strcspn(str, "\n")] = '\0';
	system("cls");
	NODE* temp = *pList;
	while (temp != NULL)
	{
		if (strcmp(temp->record.artist, str) == 0)
		{
			printf("(%d) %s\n", length, temp->record.song);
			ans = 1;
			length++;
		}
		temp = temp->nextNode;
	}
	if (ans == 0) { printf("No matching records\n"); system("pause"); return; }

	do
	{
		printf("\nPick number of song to edit:"); scanf("%d", &ans);
	} while (ans < 0 || ans >= length);
	system("cls");

	//locating node specified
	length = length - ans - 1;
	temp = *pList;
	while (temp != NULL)
	{
		if (strcmp(temp->record.artist, str) == 0)
		{
			if (length == 0) break;
			length--;
		}
		temp = temp->nextNode;
	}

	//Find area to edit
	print_record(temp);
	//Get what where to edit
	ans = 0;
	do
	{
		printf("Pick field to edit:\n(1) Artist\n(2) Album\n(3) Song\n(4) Genre\n(5) Song length\n(6) Number Played\n(7) Rating\n\n");
		scanf(" %d", &ans);
	} while (ans < 1 || ans > 7);
	printf("\nChange to: ");
	while (getchar() != '\n');
	switch (ans)
	{
	case 1: fgets(temp->record.artist, 49, stdin);
		temp->record.artist[strcspn(temp->record.artist, "\n")] = '\0'; break;
	case 2: fgets(temp->record.album, 49, stdin);
		temp->record.album[strcspn(temp->record.album, "\n")] = '\0'; break;
	case 3: fgets(temp->record.song, 49, stdin);
		temp->record.song[strcspn(temp->record.song, "\n")] = '\0'; break;
	case 4: fgets(temp->record.genre, 49, stdin);
		temp->record.genre[strcspn(temp->record.genre, "\n")] = '\0'; break;
	case 5:
		printf("\nMin: ");
		ans = -1;
		do
		{
			scanf("%d", &ans);
		} while (ans < 0 || ans > 99);
		temp->record.songLength.minutes = ans;
		printf("\nSec: ");
		ans = -1;
		do
		{
			scanf("%d", &ans);
		} while (ans < 0 || ans > 59);
		temp->record.songLength.seconds = ans;
		break;
	case 6: scanf("%d", &temp->record.numPlayed); break;
	case 7:
		ans = 0;
		do
		{
			printf("New Rating:");
			scanf(" %d", &ans);
		} while (ans < 1 || ans > 5);
		temp->record.rating = ans;
		break;
	default: break;
	}
	system("pause");
	system("cls");
	return;
}

/*
Function: sort()
Date Created: 2/9/2026
Description: sorts the playlist based on user-selected criteria
Input: NODE** headpointer
Returns: none
PreCondition: none
PostCondition: list is sorted according to selected method
*/
void sort(NODE** pList)
{
	int choice = 0;

	if (*pList == NULL || (*pList)->nextNode == NULL)
	{
		system("cls");
		printf("Not enough records to sort.\n");
		system("pause");
		return;
	}

	system("cls");
	printf("Sort Options:\n");
	printf("(1) Sort by Artist (A-Z)\n");
	printf("(2) Sort by Album Title (A-Z)\n");
	printf("(3) Sort by Rating (1-5)\n");
	printf("(4) Sort by Times Played (Largest-Smallest)\n");
	printf("\nSelect sort method: ");
	scanf("%d", &choice);

	if (choice < 1 || choice > 4)
	{
		printf("Invalid choice.\n");
		system("pause");
		return;
	}

	// Bubble sort implementation
	int swapped;
	NODE* pCur;
	NODE* pLast = NULL;

	do
	{
		swapped = 0;
		pCur = *pList;

		while (pCur->nextNode != pLast)
		{
			int shouldSwap = 0;

			switch (choice)
			{
			case 1: // Sort by artist A-Z
				if (strcmp(pCur->record.artist, pCur->nextNode->record.artist) > 0)
					shouldSwap = 1;
				break;
			case 2: // Sort by album A-Z
				if (strcmp(pCur->record.album, pCur->nextNode->record.album) > 0)
					shouldSwap = 1;
				break;
			case 3: // Sort by rating 1-5
				if (pCur->record.rating > pCur->nextNode->record.rating)
					shouldSwap = 1;
				break;
			case 4: // Sort by times played (largest to smallest)
				if (pCur->record.numPlayed < pCur->nextNode->record.numPlayed)
					shouldSwap = 1;
				break;
			}

			if (shouldSwap)
			{
				// Swap the records
				RECORD temp = pCur->record;
				pCur->record = pCur->nextNode->record;
				pCur->nextNode->record = temp;
				swapped = 1;
			}

			pCur = pCur->nextNode;
		}
		pLast = pCur;
	} while (swapped);

	printf("\nPlaylist sorted successfully!\n");
	system("pause");
	system("cls");
}

/*
Function: rate()
Date Created: 2/2/2026
Description: prompts for a song and allows rating it
Input: NODE ** headpointer
Returns: none
PreCondition:  none
PostCondition: none
*/
void rate(NODE** pList)
{
	int length = 0;
	char str[50] = { 0 };
	int ans = 0;

	system("cls");
	printf("Edit:\nArtist's Name (Case sensative)(Mars, Bruno):");
	scanf(" %s", str);
	system("cls");
	NODE* temp = *pList;
	while (temp != NULL)
	{
		if (strcmp(temp->record.artist, str) == 0)
		{
			printf("(%d) %s\n", length, temp->record.song);
			ans = 1;
			length++;
		}
		temp = temp->nextNode;
	}
	if (ans == 0) { printf("No matching records\n"); system("pause"); return; }

	do
	{
		printf("\nPick number of song to edit:"); scanf("%d", &ans);
	} while (ans < 0 || ans >= length);
	system("cls");

	//locating node specified
	length = length - ans - 1;
	temp = *pList;
	while (temp != NULL)
	{
		if (strcmp(temp->record.artist, str) == 0)
		{
			if (length == 0) break;
			length--;
		}
		temp = temp->nextNode;
	}

	//Find area to edit
	print_record(temp);
	//Get what where to edit
	ans = 0;
	do
	{
		printf("New Rating:");
		scanf(" %d", &ans);
	} while (ans < 1 || ans > 5);
	temp->record.rating = ans;
	system("cls");
	return;
}

/*
Function: play()
Date Created: 2/2/2026
Description: "plays" all the songs
Input: NODE ** headpointer
Returns: none
PreCondition:  none
PostCondition: none
*/
void play(NODE** pList)
{
	NODE* temp = *pList;
	while (temp != NULL)
	{
		system("cls");
		print_record(temp);
		Sleep(1000);
		temp = temp->nextNode;
	}
	return;
}

/*
Function: shuffle()
Date Created: 2/9/2026
Description: plays songs in random order without modifying list structure
Input: NODE** headpointer
Returns: none
PreCondition: none
PostCondition: songs played in random order
*/
void shuffle(NODE** pList, const int* order)
{
	// Count the number of songs in the list
	int count = 0;
	NODE* pCur = *pList;
	while (pCur != NULL)
	{
		count++;
		pCur = pCur->nextNode;
	}

	if (count == 0)
	{
		system("cls");
		printf("No songs to shuffle.\n");
		system("pause");
		return;
	}

	// Create array to hold play order
	int* playOrder = (int*)malloc(count * sizeof(int));
	if (playOrder == NULL)
	{
		printf("Memory allocation failed.\n");
		return;
	}
	if (order == NULL) //For testing
	{
		// Initialize play order with sequential indices
		for (int i = 0; i < count; i++)
		{
			playOrder[i] = i;
		}
		//Actual Shuffling
		for (int i = count - 1; i > 0; i--)
		{
			int j = rand() % (i + 1);
			int temp = playOrder[i];
			playOrder[i] = playOrder[j];
			playOrder[j] = temp;
		}
	}
	else
	{
		for (int i = 0; i < count; i++)
		{
			playOrder[i] = order[i];
		}
	}
	
	for (int i = 0; i < count; i++) //actual playing
	{
		int position = playOrder[i];
		NODE* pTemp = *pList;

		// Navigate to the song at the specified position
		// Can move forward or backward depending on which is closer
		//TBH idk what this was for
		if (position < count / 2)
		{
			// Move forward from head
			for (int j = 0; j < position; j++)
			{
				pTemp = pTemp->nextNode;
			}
		}
		else
		{
			// Move to end first, then backward
			while (pTemp->nextNode != NULL)
			{
				pTemp = pTemp->nextNode;
			}
			for (int j = count - 1; j > position; j--)
			{
				pTemp = pTemp->prevNode;
			}
		}

		system("cls");
		printf("Now playing (shuffled %d/%d):\n\n", i + 1, count);
		print_record(pTemp);
		Sleep(1000);
	}

	free(playOrder);
	system("cls");
}

/*
Function: exit
Date Created: 2/2/2026
Description: "exits" the program, and overwrites the file
Input: none
Returns: none
PreCondition:  none
PostCondition: none
*/
void exitProgram(NODE* pList)
{
	store(pList);
	free_list(&pList);
}

/*
Function: menu
Date Created: 2/1/2026
Description: prints a menu to console for next action
Input: none
Returns: number of action desired
PreCondition:  none
PostCondition: none
*/
int menu()
{
	int input = 0;
	do
	{
		system("cls");
		printf("(1) load\n(2) store\n(3) display\n(4) insert\n(5) delete\n(6) edit\n(7) sort\n(8) rate\n(9) play\n(10) shuffle\n(11) exit\n(0) test\nSelect your next option: ");
		if (scanf("%d", &input) != 1) //Fixing scanf being bad
		{
			while (getchar() != '\n');
			input = -1;
		}
	} while (input < 0 || input > 11);

	return input;
}

//Helper function to free the entire Linked list, no matter size
void free_list(NODE** pList)
{
	NODE* pCur = *pList;
	while (pCur != NULL)
	{
		*pList = pCur->nextNode;
		free(pCur);
		pCur = *pList;
	}
}