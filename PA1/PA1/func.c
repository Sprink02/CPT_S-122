/*
Author: Johnathan Emanuelli
Date: 1/22/2026
Class: CPT_S 122
Assignment: PA1
Task: C file that contains function prototypes to complete PA1
*/
#include "func.h"

/*
Function: getPatient
Date Created: 1/22/2026
Description: Gets Patient id and moves inputstream pointer to start of 1st line
Input: where to store patient ID string, inputstream
Returns: Patient ID string
PreCondition:  none
PostCondition: none
*/
void getPatient(char* patientString, FILE* inputstream)
{
	char line[100] = { 0 };
	if (fgets(line, 100, inputstream) == NULL) {
		patientString[0] = '\0';
		return;
	}
	//printf("read 1st line: %s", line);

	char* token = strtok(line, ",");
	token = strtok(NULL, ",");

	if (token != NULL) {
		strcpy(patientString, token);
	}
	else {
		patientString[0] = '\0';
	}
	return;
}

/*
Function: readHeaders
Date Created: 1/22/2026
Description: Gets all headers from CSV and puts into a 2d char array
Input: 2d array to store header strings, inputstream
Returns: headers
PreCondition:  2d array is large enough for headers; 8 collumns for csv and 100 chars per header
PostCondition: none
*/
void readHeaders(char headers[8][100], FILE* inputstream)
{
	char line[100] = { 0 };
	if (fgets(line, 100, inputstream) == NULL) {
		return;
	}
	//printf("read headers: %s", line);

	char* token = strtok(line, ",");
	for (int i = 0; i < 8 && token != NULL; i++)
	{
		strcpy(headers[i], token);
		token = strtok(NULL, ",");
	}
	return;
}

/*
Function: parseRecord
Date Created: 1/22/2026
Description: parses a CSV record (row/line)
Input: dataArr to store, patient to filter, input and output streams
Returns: none
PreCondition:  dataArr is = 1440 records
PostCondition: none
*/
void parseRecord(FitbitData dataArr[1440], const char* patientString, FILE* inputstream, FILE* outputstream)
{
	int rowNum = 0; // row number that we are at for dupe checking

	while (!feof(inputstream) && rowNum < 1440)
	{
		char line[100] = { 0 };
		char patTemp[10] = { 0 };
		if (fgets(line, 100, inputstream) == NULL) {
			break;  // End of file or error
		}
		//printf("Row(%d)\t\tread line: %s", rowNum, line);

		int timeNum = 0;
		char cell[50] = { 0 };
		int startIndex = 0;
		int validRecord = 1;  // Track if this record should be saved

		for (int i = 0; i < 8; i++)
		{
			// Clear cell buffer for each field
			memset(cell, 0, sizeof(cell));
			int endIndex = 0;

			// Extract characters until delimiter
			while (line[startIndex + endIndex] != ',' &&
				line[startIndex + endIndex] != '\n' &&
				line[startIndex + endIndex] != '\r' &&
				line[startIndex + endIndex] != '\0')
			{
				if (endIndex < 49) {  // Prevent buffer overflow
					cell[endIndex] = line[startIndex + endIndex];
				}
				endIndex++;
			}
			cell[endIndex < 50 ? endIndex : 49] = '\0';  // Null terminate safely

			// Move startIndex past the delimiter
			startIndex = startIndex + endIndex + 1;

			// Happens once per line - filter based on Patient
			if (i == 0 && strcmp(patientString, cell) != 0) {
				//printf("Wrong Patient\n");
				validRecord = 0; rowNum--;
				break;
			}
			//Dedupe
			
			if (i == 1)
			{
				timeNum = timeToInt(cell);
			}

			if (strcmp(cell,"") == 0)
			{
				strcpy(cell, "-1");
			}

			// Only process if valid record
			if (validRecord) {
				char* eptr;
				switch (i)
				{
				case 0: strcpy(patTemp, cell);  break;
				case 1: strcpy(dataArr[timeNum].patient, patTemp); strcpy(dataArr[timeNum].minute, cell); break;
				case 2: dataArr[timeNum].calories = strtod(cell, &eptr); break;
				case 3: dataArr[timeNum].distance = strtod(cell, &eptr); break;
				case 4: dataArr[timeNum].floors = (unsigned int)strtoul(cell, &eptr, 10); break;
				case 5: dataArr[timeNum].heartRate = (unsigned int)atoi(cell); break;
				case 6: dataArr[timeNum].steps = (unsigned int)atoi(cell); break;
				case 7: dataArr[timeNum].sleepLevel = (Sleep)atoi(cell); break;
				}
			}
		}

		// Only increment rowNum if we saved a valid record
		if (validRecord) {
			rowNum++;
		}
	}
}

