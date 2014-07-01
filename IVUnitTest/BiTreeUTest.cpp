#include "stdafx.h"
#include "CppUnitTest.h"

#include <ctime>

#include <vector>

#include "BiTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{
			std::wstring ToString(BiNode_<int> * _node)
			{
				return std::to_wstring((_ULonglong)(void*)_node);
			}
		}
	}

}

namespace IVUnitTest
{		
	TEST_CLASS(BiTreeUnitTest)
	{
	public:
	
		TEST_METHOD(BiTreeBasic)
		{
			typedef BiNode_<int> BiNode;

			BiNode * tree = new BiNode(1);
			tree->left() = new BiNode(2);
			tree->right() = new BiNode(3);

			tree->left()->left() = new BiNode(4);
			tree->left()->right() = new BiNode(5);

			tree->right()->left() = new BiNode(6);
			tree->right()->right() = new BiNode(7);

			Assert::AreEqual(tree->left(), tree->search(2));
			Assert::AreEqual(tree->left()->right(), tree->search(5));

			Assert::IsTrue(tree->left() == tree->search(2));
			Assert::IsTrue(tree->left()->right() == tree->search(5));

			Assert::IsTrue(tree->left()->right()->isSame(tree->search(5)));

			Assert::AreEqual(7u, tree->count());

			Assert::AreEqual(3u, tree->height());
			Assert::AreEqual(1u, tree->left()->right()->height());

			delete tree;
		}

		TEST_METHOD(BiTreeTraverse_0)
		{
			typedef BiNode_<int> BiNode;

			BiNode * tree = nullptr;

			std::string tret;

			traverseR(tree, PRE)([&tret](decltype(tree) _node){ tret += std::to_string(_node->value()); });
			Assert::AreEqual(tret.c_str(), "");

			tret.clear();
			traverseR(tree, IN)([&tret](decltype(tree) _node){ tret += std::to_string(_node->value()); });
			Assert::AreEqual(tret.c_str(), "");

			tret.clear();
			traverseR(tree, POST)([&tret](decltype(tree) _node){ tret += std::to_string(_node->value()); });
			Assert::AreEqual(tret.c_str(), "");

			tret.clear();
			traverseNR(tree, PRE)([&tret](decltype(tree) _node){ tret += std::to_string(_node->value()); });
			Assert::AreEqual(tret.c_str(), "");

			tret.clear();
			traverseNR(tree, IN)([&tret](decltype(tree) _node){ tret += std::to_string(_node->value()); });
			Assert::AreEqual(tret.c_str(), "");

			tret.clear();
			traverseNR(tree, POST)([&tret](decltype(tree) _node){ tret += std::to_string(_node->value()); });
			Assert::AreEqual(tret.c_str(), "");

			tret.clear();
			traverseL(tree)([&tret](decltype(tree) _node){ tret += std::to_string(_node->value()); });
			Assert::AreEqual(tret.c_str(), "");

			delete tree;
		}

		TEST_METHOD(BiTreeTraverse_1)
		{
			typedef BiNode_<int> BiNode;

			BiNode * tree = new BiNode(3);

			std::string tret;

			traverseR(tree, PRE)([&tret](decltype(tree) _node){ tret += std::to_string(_node->value()); });
			Assert::AreEqual(tret.c_str(), "3");

			tret.clear();
			traverseR(tree, IN)([&tret](decltype(tree) _node){ tret += std::to_string(_node->value()); });
			Assert::AreEqual(tret.c_str(), "3");

			tret.clear();
			traverseR(tree, POST)([&tret](decltype(tree) _node){ tret += std::to_string(_node->value()); });
			Assert::AreEqual(tret.c_str(), "3");

			tret.clear();
			traverseNR(tree, PRE)([&tret](decltype(tree) _node){ tret += std::to_string(_node->value()); });
			Assert::AreEqual(tret.c_str(), "3");

			tret.clear();
			traverseNR(tree, IN)([&tret](decltype(tree) _node){ tret += std::to_string(_node->value()); });
			Assert::AreEqual(tret.c_str(), "3");

			tret.clear();
			traverseNR(tree, POST)([&tret](decltype(tree) _node){ tret += std::to_string(_node->value()); });
			Assert::AreEqual(tret.c_str(), "3");

			tret.clear();
			traverseL(tree)([&tret](decltype(tree) _node){ tret += std::to_string(_node->value()); });
			Assert::AreEqual(tret.c_str(), "3");

			delete tree;
		}

		TEST_METHOD(BiTreeTraverse_a)
		{
			typedef BiNode_<int> BiNode;

			BiNode * tree = new BiNode(1);
			tree->left() = new BiNode(2);

			tree->left()->left() = new BiNode(3);
			tree->left()->left()->left() = new BiNode(4);
			tree->left()->left()->left()->left() = new BiNode(5);

			std::string tret;

			traverseR(tree, PRE)([&tret](decltype(tree) _node){ tret += std::to_string(_node->value()); });
			Assert::AreEqual(tret.c_str(), "12345");

			tret.clear();
			traverseR(tree, IN)([&tret](decltype(tree) _node){ tret += std::to_string(_node->value()); });
			Assert::AreEqual(tret.c_str(), "54321");

			tret.clear();
			traverseR(tree, POST)([&tret](decltype(tree) _node){ tret += std::to_string(_node->value()); });
			Assert::AreEqual(tret.c_str(), "54321");

			tret.clear();
			traverseNR(tree, PRE)([&tret](decltype(tree) _node){ tret += std::to_string(_node->value()); });
			Assert::AreEqual(tret.c_str(), "12345");

			tret.clear();
			traverseNR(tree, IN)([&tret](decltype(tree) _node){ tret += std::to_string(_node->value()); });
			Assert::AreEqual(tret.c_str(), "54321");

			tret.clear();
			traverseNR(tree, POST)([&tret](decltype(tree) _node){ tret += std::to_string(_node->value()); });
			Assert::AreEqual(tret.c_str(), "54321");

			tret.clear();
			traverseL(tree)([&tret](decltype(tree) _node){ tret += std::to_string(_node->value()); });
			Assert::AreEqual(tret.c_str(), "12345");

			delete tree;
		}

		TEST_METHOD(BiTreeTraverse_b)
		{
			typedef BiNode_<int> BiNode;

			BiNode * tree = new BiNode(1);
			tree->right() = new BiNode(2);

			tree->right()->right() = new BiNode(3);
			tree->right()->right()->right() = new BiNode(4);
			tree->right()->right()->right()->right() = new BiNode(5);

			std::string tret;

			traverseR(tree, PRE)([&tret](decltype(tree) _node){ tret += std::to_string(_node->value()); });
			Assert::AreEqual(tret.c_str(), "12345");

			tret.clear();
			traverseR(tree, IN)([&tret](decltype(tree) _node){ tret += std::to_string(_node->value()); });
			Assert::AreEqual(tret.c_str(), "12345");

			tret.clear();
			traverseR(tree, POST)([&tret](decltype(tree) _node){ tret += std::to_string(_node->value()); });
			Assert::AreEqual(tret.c_str(), "54321");

			tret.clear();
			traverseNR(tree, PRE)([&tret](decltype(tree) _node){ tret += std::to_string(_node->value()); });
			Assert::AreEqual(tret.c_str(), "12345");

			tret.clear();
			traverseNR(tree, IN)([&tret](decltype(tree) _node){ tret += std::to_string(_node->value()); });
			Assert::AreEqual(tret.c_str(), "12345");

			tret.clear();
			traverseNR(tree, POST)([&tret](decltype(tree) _node){ tret += std::to_string(_node->value()); });
			Assert::AreEqual(tret.c_str(), "54321");

			tret.clear();
			traverseL(tree)([&tret](decltype(tree) _node){ tret += std::to_string(_node->value()); });
			Assert::AreEqual(tret.c_str(), "12345");

			delete tree;
		}

		TEST_METHOD(BiTreeTraverse_c)
		{
			typedef BiNode_<int> BiNode;

			BiNode * tree = new BiNode(1);
			tree->left() = new BiNode(2);
			tree->right() = new BiNode(3);

			tree->left()->left() = new BiNode(4);
			tree->left()->right() = new BiNode(5);

			tree->right()->left() = new BiNode(6);
			tree->right()->right() = new BiNode(7);

			std::string tret;

			traverseR(tree, PRE)([&tret](decltype(tree) _node){ tret += std::to_string(_node->value()); });
			Assert::AreEqual(tret.c_str(), "1245367");

			tret.clear();
			traverseR(tree, IN)([&tret](decltype(tree) _node){ tret += std::to_string(_node->value()); });
			Assert::AreEqual(tret.c_str(), "4251637");

			tret.clear();
			traverseR(tree, POST)([&tret](decltype(tree) _node){ tret += std::to_string(_node->value()); });
			Assert::AreEqual(tret.c_str(), "4526731");

			tret.clear();
			traverseNR(tree, PRE)([&tret](decltype(tree) _node){ tret += std::to_string(_node->value()); });
			Assert::AreEqual(tret.c_str(), "1245367");

			tret.clear();
			traverseNR(tree, IN)([&tret](decltype(tree) _node){ tret += std::to_string(_node->value()); });
			Assert::AreEqual(tret.c_str(), "4251637");

			tret.clear();
			traverseNR(tree, POST)([&tret](decltype(tree) _node){ tret += std::to_string(_node->value()); });
			Assert::AreEqual(tret.c_str(), "4526731");

			tret.clear();
			traverseL(tree)([&tret](decltype(tree) _node){ tret += std::to_string(_node->value()); });
			Assert::AreEqual(tret.c_str(), "1234567");

			delete tree;
		}

		TEST_METHOD(BiTreeTraverse_d)
		{
			typedef BiNode_<char> BiNode;

			BiNode * tree = new BiNode('1');
			tree->left() = new BiNode('2');
			tree->right() = new BiNode('3');

			tree->left()->left() = new BiNode('4');
			tree->left()->right() = new BiNode('5');

			tree->right()->left() = new BiNode('6');
			tree->right()->right() = new BiNode('7');

			tree->left()->right()->right() = new BiNode('8');
			tree->left()->right()->right()->left() = new BiNode('A');

			tree->right()->left()->right() = new BiNode('9');
			tree->right()->left()->right()->right() = new BiNode('B');

			std::string tret;

			traverseR(tree, PRE)([&tret](decltype(tree) _node){ tret += _node->value(); });
			Assert::AreEqual(tret.c_str(), "12458A369B7");

			tret.clear();
			traverseR(tree, IN)([&tret](decltype(tree) _node){ tret += _node->value(); });
			Assert::AreEqual(tret.c_str(), "425A8169B37");

			tret.clear();
			traverseR(tree, POST)([&tret](decltype(tree) _node){ tret += _node->value(); });
			Assert::AreEqual(tret.c_str(), "4A852B96731");

			tret.clear();
			traverseNR(tree, PRE)([&tret](decltype(tree) _node){ tret += _node->value(); });
			Assert::AreEqual(tret.c_str(), "12458A369B7");

			tret.clear();
			traverseNR(tree, IN)([&tret](decltype(tree) _node){ tret += _node->value(); });
			Assert::AreEqual(tret.c_str(), "425A8169B37");

			tret.clear();
			traverseNR(tree, POST)([&tret](decltype(tree) _node){ tret += _node->value(); });
			Assert::AreEqual(tret.c_str(), "4A852B96731");

			tret.clear();
			traverseL(tree)([&tret](decltype(tree) _node){ tret += _node->value(); });
			Assert::AreEqual(tret.c_str(), "123456789AB");

			delete tree;
		}

		template<typename T>
		void choice_branch(BiNode_<T> * _node, std::function<T(void)> _rando)
		{
			auto a = _rando();
			auto b = _rando();

			if (a > b)
			{
				_node->left() = new BiNode_<T>(_rando());

			}
			else
			{
				_node->right() = new BiNode_<T>(_rando());
			}
		}

		TEST_METHOD(BiTreeTraverse_f)
		{
			srand((unsigned int)time(NULL));

			typedef BiNode_<char> BiNode;
			typedef std::function<char(void)> randoFunc;

			// random from 1 ~ 10
			randoFunc digi_ran  = [](){ return char(rand() % 10 + '0'); };
			randoFunc ALPHA_ran = [](){ return char(rand() % 26 + 'A'); };
			randoFunc alpha_ran = [](){ return char(rand() % 26 + 'a'); };

			std::string seq;
			BiNode * tree = new BiNode(digi_ran());
			seq += tree->value();

			auto lv0 = tree;
			lv0->left() = new BiNode(alpha_ran());
			lv0->right() = new BiNode(ALPHA_ran());
			seq += lv0->left()->value();
			seq += lv0->right()->value();

			auto lv1l = lv0->left();
			auto lv1r = lv0->right();

			lv1l->left() = new BiNode(digi_ran());
			lv1l->right() = new BiNode(ALPHA_ran());
			seq += lv1l->left()->value();
			seq += lv1l->right()->value();

			auto lv1 = lv1r;
			choice_branch(lv1, digi_ran);

			auto lv2 = nullptr == lv1->right() ? lv1->left() : lv1->right();
			choice_branch(lv2, ALPHA_ran);
			seq += lv2->value();

			auto lv3 = nullptr == lv2->right() ? lv2->left() : lv2->right();
			choice_branch(lv3, alpha_ran);
			seq += lv3->value();

			auto lv4 = nullptr == lv3->right() ? lv3->left() : lv3->right();
			choice_branch(lv4, ALPHA_ran);
			seq += lv4->value();

			auto lv5 = nullptr == lv4->right() ? lv4->left() : lv4->right();
			seq += lv5->value();

			{
				std::string r_ret;
				std::string nr_ret;

				traverseR(tree, PRE)([&r_ret](decltype(tree) _node){ r_ret += _node->value(); });
				traverseNR(tree, PRE)([&nr_ret](decltype(tree) _node){ nr_ret += _node->value(); });

				Assert::AreEqual(nr_ret, r_ret);
			}

			{
				std::string r_ret;
				std::string nr_ret;

				traverseR(tree, IN)([&r_ret](decltype(tree) _node){ r_ret += _node->value(); });
				traverseNR(tree, IN)([&nr_ret](decltype(tree) _node){ nr_ret += _node->value(); });

				Assert::AreEqual(nr_ret, r_ret);
			}

			{
				std::string r_ret;
				std::string nr_ret;

				traverseR(tree, POST)([&r_ret](decltype(tree) _node){ r_ret += _node->value(); });
				traverseNR(tree, POST)([&nr_ret](decltype(tree) _node){ nr_ret += _node->value(); });

				Assert::AreEqual(nr_ret, r_ret);
			}

			{
				std::string l_ret;

				traverseL(tree)([&l_ret](decltype(tree) _node){ l_ret += _node->value(); });
				Assert::AreEqual(seq, l_ret);
			}

			delete tree;
		}

		TEST_METHOD(BiTreeIterator)
		{
			typedef BiNode_<char> BiNode;

			BiNode * tree = new BiNode('1');
			tree->left() = new BiNode('2');
			tree->right() = new BiNode('3');

			tree->left()->left() = new BiNode('4');
			tree->left()->right() = new BiNode('5');

			tree->right()->left() = new BiNode('6');
			tree->right()->right() = new BiNode('7');

			tree->left()->right()->right() = new BiNode('8');
			tree->left()->right()->right()->left() = new BiNode('A');

			tree->right()->left()->right() = new BiNode('9');
			tree->right()->left()->right()->right() = new BiNode('B');

			std::string tret;
			traverseR(tree, IN)([&tret](decltype(tree) _node){ tret += _node->value(); });

			std::string itr_ret;
			for (auto itr = tree->begin(); itr != tree->end(); ++itr)
			{
				itr_ret += (*itr)->value();
			}
			Assert::AreEqual(tret, itr_ret);

			itr_ret.clear();
			for (auto itr = tree->cbegin(); itr != tree->cend(); ++itr)
			{
				itr_ret += (*itr)->value();
			}
			Assert::AreEqual(tret, itr_ret);


			delete tree;
		}
	};
}