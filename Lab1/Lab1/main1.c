#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>

char* my_strcat(char* destination, const char* source)
{
	//Test 1 (Null pointer for either)
	if (destination == NULL)
	{
		return NULL;
	}
	if (source == NULL)
	{
		return destination;
	}

	//Test 2 (Both empty string)
	if (*destination == NULL && *source == NULL)
	{
		return destination;
	}

	int dstLen = strlen(destination), srcLen = strlen(source) + 1;

	for (int i = 0; i < srcLen; i++)
	{
		destination[dstLen + i] = source[i];
	}

	return destination;
}
/*
char string1[1000] = "";
	char* string2 = "";
	printf("%s", my_strcat(string1, string2));
	printf("%c",254);
	return 0;
*/

void str_rev_rec(char* str, int len)
{
	if (len < 2) return; //Base Case

	char tmp = *str; //Rev String
	*str = str[len - 1];
	str[len - 1] = tmp;

	return str_rev_rec(str + 1, len - 2); //Recursive Step
}
/*
	char str[] = "";
	int len = strlen(str);
	str_rev_rec(str, len);
	printf("%s",str);
	return 0;
*/


char* myStrTok(char* str, const char* delim)
{
	static char* pToken;
	int i = 0;
	if (str != NULL)
	{
		while (str[i] == *delim)
		{
			if (str[i] == 0)
			{
				return NULL;
			}
			i++;
		}
		int j = 0;
		while (str[i + j] != 0)
		{
			if (str[i + j] == *delim)
			{
				str[i + j] == 0;
				pToken = str + i + j + 1;
			}
			j++;
		}
		return str;
	}
	if (str == NULL)
	{
		while (pToken[i] == *delim)
		{
			if (pToken[i] == 0)
			{
				return NULL;
			}
			i++;
		}
		int j = 0;
		while (pToken[i + j] != 0)
		{
			if (pToken[i + j] == *delim)
			{
				pToken[i + j] == 0;
				pToken = i + j + 1;
			}
			j++;
		}
		return pToken;
	}
}




int main()
{
	char str[8] = "a,b,c,d";
	char* delim = ",";
	myStrTok(str, delim);
	for (int i = 0; i < 4; i++)
	{
		myStrTok(NULL, delim);
		printf("%s\n", str);
	}
	return 0;
}