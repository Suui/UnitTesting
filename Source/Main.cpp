#include <iostream>
#include <map>
#include <string>
#include <vector>


class TestClass
{
public:

	virtual ~TestClass()
	{
	}

	TestClass()
	{
		
	}

	void printSomething()
	{
		std::cout << "I've printed something" << std::endl;
	}

	virtual void RegisterTests() {}

	virtual void ExecuteTests() {}
};


typedef void(*TestFunction)();

class TestRepository
{
public:
	
	static std::map<std::string, TestClass> testClasses;
	
	static std::vector<TestClass*> newTestClasses;
	
	static std::vector<TestFunction> testFunctions;

	static std::vector<std::string> testClassNames;
};

std::map<std::string, TestClass> TestRepository::testClasses;

std::vector<TestFunction> TestRepository::testFunctions;

std::vector<TestClass*> TestRepository::newTestClasses;

std::vector<std::string> TestRepository::testClassNames;


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


class TestClassRegistrar
{
public:

	TestClassRegistrar(TestClass* testClass)
	{
		TestRepository::newTestClasses.push_back(testClass);
	}
};

class TestFunctionRegistrar
{
public:

	TestFunctionRegistrar(TestFunction testFunction)
	{
		TestRepository::testFunctions.push_back(testFunction);
	}
};

class TestClassNamesRegistrar
{
public:

	TestClassNamesRegistrar(std::string testClassName)
	{
		TestRepository::testClassNames.push_back(testClassName);
	}
};

typedef TestClass* TestClassPointer;


#define TEST_CLASS(ClassName)					\
class ClassName;								\
ClassName* fooBool;								\
TestClassRegistrar fooRegistrar(fooBool);		\
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

#define Test(TestName)	\
void TestName()


#define AssertThat(parameter) \


TEST_CLASS(BooleanShould)
{
public:

	typedef void(BooleanShould::*MemberFunction)();
	std::vector<MemberFunction> memberFunctions;

	TEST(report_error_when_unmatched);

	TEST(be_true_when_true);

	TEST(be_false_when_false);

	Test(test_function)
	{
		std::cout << "I've been called as a member function pointer" << std::endl;
	}

	void random_test()
	{
		auto number = 5;

		AssertThat(number).Is(5);
	}

	void RegisterTests() override
	{
		memberFunctions.push_back(&BooleanShould::test_function);
	}

	void ExecuteTests() override
	{
		for (auto function : memberFunctions)
		{
			(this->*function)();
		}
	}
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

	BooleanShould* ptr;
	ptr = new BooleanShould();

	for (auto testClass : TestRepository::newTestClasses)
	{
		testClass->printSomething();
	}
}
