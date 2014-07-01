#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>

#include <vector>

#include "LString.h"
#include "SList.h"
#include "BiTree.h"

int main(int argc, char * argv[])
{
	LString s0;
	LString s1("hello");
	LString s3 = s1;

	std::vector<LString> lsVec(8);
	lsVec.push_back(s0);
	lsVec.push_back(s1);
	lsVec.push_back("good");

	typedef BiNode_<char> BiNode;

	//traverse(tree, POST)([](decltype(tree) _node){ printf("%d\n", _node->value()); });
	//traverser<int>(tree)([](decltype(tree) _node){ printf("%d\n", _node->value()); });
	//traverseNR(tree, POST)([&tret](decltype(tree) _node){ tret += std::to_string(_node->value()); });

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
	//traverseR(tree, PRE)([&tret](decltype(tree) _node){ std::cout << _node->value() << std::endl; });

	std::string itr_ret;
	for (auto itr = tree->begin(); itr != tree->end(); ++itr)
	{
		itr_ret += (*itr)->value();
	}


	printf(tret.c_str());

	delete tree;

	system("pause");
	return 0;
}