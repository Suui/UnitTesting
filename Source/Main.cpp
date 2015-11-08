#include "UnitTest.hpp"
#include <iostream>


void scopeTest()
{
	int a = 5;
	std::cout << a << std::endl;
	{
		a = 10;
		std::cout << a << std::endl;
	}
	std::cout << a << std::endl;
}


int main()
{
	scopeTest();
	std::vector<std::string> local = MyClasses::myclasses;
	//TestRepository::getInstance().runTests();
}