#include "Complex.hpp"

//namespace hi { int hello = 1; };

int main()
{
	Complex n1(12, 2);
	n1.print(std::cout);
	Complex n2(6, 3);
	Complex n3 = n1 - n2; //6-1i
	n2.print(std::cout);
	n3.print(std::cout);
	n1.add(n2);
	n1.print(std::cout);

	
	return 0;
}