#include <UnitTest++.h>

#pragma comment(lib, "UnitTest++.lib")
#pragma comment(lib, "IVTest.lib")

TEST(DefaultTest)
{
	CHECK(true);
}

int main()
{
	return UnitTest::RunAllTests();
}