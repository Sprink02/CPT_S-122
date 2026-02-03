/*
Author: Johnathan Emanuelli
Date: 1/31/2026
Class: CPT_S 122
Assignment: PA2
Task: Main program that loads data from musicPlayList.csv and "plays" it
*/

#include "func.h"

int main()
{
	srand(time(NULL)); //set random for shuffle
	NODE* pHead = NULL;
	FILE* inputstream = fopen("musicPlayList.csv", "r");
	if (inputstream == NULL) { printf("failed to open musicPlayList.csv"); return 0; }

	int input = 0;
	while (input != 11)
	{
		input = menu();
		switch (input)
		{
		case 1: load(&pHead, inputstream); break;
		case 2: store(pHead); break;
		case 3: display(&pHead); break;
		case 4: printf("Insert not implemented\n"); system("pause"); break;
		case 5: printf("Delete not implemented\n"); system("pause"); break;
		case 6: edit(&pHead); break;
		case 7: printf("Sort not implemented\n"); system("pause"); break;
		case 8: printf("Rate not implemented\n"); system("pause"); break;
		case 9: play(&pHead); break;
		case 10: printf("Shuffle not implemented\n"); system("pause"); break;
		case 11: exitProgram(pHead); break;
		default: break;
		}
	}
	
	fclose(inputstream);
	return 0;
}