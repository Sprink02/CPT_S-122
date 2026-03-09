#pragma once
#include <string>
#include <print>
#include <limits>
#include <ctime>
#include <iostream>
#include <cassert>

#include "../Queue/queue.hpp"
#include "../SimWrapper/sim.hpp"

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

class TEST
{
private:
	bool test_queue_enqueue_empty();
	bool test_queue_enqueue_one();
	bool test_queue_dequeue_one();
	bool test_queue_dequeue_two();
	bool test_sim_24h();
public:
	void run();
};
