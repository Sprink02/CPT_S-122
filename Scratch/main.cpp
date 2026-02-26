#include <iostream>

int main()
{
	int var = 1;
	int* p = &var;
	int& ref = var;
	std::cout << var << ": " << p << ": " << ref << std::endl;

	return 0;
}