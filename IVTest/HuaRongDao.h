#pragma once

#include <algorithm>
#include <functional>
#include <map>
#include <vector>

namespace HuaRongDao
{

class Block;

// should be initialized by a rows*cols char seq
template<size_t ROWS, size_t COLS>
class Layout_
{
public:
	inline size_t const rows() const { return ROWS; }
	inline size_t const cols() const { return COLS; }

	typedef Layout_<ROWS, COLS> _Myt;

	Layout_() { m_data[rows()*cols()] = '\0'; }

	explicit Layout_(char const * _data) : Layout_()
	{
		memcpy_s(m_data, rows()*cols(), _data, rows()*cols());
		parseBlocks();
	}

	Layout_(_Myt const &_rhs) : Layout_()
	{
		memcpy_s(m_data, rows()*cols(), _rhs.m_data, rows()*cols());
		m_blocks.swap(std::map<char, Block>(_rhs.m_blocks));
	}
	Layout_(_Myt &&_rhs) { swap(_rhs); }

	_Myt& operator = (_Myt _rhs)
	{
		swap(_rhs);
		return *this;
	}

	char operator () (int _i0, int _i1) const { return m_data[_i0*cols() + _i1]; } 
	char& operator () (int _i0, int _i1) { return m_data[_i0*cols() + _i1]; } 
	char operator [] (int _idx) const { return m_data[_idx]; } 

	bool operator < (_Myt const &_rhs) const { return strcmp(m_data, _rhs.m_data) < 0; }

	char const * to_string() const { return m_data; }

	_Myt& Render()
	{
		std::fill_n(m_data, rows()*cols(), '0');
		for (auto  block : m_blocks)
		{
			block.second.Render(*this, block.first);
		}
		return *this;
	}

	// the four square front of door should be same
	//	1. always square
	//  2. maximum: _|||||||_, only except the most outside two
	bool isSolved() const
	{
		auto row_id = rows() - 1;
		auto base = (*this)(row_id, 1);
		for (size_t j = row_id; j > cols() - 2; --j)
		{
			for (size_t i = 1; i < cols() - 1; ++i)
			{
				if (base != (*this)(j, i))
					return false;
			}
		}

		return true;
	}

	bool isValid(char _block_id) const
	{
		auto &curr_blk = m_blocks.at(_block_id);
		
		if (curr_blk.IsCrossBoundary(*this)) return false;

		//overlap check
		for (auto &block : m_blocks)
			if (curr_blk.IsOverlap(block.second) && _block_id != block.first)
				return false;

		return true;
	}

	template <typename pariT>
	_Myt MoveDown(pariT _block)
	{
		auto ret = _Myt(*this);
		ret.m_blocks[_block.first] = _block.second.Move(Block::DOWN);
		return ret;
	}

	template <typename pariT>
	_Myt MoveUp(pariT _block)
	{
		auto ret = _Myt(*this);
		ret.m_blocks[_block.first] = _block.second.Move(Block::UP);
		return ret;
	}

	template <typename pariT>
	_Myt MoveLeft(pariT _block)
	{
		auto ret = _Myt(*this);
		ret.m_blocks[_block.first] = _block.second.Move(Block::LEFT);
		return ret;
	}

	template <typename pariT>
	_Myt MoveRight(pariT _block)
	{
		auto ret = _Myt(*this);
		ret.m_blocks[_block.first] = _block.second.Move(Block::RIGHT);
		return ret;
	}

	std::vector<_Myt> moves()
	{
		std::vector<_Myt> ret;
		for (auto block : m_blocks)
		{
			_Myt tmp = MoveDown(block);
			if (tmp.isValid(block.first)) ret.push_back(tmp.Render());

			tmp = MoveUp(block);
			if (tmp.isValid(block.first)) ret.push_back(tmp.Render());

			tmp = MoveLeft(block);
			if (tmp.isValid(block.first)) ret.push_back(tmp.Render());

			tmp = MoveRight(block);
			if (tmp.isValid(block.first)) ret.push_back(tmp.Render());
		}
		return ret;
	}

