/*
Author: Johnathan Emanuelli
Date: 1/22/2026
Class: CPT_S 122
Assignment: PA1
Task: Main program that cleanses and outputs results from fitbit.csv data
*/

#include "func.h"

int main()
{
	FitbitData dataArr[1440] = { 0 };
	FILE* inputstream = fopen("FitbitData.csv", "r");
	FILE* outputstream = fopen("Results.csv", "w");
	if (inputstream == NULL)
	{
		printf("Could not read FitbitData.csv\n");
		return 1;
	}
	if (outputstream == NULL)
	{
		printf("Could not write Results.csv\n");
		return 1;
	}

	char patientString[50] = { 0 };
	char headers[8][100] = { 0 };

	getPatient(patientString, inputstream);
	readHeaders(headers, inputstream);
	parseRecord(dataArr, patientString, inputstream, outputstream);

	float totalCal = 0, distance = 0, floors = 0, steps = 0, heartSum = 0, heartRate = 0;
	int heartNum = 0, stepsMax = 0, poorSleepLength = 0, poorSleepLength_t = 0, pSToggle = 0;
	char poorSleepStart[9] = { 0 };
	char poorSleepStart_t[9] = { 0 };
	char poorSleepEnd[9] = { 0 };


	for (int i = 0; i < 1440; i++)
	{
		totalCal += dataArr[i].calories;
		distance += dataArr[i].distance;
		floors += dataArr[i].floors;
		steps += dataArr[i].steps;
		if (!(dataArr[i].heartRate == (unsigned int)-1))
		{
			heartSum += dataArr[i].heartRate;
			heartNum++;
		}
		if (stepsMax < dataArr[i].steps)
		{
			stepsMax = dataArr[i].steps;
		}
		if (dataArr[i].sleepLevel > 1) //Start of length
		{
			if (pSToggle == 0)
			{
				strcpy(poorSleepStart_t, dataArr[i].minute);
				pSToggle = 1;
			}
			poorSleepLength_t += dataArr[i].sleepLevel;
		}
		else //At end of length
		{
			if (poorSleepLength_t > poorSleepLength) //Check poorSleep
			{
				strcpy(poorSleepStart, poorSleepStart_t);
				strcpy(poorSleepEnd, dataArr[i - 1].minute);
				poorSleepLength = poorSleepLength_t;
			}
			if (pSToggle == 1) //Reset always
			{
				pSToggle = 0;
				poorSleepLength_t = 0;
				strcpy(poorSleepStart_t, "");
			}
		}
	}

	//printf("\nStart of PoorSleep:%s\nEnd of PoorSleep:%s", poorSleepStart, poorSleepEnd);
	heartRate = heartSum / heartNum;

	printCSV(outputstream, dataArr, totalCal, distance, floors, steps, heartRate, stepsMax, poorSleepStart, poorSleepEnd, headers);



	fclose(outputstream);
	fclose(inputstream);
	return 0;
}
