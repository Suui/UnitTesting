#include <iostream>
#include <map>
#include <string>


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

class TestClass
{
public:

	void printSomething()
	{
		std::cout << "I've printed something" << std::endl;
	}
};

class TestRepository
{
public:
	static std::map<std::string, TestClass> testClasses;
};

std::map<std::string, TestClass> TestRepository::testClasses;

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


int main()
{
	TestClass testClass;
	TestRegistrar registrar(testClass, "testClass");

	for (auto it : TestRepository::testClasses)
	{
		std::cout << it.first << " says: ";
		TestRepository::testClasses[it.first].printSomething();
	}
}