	template <typename Func>
	void moves(Func _func)
	{

	}

private:
	void parseBlocks()
	{
		m_blocks.clear();

		for (size_t r = 0; r < rows(); ++r)
		{
			for (size_t c = 0; c < cols(); c++)
			{
				auto id = (*this)(r, c);
				if (id != '0' && m_blocks.count(id) == 0)
				{
					m_blocks[id] = Block(*this, id);
				}
			}
		}
	}

	void swap(_Myt &_rhs)
	{
		std::swap(m_data, _rhs.m_data);
		std::swap(m_blocks, _rhs.m_blocks);
	}
	char m_data[ROWS*COLS+1];

	std::map<char, Block> m_blocks;
};

typedef Layout_<5, 4> Layout;

class Block
{
public:
	struct Point
	{
		int x;
		int y;

		Point(int const _x, int const _y) : x(_x), y(_y) {}
		Point(size_t const _x, size_t const _y) : x(_x), y(_y) {}

		bool operator <  (Point const &_rhs) const { return x < _rhs.x || (x == _rhs.x && y < _rhs.y); }
		bool operator == (Point const &_rhs) const { return x == _rhs.x && y == _rhs.y; }
	};

	enum EMoveDir : char
	{
		UP = 0,
		DOWN,
		LEFT,
		RIGHT
	};

	Block() {}
	explicit Block(Layout const &_layout, char const _id)
	{
		for (size_t r = 0; r < _layout.rows(); ++r)
			for (size_t c = 0; c < _layout.cols(); c++)
				if (_id == _layout(r, c)) m_pos.push_back({ c, r });
		std::sort(m_pos.begin(), m_pos.end());
	}

	Block(Block const &_rhs) { m_pos.assign(_rhs.m_pos.begin(), _rhs.m_pos.end()); }
	Block(Block &&_rhs) { std::swap(m_pos, _rhs.m_pos); }

	Block& operator = (Block _rhs)
	{
		std::swap(m_pos, _rhs.m_pos);
		return *this;
	}
	Point const & operator[](int _idx) { return m_pos[_idx]; }

	bool operator == (Block const &_rhs) const
	{
		return m_pos.size() == _rhs.size() 
			&& std::equal(m_pos.cbegin(), m_pos.cend(), _rhs.m_pos.cbegin());
	}

	size_t size() const { return m_pos.size(); }

	Block& Move(EMoveDir _dir)
	{
		std::function<void(Point&)> mover[] = {
			[](Point &_pt){ _pt.y -= 1; },
			[](Point &_pt){ _pt.y += 1; },
			[](Point &_pt){ _pt.x -= 1; },
			[](Point &_pt){ _pt.x += 1; } };

		std::for_each(m_pos.begin(), m_pos.end(), mover[_dir]);

		return *this;
	}

	// if cross boundary, return true
	bool IsCrossBoundary(Layout const &_layout) const
	{
		int cols = _layout.cols();
		int rows = _layout.rows();

		auto checker = [&](Point const &_pt){
			return _pt.x < 0 || _pt.y < 0 || _pt.x >= cols || _pt.y >= rows;
		};

		return std::any_of(m_pos.cbegin(), m_pos.cend(), checker);
	}

	bool IsOverlap(Block const &_rhs) const
	{
		auto checker = [&_rhs](Point const &_pt){
			auto innerChecker = [&_pt](Point const &_ipt){
				return _ipt == _pt;
			};
			return std::any_of(_rhs.m_pos.cbegin(), _rhs.m_pos.cend(), innerChecker);
		};
		return std::any_of(m_pos.cbegin(), m_pos.cend(), checker);
	}

	void Render(Layout & _canvas, char const _val) const
	{
		if (IsCrossBoundary(_canvas)) return;

		auto rendor = [&_canvas, &_val](Point const &_pt){
			_canvas(_pt.y, _pt.x) = _val;
		};

		std::for_each(m_pos.cbegin(), m_pos.cend(), rendor);
	}

private:
	std::vector<Point> m_pos;
};

int solve(Layout const &_init);

}
