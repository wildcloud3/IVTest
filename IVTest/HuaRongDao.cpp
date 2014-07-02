#include "HuaRongDao.h"

#include <queue>
#include <set>

namespace HuaRongDao
{
	int solve(Layout const &_init)
	{
		std::set<Layout> seen;
		std::queue<Layout> q;

		seen.insert(_init);
		q.push(_init);

		while (!q.empty())
		{
			//printf("Pending Q: %d\n", q.size());
			auto curr_layout = q.front();
			q.pop();

			if (curr_layout.isSolved()) { return 1; }

			// if with c++11, the return of moves could be optimised with rvalue
			/*
			for (auto nlayout : curr_layout.moves())
			{
				auto ret = seen.insert(nlayout);
				if (ret.second) q.push(nlayout);
			}
			*/

			curr_layout.moves([&seen, &q](Layout const &_layout){
				auto ret = seen.insert(_layout);
				if (ret.second) q.push(_layout);
			});
		}

		return 0;
	}
}