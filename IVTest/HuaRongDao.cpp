#include "HuaRongDao.h"

#include <map>
#include <queue>
#include <set>

namespace HuaRongDao
{
	Layout __inner_solver(Layout const &_init, bool find_best = false)
	{
		std::set<Layout> seen;
		std::queue<Layout> q;

		seen.insert(_init);
		q.push(_init);

		Layout ret;

		while (!q.empty())
		{
			auto curr_layout = q.front();
			q.pop();

			if (curr_layout.isSolved())
			{ 
				if (!find_best)
				{
					return curr_layout;
				}

				if (curr_layout.steps().size() < ret.steps().size() || ret.steps().empty())
				{
					printf("update best solution from %d steps to %d steps\n", ret.steps().size(), curr_layout.steps().size());
					ret = curr_layout;
				}
			}

			curr_layout.moves([&seen, &q](Layout const &_layout){
				auto ret = seen.insert(_layout);
				if (ret.second) q.push(_layout);
			});
		}

		printf("%d views seen\n", seen.size());
		return ret;
	};

	std::map<HuaRongDao::EMoveDir, std::string> dir_mapper = {
		{ HuaRongDao::DOWN,  "DOWN" },
		{ HuaRongDao::UP,    "UP" },
		{ HuaRongDao::LEFT,  "LEFT" },
		{ HuaRongDao::RIGHT, "RIGHT" }
	};

	void steps_printer(HuaRongDao::Layout::MvSteps _steps)
	{
		printf("Steps: \n");
		int idx = 0;
		while (!_steps.empty())
		{
			auto step = _steps.front();
			_steps.pop();

			printf("step %3d: [%c] move %s\n", ++idx, step.first, dir_mapper[step.second].c_str());
		}
		printf("There's %d steps in all to escape\n", idx);
	}

	Layout solve(Layout const &_init, bool _find_best /*= false*/, bool _print_steps /*= false*/)
	{
		auto ret = __inner_solver(_init, _find_best);

		if (_print_steps && ret.isSolved())
		{
			steps_printer(ret.steps());
		}

		return ret;
	}
}