/*
Function: timeToInt
Date Created: 1/24/2026
Description: converts time to an integer from 0-1440
Input: time as a 9 char
Returns: integer between 0-1439
PreCondition:  dataArr is = 1440 records
PostCondition: none
*/
int timeToInt(char time[9])
{
	char cell[9] = { 0 };
	strcpy(cell, time);
	char* token = strtok(cell, ":");
	char* token2 = strtok(NULL, ":");
	return atoi(token) * 60 + atoi(token2);
}


/*
Function: printCSV
Date Created: 1/24/2026
Description: prints a CSV in order stated in assignment
Input: outputstream, data, various variables to give
Returns: none
PreCondition: outputstream is open
PostCondition: none
*/
void printCSV(FILE* outputstream, FitbitData dataArr[1440], float calories, float distance, float floors, float steps, float heartrate, float stepsMax, char poorSleepStart[9], char poorSleepEnd[9], char headers[8][100])
{
	fprintf(outputstream, "Total Calories,Total Distance,Total Floors,Total Steps, Avg Heartrate, Max Steps, Sleep\n");
	fprintf(outputstream, "%f,%f,%f,%f,%f,%f,%s:%s\n", calories, distance, floors, steps, heartrate, stepsMax, poorSleepStart, poorSleepEnd);
	fprintf(outputstream, "Target: ,%s,,,,,,\n", dataArr[0].patient);
	for (int i = 0; i < 8; i++)
	{
		fprintf(outputstream, "%s", headers[i]);
		if (i < 7)
		{
			fprintf(outputstream, ",");
		}
	}
	for (int i = 0; i < 1440; i++)
	{
		dataArr[i].patient == "-1" ? fprintf(outputstream, ",") : fprintf(outputstream, "%s,", dataArr[i].patient);
		dataArr[i].minute == "-1" ? fprintf(outputstream, ",") : fprintf(outputstream, "%s,", dataArr[i].minute);
		dataArr[i].calories == -1 ? fprintf(outputstream, ",") : fprintf(outputstream, "%lf,", dataArr[i].calories);
		dataArr[i].distance == -1 ? fprintf(outputstream, ",") : fprintf(outputstream, "%lf,", dataArr[i].distance);
		dataArr[i].floors == -1 ? fprintf(outputstream, ",") : fprintf(outputstream, "%d,", dataArr[i].floors);
		dataArr[i].heartRate == -1 ? fprintf(outputstream, ",") : fprintf(outputstream, "%d,", dataArr[i].heartRate);
		dataArr[i].steps == -1 ? fprintf(outputstream, ",") : fprintf(outputstream, "%d,", dataArr[i].steps);
		dataArr[i].sleepLevel == -1 ? fprintf(outputstream, "\n") : fprintf(outputstream, "%d\n", (unsigned int)dataArr[i].sleepLevel);
	}

	//Print to console
	printf("Total Calories,Total Distance,Total Floors,Total Steps, Avg Heartrate, Max Steps, Sleep\n");
	printf("%f,%f,%f,%f,%f,%f,%s:%s\n", calories, distance, floors, steps, heartrate, stepsMax, poorSleepStart, poorSleepEnd);
	printf("Target: ,%s,,,,,,\n", dataArr[0].patient);
	for (int i = 0; i < 8; i++)
	{
		printf("%s", headers[i]);
		if (i < 7)
		{
			printf(",");
		}
	}
	for (int i = 0; i < 1440; i++)
	{
		dataArr[i].patient == "-1" ? printf(",") : printf("%s,", dataArr[i].patient);
		dataArr[i].minute == "-1" ? printf(",") : printf("%s,", dataArr[i].minute);
		dataArr[i].calories == -1 ? printf(",") : printf("%lf,", dataArr[i].calories);
		dataArr[i].distance == -1 ? printf(",") : printf("%lf,", dataArr[i].distance);
		dataArr[i].floors == -1 ? printf(",") : printf("%d,", dataArr[i].floors);
		dataArr[i].heartRate == -1 ? printf(",") : printf("%d,", dataArr[i].heartRate);
		dataArr[i].steps == -1 ? printf(",") : printf("%d,", dataArr[i].steps);
		dataArr[i].sleepLevel == -1 ? printf("\n") : printf("%d\n", (unsigned int)dataArr[i].sleepLevel);
	}
}