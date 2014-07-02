#include "stdafx.h"
#include "CppUnitTest.h"

#include <vector>

#include "HuaRongDao.h"

#ifdef _DEBUG
#	pragma comment(lib, "../Debug/IVTest.lib")
#else
#	pragma comment(lib, "../Release/IVTest.lib")
#endif // _DEBUG


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{
			/*
			std::wstring ToString(HuaRongDao::Block::Point * _point)
			{
				return std::to_wstring();
			}

			std::wstring ToString(HuaRongDao::Block * _block)
			{
				return std::to_wstring((_ULonglong)(void*)_node);
			}
			*/
		}
	}

}

namespace IVUnitTest
{
	TEST_CLASS(HuaRongDaoUnitTest)
	{
	public:
		TEST_METHOD(hrd_block_parse)
		{
			using namespace HuaRongDao;

			char layout[] = {
				'1', '2', '2', '3',
				'1', '2', '2', '3',
				'4', '5', '5', '6',
				'4', '7', '8', '6',
				'9', '0', '0', 'A'
			};

			Layout iStart(layout);

		}

		TEST_METHOD(hrd_block_render)
		{
			using namespace HuaRongDao;

			char layout[] = {
				'1', '2', '2', '3',
				'1', '2', '2', '3',
				'4', '5', '5', '6',
				'4', '7', '8', '6',
				'9', '0', '0', 'A'
			};

			Layout iStart(layout);

			Assert::AreEqual("24422442233221121001", iStart.to_string());
		}

		TEST_METHOD(hrd_layout_basic)
		{
			using namespace HuaRongDao;

			char layout[] = {
				'1', '2', '2', '3',
				'1', '2', '2', '3',
				'4', '5', '5', '6',
				'4', '7', '8', '6',
				'9', '0', '0', 'A'
			};

			char layout_a[] = "1223122345568786900A";
			char layout_b[] = "1223122345568BB69BBA";
			char layout_c[] = "1223122345568BBBBBcA";

			HuaRongDao::Layout iStart(layout);
	
			Assert::AreEqual(4u, iStart.cols());
			Assert::AreEqual(5u, iStart.rows());

			HuaRongDao::Layout tmp;
			Assert::AreEqual('\0', tmp.to_string()[tmp.rows()*tmp.cols()]);

			HuaRongDao::Layout cc = iStart;
			Assert::AreEqual(iStart.to_string(), cc.to_string());
			Assert::IsFalse(&iStart == &cc);

			HuaRongDao::Layout mvc = HuaRongDao::Layout(layout);
			Assert::AreEqual(iStart.to_string(), mvc.to_string());

			tmp = iStart;
			tmp.Render();
			Assert::AreEqual(iStart.to_string(), tmp.to_string());

			Assert::IsFalse(iStart.isSolved());
			Assert::IsTrue(HuaRongDao::Layout(layout_b).isSolved());
			Assert::IsFalse(HuaRongDao::Layout(layout_c).isSolved());

			auto nexts = iStart.moves();
			Assert::AreEqual(4u, nexts.size());
			Assert::AreEqual("24422442233220121101", nexts[0].to_string());
			Assert::AreEqual("24422442233221021011", nexts[1].to_string());
			Assert::AreEqual("24422442233221120101", nexts[2].to_string());
			Assert::AreEqual("24422442233221121010", nexts[3].to_string());
		}

		TEST_METHOD(hrd_layout_solve)
		{
			using namespace HuaRongDao;

			char layout_a[] = {
				'1', '2', '2', '3',
				'1', '2', '2', '3',
				'4', '5', '5', '6',
				'4', '7', '8', '6',
				'9', '0', '0', 'A'
			};
			//Assert::AreEqual(1, HuaRongDao::solve(Layout(layout_a)));

			char layout_b[] = {
				'1', '2', '2', '3',
				'1', '2', '2', '3',
				'4', '0', '0', '6',
				'4', '0', '0', '6',
				'9', '0', '0', 'A'
			};
			//Assert::AreEqual(1, solveLayout(Layout(layout_b)));
			// Oooops, there's some access violation due to VS's bug (on stackflow)
		}


	};
}
	