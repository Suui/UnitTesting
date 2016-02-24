#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>


#define Test()

#define Setup()


class BooleanShould
{
public:

	Setup()
	void initialize()
	{
		std::cout << "The initialize function has been called" << std::endl;
	}

	Test()
	void test_function()
	{
		std::cout << "The test function has been called" << std::endl;
	}
};


std::vector<std::string> Split(std::string& string)
{
	std::stringstream stream(string);
	std::string element;
	auto elements = std::vector<std::string>();

	while (std::getline(stream, element, ' '))
	{
		elements.push_back(element);
	}

	return elements;
}

typedef void (BooleanShould::*TestFunction)();

#define TEST_FUNCTION_PTR(ClassName, FunctionName) &ClassName::FunctionName

int main()
{
	std::ifstream fileStream("D:\\Projects\\Programming\\Cpp\\UnitTesting\\Source\\Main.cpp");
	std::string line;
	
	while (std::getline(fileStream, line))
	{
		if (line.find("Test()") != std::string::npos)
		{
			if (line.find("#define") != std::string::npos) continue;
			if (line.find("find") != std::string::npos) continue;

			std::getline(fileStream, line);
			auto words = Split(line);
			auto functionName = words[1].substr(0, words[1].length() - 2);
			std::cout << "Test Function with name: " << functionName << std::endl;
//			TestFunction function = TEST_FUNCTION_PTR("BooleandShould", functionName);
		}
	}
}
