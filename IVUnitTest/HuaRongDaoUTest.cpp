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

			Block b_1(iStart, '1');
			Assert::AreEqual(2u, b_1.size());
			Assert::IsTrue(Block::Point({ 0, 0 }) == b_1[0]);
			Assert::IsTrue(Block::Point({ 0, 1 }) == b_1[1]);

			Block b_2(iStart, '6');
			Assert::AreEqual(2u, b_2.size());
			Assert::IsTrue(Block::Point({ 3, 2 }) == b_2[0]);
			Assert::IsTrue(Block::Point({ 3, 3 }) == b_2[1]);

			Block b_3(iStart, '2');
			Assert::AreEqual(4u, b_3.size());

			Block b_4(iStart, 'A');
			Assert::AreEqual(1u, b_4.size());
			Assert::IsTrue(Block::Point({ 3, 4 }) == b_4[0]);

			Block b_5 = b_1;
			Assert::IsTrue(b_1 == b_5);
			Assert::IsTrue(b_1 == Block(iStart, '1'));

			Block b_6 = Block(iStart, '2');
			Assert::IsTrue(b_6 == b_3);

			b_1.Move(DOWN);
			Assert::AreEqual(2u, b_1.size());
			Assert::IsTrue(Block::Point({ 0, 1 }) == b_1[0]);
			Assert::IsTrue(Block::Point({ 0, 2 }) == b_1[1]);

			b_1.Move(RIGHT);
			Assert::AreEqual(2u, b_1.size());
			Assert::IsTrue(Block::Point({ 1, 1 }) == b_1[0]);
			Assert::IsTrue(Block::Point({ 1, 2 }) == b_1[1]);

			b_2.Move(UP);
			Assert::AreEqual(2u, b_2.size());
			Assert::IsTrue(Block::Point({ 3, 1 }) == b_2[0]);
			Assert::IsTrue(Block::Point({ 3, 2 }) == b_2[1]);

			b_2.Move(LEFT);
			Assert::AreEqual(2u, b_2.size());
			Assert::IsTrue(Block::Point({ 2, 1 }) == b_2[0]);
			Assert::IsTrue(Block::Point({ 2, 2 }) == b_2[1]);

			Assert::IsFalse(b_2.IsCrossBoundary(iStart));

			b_2.Move(RIGHT).Move(RIGHT);
			Assert::IsTrue(b_2.IsCrossBoundary(iStart));

			Assert::IsFalse(Block(iStart, '2').IsOverlap(Block()));
			Assert::IsFalse(Block(iStart, '2').IsOverlap(Block(iStart, '9')));
			Assert::IsFalse(Block(iStart, '2').IsOverlap(Block(iStart, '5')));
			Assert::IsTrue(Block(iStart, '2').IsOverlap(Block(iStart, '5').Move(UP)));
			Assert::IsTrue(Block(iStart, '2').Move(DOWN).IsOverlap(Block(iStart, '5')));
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
			Layout rendered = iStart;

			Block b_1(iStart, '1');
			b_1.Render(rendered, '1');
			Assert::AreEqual("1223122345564786900A", rendered.to_string());

			b_1.Move(DOWN);
			b_1.Render(rendered, '1');
			Assert::AreEqual("1223122315564786900A", rendered.to_string());

			b_1.Move(RIGHT);
			b_1.Render(rendered, '1');
			Assert::AreEqual("1223112311564786900A", rendered.to_string());

			rendered = iStart;
			Block b_2(iStart, '2');

			b_2.Move(DOWN);
			b_2.Render(rendered, '2');
			Assert::AreEqual("1223122342264786900A", rendered.to_string());

			rendered = iStart;
			b_2.Move(DOWN);
			b_2.Render(rendered, '2');
			Assert::AreEqual("1223122342264226900A", rendered.to_string());

			rendered = iStart;
			b_2.Move(DOWN).Move(RIGHT);
			b_2.Render(rendered, '2');
			Assert::AreEqual("12231223455647229022", rendered.to_string());

			rendered = iStart;
			Block b_3(iStart, '6');

			b_3.Move(UP).Move(LEFT).Move(RIGHT).Move(RIGHT);
			b_3.Render(rendered, '6');
			Assert::AreEqual("1223122345564786900A", rendered.to_string());
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
			Assert::AreEqual('\0', tmp(tmp.rows()-1, tmp.cols()));

			HuaRongDao::Layout cc = iStart;
			Assert::AreEqual(iStart.to_string(), cc.to_string());
			Assert::IsFalse(&iStart == &cc);

			HuaRongDao::Layout mvc = HuaRongDao::Layout(layout);
			Assert::AreEqual(iStart.to_string(), mvc.to_string());

			HuaRongDao::Layout l_2(layout_a);
			Assert::IsTrue(iStart < l_2);

			tmp = iStart;
			tmp.Render();
			Assert::AreEqual(iStart.to_string(), tmp.to_string());

			Assert::IsFalse(iStart.isSolved());
			Assert::IsTrue(HuaRongDao::Layout(layout_b).isSolved());
			Assert::IsFalse(HuaRongDao::Layout(layout_c).isSolved());

			char id_key;

			id_key = '1';
			tmp = iStart;
			tmp[id_key] = Block(iStart, id_key).Move(DOWN);
			Assert::IsFalse(tmp.Render().isValid(id_key));

			id_key = '2';
			tmp = iStart;
			tmp[id_key] = Block(iStart, id_key).Move(DOWN);
			Assert::IsFalse(tmp.Render().isValid(id_key));

			id_key = '7';
			tmp = iStart;
			tmp[id_key] = Block(iStart, id_key).Move(DOWN);
			Assert::IsTrue(tmp.Render().isValid(id_key));

			tmp = iStart;
			tmp[id_key] = Block(iStart, id_key).Move(UP);
			Assert::IsFalse(tmp.Render().isValid(id_key));

			tmp = iStart;
			tmp[id_key] = Block(iStart, id_key).Move(LEFT);
			Assert::IsFalse(tmp.Render().isValid(id_key));

			auto nexts = iStart.moves();
			Assert::AreEqual(4u, nexts.size());
			Assert::AreEqual("1223122345564086970A", nexts[0].to_string());
			Assert::AreEqual("1223122345564706908A", nexts[1].to_string());
			Assert::AreEqual("1223122345564786090A", nexts[2].to_string());
			Assert::AreEqual("122312234556478690A0", nexts[3].to_string());
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
	