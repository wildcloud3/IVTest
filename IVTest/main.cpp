#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>

#include <vector>

#include "LString.h"
#include "SList.h"
#include "BiTree.h"
#include "HuaRongDao.h"

int main(int argc, char * argv[])
{
	char layout[] = {
		'1', '2', '2', '3',
		'1', '2', '2', '3',
		'4', '5', '5', '6',
		'4', '7', '8', '6',
		'9', '0', '0', 'A'
	};

	HuaRongDao::Layout iStart(layout);

	auto ret = HuaRongDao::solve(iStart);

	if (ret == 0)
	{
		printf("no solution\n");
	}
	else
	{
		printf("done, escaped\n");
	}

	system("pause");
	return 0;
}