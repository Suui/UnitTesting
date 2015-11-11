#pragma once
#include <queue>

typedef void (*TestFunction)();

static std::queue<TestFunction> testQueue;


class TestClass
{
public:
	virtual ~TestClass();
	virtual void testFunction();
};

	
class TestRepository
{
	TestRepository() {}
	TestRepository(TestRepository const&) = delete;
	void operator=(TestRepository const&) = delete;

	std::vector<TestClass> testClassRepo;

public:

	static TestRepository& getInstance()
	{
		static TestRepository instance;
		return instance;
	}

	void registerTestClass(TestClass& testClass)
	{
		testClassRepo.push_back(testClass);
	}

	void runTests()
	{
		testClassRepo[0].testFunction();
	}
};


namespace Namespace
{
	struct TestRegistrator
	{
		TestRegistrator();
		TestRegistrator(TestFunction testFunction);
		TestRegistrator(TestClass& testClass)
		{
			TestRepository::getInstance().registerTestClass(testClass);
		}
	};
}

#define TEST_CLASS(ClassName) \
class ClassName : public TestClass \
{ \
public: \
	void testFunction() override; \
}; \
namespace { static Namespace::TestRegistrator registrator(ClassName testClass()); } \
void ClassName::testFunction()


namespace UnitTestNamespace
{
	struct TestRegistrator
	{
		TestRegistrator(TestFunction testFunction);
	};
}

#define TEST(TestName) \
static void TestName(); \
namespace { UnitTestNamespace::TestRegistrator testRegistrator(&TestName); } \
static void TestName()


class UnitTest
{

public:

	static void registerTest(TestFunction& testFunction) { testQueue.push(testFunction); }
};


// Stackoverflow example
struct MyClasses
{
	static std::vector<std::string> myclasses;
	MyClasses(std::string name) { myclasses.push_back(name); }
};

#define REGISTER_CLASS(cls) static MyClasses myclass_##cls(#cls);
