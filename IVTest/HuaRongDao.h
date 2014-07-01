#pragma once

#include <vector>
#include <map>
#include <algorithm>

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

	explicit Layout_(char const * _data)
	{
		m_data[rows()*cols()] = '\0';
		memcpy_s(m_data, rows()*cols(), _data, rows()*cols());

		parseBlocks();
	}

	Layout_(_Myt const &_rhs) : Layout_(_rhs.m_data)
	{
		m_blocks.swap(std::map<char, Block>(_rhs.m_blocks));
	}
	Layout_(_Myt &&_rhs) { swap(_rhs); }

	_Myt& operator = (_Myt _rhs)
	{
		swap(_rhs);
		return *this;
	}

	char operator () (int _i0, int _i1) const { return m_data[_i0*cols() + _i1]; } 
	char operator [] (int _idx) const { return m_data[_idx]; } 

	bool operator < (_Myt const &_rhs) const
	{
		return strcmp(m_data, _rhs.m_data) < 0;
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
		
		if (!curr_blk.BoundaryCheck(rows(), cols())) return false;

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
		ret.m_blocks[_block.first] = _block.second.MoveDown();
		return ret;
	}

	template <typename pariT>
	_Myt MoveUp(pariT _block)
	{
		auto ret = _Myt(*this);
		ret.m_blocks[_block.first] = _block.second.MoveUp();
		return ret;
	}

	template <typename pariT>
	_Myt MoveLeft(pariT _block)
	{
		auto ret = _Myt(*this);
		ret.m_blocks[_block.first] = _block.second.MoveLeft();
		return ret;
	}

	template <typename pariT>
	_Myt MoveRight(pariT _block)
	{
		auto ret = _Myt(*this);
		ret.m_blocks[_block.first] = _block.second.MoveRight();
		return ret;
	}

	std::vector<_Myt> moves()
	{
		std::vector<_Myt> ret;
		for (auto block : m_blocks)
		{
			_Myt tmp = MoveDown(block);
			if (tmp.isValid(block.first)) ret.push_back(tmp);

			tmp = MoveUp(block);
			if (tmp.isValid(block.first)) ret.push_back(tmp);

			tmp = MoveLeft(block);
			if (tmp.isValid(block.first)) ret.push_back(tmp);

			tmp = MoveRight(block);
			if (tmp.isValid(block.first)) ret.push_back(tmp);
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

		bool operator == (Point const &_rhs) const
		{
			return x == _rhs.x && y == _rhs.y;
		}
	};

	Block() {}

	explicit Block(Layout const &_layout, char const _id)
	{
		for (size_t r = 0; r < _layout.rows(); ++r)
			for (size_t c = 0; c < _layout.cols(); c++)
				if (_id == _layout(r, c)) m_pos.push_back({ r, c });
	}

	Block(Block const &_rhs) { m_pos.assign(_rhs.m_pos.begin(), _rhs.m_pos.end()); }
	Block(Block &&_rhs) { std::swap(m_pos, _rhs.m_pos); }

	Block& operator = (Block _rhs)
	{
		std::swap(m_pos, _rhs.m_pos);
		return *this;
	}

	Block& MoveDown()
	{
		for (auto &pos : m_pos) pos.y += 1;
		return *this;
	}

	Block& MoveUp()
	{
		for (auto &pos : m_pos) pos.y -= 1;
		return *this;
	}

	Block& MoveLeft()
	{
		for (auto &pos : m_pos) pos.x -= 1;
		return *this;
	}

	Block& MoveRight()
	{
		for (auto &pos : m_pos) pos.x += 1;
		return *this;
	}

	bool BoundaryCheck(size_t _rows, size_t _cols) const
	{
		for (auto &pos : m_pos)
		{
			if (pos.x < 0 || pos.y < 0 || pos.x >= (int)_cols || pos.y >= (int)_rows)
			{
				return false;
			}
		}
		return true;
	}

	bool IsOverlap(Block const &_rhs) const
	{
		return !std::any_of(m_pos.cbegin(), m_pos.cend(), [&_rhs](Point const &_pt){
			for (auto &rhs_pos : _rhs.m_pos)
				return _pt == rhs_pos;
			return false;
		});
	}

private:
	std::vector<Point> m_pos;
};

int solve(Layout const &_init);

}
