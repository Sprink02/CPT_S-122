#pragma once
#include "../src/Queue/queue.hpp"
#include "../src/SimWrapper/sim.hpp"
#include "../src/Test/test.hpp"
#include "chrono"
//Compiler should be set to c++ 23 or newer
#include <windows.h> //just for colors


int main()
{
	//COLOR SUPPORT!!!! YAHOOOOOO
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwMode = 0;
	GetConsoleMode(hOut, &dwMode);
	SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
	//End of colors
	TEST t;
	t.run();
	int i = -1;
	while (i != 0)
	{
		pause();
		clr_scr();
		std::println("0 for exit, # of minutes to run next sim");
		std::cin >> i;
		std::cin.ignore();
		clr_scr();
		if (i == 0) break;
		SIM newS;
		newS.run(i);
	}
	return 0;
}