#include "stdafx.h"
#include "CppUnitTest.h"

#include <vector>

#include "LString.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IVUnitTest
{		
	TEST_CLASS(LStringUnitTest)
	{
	public:
		
		TEST_METHOD(Pass)
		{
			Assert::AreEqual(1, 1);
		}

		void foo(LString x){}
		void bar(LString const &x){}
		LString baz()
		{
			LString ret("world");
			return ret;
		}

		TEST_METHOD(LStringBasic)
		{
			LString s0;
			Assert::IsNotNull(s0.c_str());

			LString s1("hello");
			Assert::AreNotEqual(s0.c_str(), s1.c_str());

			LString s2(s0);
			Assert::AreEqual(s0.c_str(), s2.c_str());

			LString s3 = s1;
			Assert::AreEqual(s1.c_str(), s3.c_str());

			Assert::IsFalse(s2 == s1);

			s2 = s1;
			Assert::IsTrue(s2 == s1);
			Assert::AreEqual(s1.c_str(), s2.c_str());

			foo(s1);
			bar(s1);
			foo("tempo");
			bar("tempo");
			LString s4 = baz();
			Assert::AreEqual(s4.c_str(), "world");

			Assert::AreEqual(s4[2], 'r');
			Assert::IsTrue(s4 > "fale");
			Assert::IsTrue(s4 < "zero");
			Assert::IsTrue(s4 == "world");

			std::vector<LString> lsVec;
			lsVec.push_back(s0);
			lsVec.push_back(s1);
			lsVec.push_back(baz());
			lsVec.push_back("good");

		}
	};
}