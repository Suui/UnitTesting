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

public:

	static TestRepository& getInstance()
	{
		static TestRepository instance;
		return instance;
	}
};


namespace Namespace
{
	struct TestRegistrator
	{
		TestRegistrator();
	};
}

#define TEST_CLASS(ClassName) \
class ClassName : public TestClass \
{ \
public: \
	void testFunction() override; \
}; \
namespace { Namespace::TestRegistrator registrator(); } \
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
