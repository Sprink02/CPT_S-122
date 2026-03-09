#include <iostream>
#include <cstdio>
#include <cstring>
#include <print>
#include <random>
#include <queue>
#include <stack>


//std clearscreen
inline void clr_scr()
{
	std::cout << "\x1B[2J\x1B[0;0H";
}

//std pause Wait for \n
inline void pause()
{
	std::print("Press ENTER to continue");
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

typedef struct myStruct
{
	int i;
	double d;
}MyStruct;

int main()
{
	
}