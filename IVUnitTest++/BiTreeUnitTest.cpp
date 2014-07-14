#include <UnitTest++.h>

#include <BiTree.h>

typedef BiNode_<int> BiNode;

SUITE(BiTreeBasic)
{
	struct BasicFixture
	{
		BasicFixture()
		{
			m_tree = new BiNode(1);
			m_tree->left() = new BiNode(2);
			m_tree->right() = new BiNode(3);

			m_tree->left()->left() = new BiNode(4);
			m_tree->left()->right() = new BiNode(5);

			m_tree->right()->left() = new BiNode(6);
			m_tree->right()->right() = new BiNode(7);
		}
		~BasicFixture()
		{
			if (nullptr != m_tree)
			{
				delete m_tree;
			}
		}

		BiNode *m_tree;
	};

	TEST_FIXTURE(BasicFixture, SearchEqual)
	{
		auto tree = m_tree;
		CHECK(tree->left() == tree->search(2));
		CHECK(tree->left()->right() == tree->search(5));
	}

	TEST_FIXTURE(BasicFixture, SameCheck)
	{
		auto tree = m_tree;
		CHECK(tree->left()->right()->isSame(tree->search(5)));
	}

	TEST_FIXTURE(BasicFixture, NodeCount)
	{
		auto tree = m_tree;
		CHECK_EQUAL(7, tree->count());
	}

	TEST_FIXTURE(BasicFixture, HeightEval)
	{
		auto tree = m_tree;
		CHECK_EQUAL(3, tree->height());
	}

	TEST_FIXTURE(BasicFixture, SubHeightEval)
	{
		auto tree = m_tree;
		CHECK_EQUAL(1, tree->left()->right()->height());
	}

}