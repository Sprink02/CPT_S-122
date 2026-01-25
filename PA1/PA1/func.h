/*
Author: Johnathan Emanuelli
Date: 1/22/2026
Class: CPT_S 122
Assignment: PA1
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

typedef enum sleep
{
	NONE = 0, ASLEEP = 1, AWAKE = 2, REALLYAWAKE = 3
} Sleep;

typedef struct fitbit
{
	char patient[10];
	char minute[9];
	double calories;
	double distance;
	unsigned int floors;
	unsigned int heartRate;
	unsigned int steps;
	Sleep sleepLevel;
} FitbitData;


void getPatient(char* patientString, FILE* inputstream);
void readHeaders(char** headers, FILE* inputstream);
void parseRecord(FitbitData dataArr[1440], const char* patientString, FILE* inputstream, FILE* outputstream);
int timeToInt(char time[9]);
void printCSV(FILE* outputstream, FitbitData dataArr[1440], float calories, float distance, float floors, float steps, float heartrate, float stepsMax, char poorSleepStart[9], char poorSleepEnd[9], char headers[8][100]);

#endif // FUNC_H