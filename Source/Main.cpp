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



class TestRegistrar
{
public:

	TestRegistrar(TestClass& testClass, std::string testClassName)
	{
		TestRepository::testClasses.insert(std::make_pair(testClassName, testClass));
	}
};

#define REGISTER_TEST(ClassName)					\
TestClass ClassName;								\
TestRegistrar registrar##ClassName(ClassName, #ClassName);

REGISTER_TEST(TestShould);


class TestFunctionRegistrar
{
public:

	TestFunctionRegistrar(TestFunction testFunction)
	{
		TestRepository::testFunctions.push_back(testFunction);
	}
};


#define TEST_CLASS(ClassName)	\
class ClassName : public TestClass

#define TEST(TestName)				\
static void TestName()				\

#define IMPLEMENT()			\
TestFunctionRegistrar registrar_BooleanShould_be_true_when_true(BooleanShould::be_true_when_true);

#define IMPLEMENTATION(TestName)		\
TestFunctionRegistrar registrar_BooleanShould_be_false_when_false(BooleanShould::be_false_when_false);	\
void TestName()

#define NAME_AND_LINE_STRINGIFIED(name, line) name##line
#define NAME_AND_LINE(name, line) NAME_AND_LINE_STRINGIFIED(name, line)
#define GET_UNIQUE_NAME() NAME_AND_LINE(FluentUnrealUnit, __LINE__)

//#define REGISTER(TestName)				\
//TestFunctionRegistrar registrar_BooleanShould_report_error_when_unmatched(TestName);	\
//void TestName()

#define REGISTER(TestName)				\
TestFunctionRegistrar GET_UNIQUE_NAME()(TestName);	\
void TestName()


TEST_CLASS(BooleanShould)
{
public:

	TEST(report_error_when_unmatched);

	TEST(be_true_when_true);

	TEST(be_false_when_false);
};


REGISTER(BooleanShould::report_error_when_unmatched)
{
	std::cout << "Report error when unmatched" << std::endl;
}


IMPLEMENT()
void BooleanShould::be_true_when_true()
{
	std::cout << "Be True When True!" << std::endl;
}


IMPLEMENTATION(BooleanShould::be_false_when_false)
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
