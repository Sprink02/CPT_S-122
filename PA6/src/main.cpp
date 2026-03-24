#pragma once
#include "./BST/BST/BST.hpp"
#include <cassert>

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

int main()
{
	BST<char, string> tree("statics/MorseTable.txt");

    std::println("=== Morse Code Table (in-order) ===");
    tree.print();
    std::cout << "\n";

    // Open the text file to convert
    std::ifstream convertFile("statics/Convert.txt");
    assert(convertFile.is_open() && "ERROR: Could not open Convert.txt"); //file open sanity check

    std::println("=== Morse Code Conversion ===");

    char ch;
    while (convertFile.get(ch)) {
        if (ch == '\n')
        {
            std::cout << "\n";
        }
        else if (ch == ' ') {
            std::print("   "); //three spaces
        }
        else {
            std::string morse = tree.search(static_cast<char>(toupper(ch))); //change all to upper before search
            //^ follows the "search ()" requirement in part 3
            if (!morse.empty())
            {
                std::print("{} ", morse);
            }
        }
    }

    convertFile.close();
	return 0;
}