#include "UnitTest.hpp"

struct MyClasses
{
	static std::vector<std::string> myclasses;
	MyClasses(std::string name) { myclasses.push_back(name); }
};

std::vector<std::string> MyClasses::myclasses;

#define REGISTER_CLASS(cls) static MyClasses myclass_##cls(#cls);

struct XYZ
{
};

REGISTER_CLASS(XYZ);

int main()
{
	std::vector<std::string> local = MyClasses::myclasses;
	TestRepository::getInstance().runTests();
}