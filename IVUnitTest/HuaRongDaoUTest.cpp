#include "stdafx.h"
#include "CppUnitTest.h"

#include <vector>

#include "HuaRongDao.h"

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

			b_1.Move(Block::DOWN);
			Assert::AreEqual(2u, b_1.size());
			Assert::IsTrue(Block::Point({ 0, 1 }) == b_1[0]);
			Assert::IsTrue(Block::Point({ 0, 2 }) == b_1[1]);

			b_1.Move(Block::RIGHT);
			Assert::AreEqual(2u, b_1.size());
			Assert::IsTrue(Block::Point({ 1, 1 }) == b_1[0]);
			Assert::IsTrue(Block::Point({ 1, 2 }) == b_1[1]);

			b_2.Move(Block::UP);
			Assert::AreEqual(2u, b_2.size());
			Assert::IsTrue(Block::Point({ 3, 1 }) == b_2[0]);
			Assert::IsTrue(Block::Point({ 3, 2 }) == b_2[1]);

			b_2.Move(Block::LEFT);
			Assert::AreEqual(2u, b_2.size());
			Assert::IsTrue(Block::Point({ 2, 1 }) == b_2[0]);
			Assert::IsTrue(Block::Point({ 2, 2 }) == b_2[1]);

			Assert::IsFalse(b_2.IsCrossBoundary(iStart));

			b_2.Move(Block::RIGHT).Move(Block::RIGHT);
			Assert::IsTrue(b_2.IsCrossBoundary(iStart));

			Assert::IsFalse(Block(iStart, '2').IsOverlap(Block()));
			Assert::IsFalse(Block(iStart, '2').IsOverlap(Block(iStart, '9')));
			Assert::IsFalse(Block(iStart, '2').IsOverlap(Block(iStart, '5')));
			Assert::IsTrue(Block(iStart, '2').IsOverlap(Block(iStart, '5').Move(Block::UP)));
			Assert::IsTrue(Block(iStart, '2').Move(Block::DOWN).IsOverlap(Block(iStart, '5')));
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

			b_1.Move(Block::DOWN);
			b_1.Render(rendered, '1');
			Assert::AreEqual("1223122315564786900A", rendered.to_string());

			b_1.Move(Block::RIGHT);
			b_1.Render(rendered, '1');
			Assert::AreEqual("1223112311564786900A", rendered.to_string());

			rendered = iStart;
			Block b_2(iStart, '2');

			b_2.Move(Block::DOWN);
			b_2.Render(rendered, '2');
			Assert::AreEqual("1223122342264786900A", rendered.to_string());

			rendered = iStart;
			b_2.Move(Block::DOWN);
			b_2.Render(rendered, '2');
			Assert::AreEqual("1223122342264226900A", rendered.to_string());

			rendered = iStart;
			b_2.Move(Block::DOWN).Move(Block::RIGHT);
			b_2.Render(rendered, '2');
			Assert::AreEqual("12231223455647229022", rendered.to_string());

			rendered = iStart;
			Block b_3(iStart, '6');

			b_3.Move(Block::UP).Move(Block::LEFT).Move(Block::RIGHT).Move(Block::RIGHT);
			b_3.Render(rendered, '6');
			Assert::AreEqual("1223122345564786900A", rendered.to_string());
		}
	};
}
	