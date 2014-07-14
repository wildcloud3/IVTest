#include <UnitTest++.h>

#pragma comment(lib, "UnitTest++.lib")

TEST(DefaultTest)
{
	CHECK(false);
}

int main()
{
	UnitTest::RunAllTests();

	system("pause");
	return 0;
}