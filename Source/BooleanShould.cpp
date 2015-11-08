#include "UnitTest.hpp"
#include <iostream>

//TEST_CASE("Boolean Should")
//{
//	SECTION("return true when it is true")
//	{
//		CHECK(true == true);
//	}
//}


struct XYZ
{
};

REGISTER_CLASS(XYZ);



TEST_CLASS(BooleanShould)
{
	bool value = true;

	std::cout << "value before anonymous scope: " << value << std::endl;

	{
		value = false;
		std::cout << "value inside anonymous scope: " << value << std::endl;
	}

	std::cout << "value after anonymous scope: " << value << std::endl;
}

//TEST(return_true_when_it_is_true)
//{
//
//}

//void testFunc() {}
//
//void equivalentCode()
//{
//	UnitTestNamespace::TestRegistrator hello (&testFunc);
//}
	