#include <iostream>
#include <map>
#include <string>
#include <vector>


class TestClass
{
public:

	TestClass()
	{
		
	}

	void printSomething()
	{
		std::cout << "I've printed something" << std::endl;
	}
};


typedef void(*TestFunction)();

class TestRepository
{
public:
	
	static std::map<std::string, TestClass> testClasses;
	
	static std::vector<TestFunction> testFunctions;
};

std::map<std::string, TestClass> TestRepository::testClasses;

std::vector<TestFunction> TestRepository::testFunctions;


class TestFunctionRegistrar
{
public:

	TestFunctionRegistrar(TestFunction testFunction)
	{
		TestRepository::testFunctions.push_back(testFunction);
	}
};


#define NAME_AND_LINE_STRINGIFIED(name, line) name##line
#define NAME_AND_LINE(name, line) NAME_AND_LINE_STRINGIFIED(name, line)
#define GET_UNIQUE_NAME() NAME_AND_LINE(FluentUnrealUnit, __LINE__)

#define TEST_CLASS(ClassName)	\
class ClassName : public TestClass

#define TEST(TestName)				\
TestFunctionRegistrar GET_UNIQUE_NAME()(TestName);	\
void TestName()


TEST_CLASS(BooleanShould)
{
public:

	static void report_error_when_unmatched();

	static void be_true_when_true();

	static void be_false_when_false();
};


TEST(BooleanShould::report_error_when_unmatched)
{
	std::cout << "Report error when unmatched" << std::endl;
}


TEST(BooleanShould::be_true_when_true)
{
	std::cout << "Be True When True!" << std::endl;
}


TEST(BooleanShould::be_false_when_false)
{
	std::cout << "Be False When False!" << std::endl;
}


int main()
{
	for (auto it : TestRepository::testClasses)
	{
		std::cout << it.first << " says: ";
		TestRepository::testClasses[it.first].printSomething();
	}

	for (auto it : TestRepository::testFunctions)
	{
		it();
	}
}
