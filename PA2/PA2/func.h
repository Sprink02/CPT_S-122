/*
Author: Johnathan Emanuelli
Date: 1/31/2026
Class: CPT_S 122
Assignment: PA2
Task: Header file that contains function prototypes to complete PA1
*/
#pragma once
#ifndef FUNC_H
#define FUNC_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

typedef struct
{
	int seconds;
	int minutes;
}DURATION;

typedef struct
{
	char artist[50];
	char album[50];
	char song[50];
	char genre[50];
	DURATION songLength;
	int numPlayed;
	int rating;
}RECORD;

typedef struct node
{
	RECORD record;
	struct node* prevNode;
	struct node* nextNode;
}NODE;

void load(NODE** pList, FILE* input);
void store(NODE* pList);
void display(NODE** pList);
//void insert();
//void delete();
void edit(NODE** pList);
//void sort();
void rate(NODE** pList);
void play(NODE** pList);
//void shuffle();
void exitProgram(NODE* pList);


DURATION strtodur(char cell[50]);
int add_node_front(NODE** pList, RECORD newSong);
NODE* create_node(RECORD newSong);
int menu();
int comma_check(char cell[50]);
void print_record(NODE* node);
void free_list(NODE** pList);

#endif // FUNC_H