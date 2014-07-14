#include <vector>

#include <UnitTest++.h>

#include <LString.h>

SUITE(LStringBasic)
{
	TEST(DefaultNull)
	{
		LString s0;
		CHECK(NULL != s0.c_str());
	}

	TEST(DefaultEqual)
	{
		LString s0 = "hello";
		LString s1("hello");
		CHECK_EQUAL(s0.c_str(), s1.c_str());
	}

	TEST(CopyConstructorEqual)
	{
		LString s0 = "hello";
		LString s1(s0);
		CHECK_EQUAL(s0.c_str(), s1.c_str());
	}

	TEST(CopyConstructorRefNotEqual)
	{
		LString s0 = "hello";
		LString s1(s0);
		CHECK(s0.c_str() != s1.c_str());
	}

	void foo(LString x){}
	void bar(LString const &x){}
	LString baz()
	{
		LString ret("world");
		return ret;
	}

	TEST(PassingValueCopy)
	{
		LString s0;
		foo(s0);
	}

	TEST(PassingValueConstRef)
	{
		LString s0;
		bar(s0);
	}

	TEST(ReturnVal)
	{
		LString s0 = baz();
		CHECK_EQUAL(s0.c_str(), "world");
	}

	TEST(IndexVal)
	{
		LString s0 = baz();
		CHECK_EQUAL(s0[2], 'r');
	}

	TEST(CompareLarge)
	{
		LString s0 = baz();
		CHECK(s0 > "fale");
	}

	TEST(CompareSmall)
	{
		LString s0 = baz();
		CHECK(s0 < "zero");
	}

	TEST(CompareEqual)
	{
		LString s0 = baz();
		CHECK(s0 == "world");
	}

	TEST(VectorLString)
	{
		LString s0;
		LString s1 = baz();

		std::vector<LString> lsVec;
		lsVec.push_back(s0);
		lsVec.push_back(s1);
		lsVec.push_back(baz());
		lsVec.push_back("good");
	}

}