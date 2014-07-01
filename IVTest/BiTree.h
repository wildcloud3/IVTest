#pragma once

#include <cstdlib>
#include <queue>
#include <functional>
#include <stack>
#include <queue>
#include <set>
#include <memory>

template<typename T>
class BiNode_;

// deprecated, re-impl of the inner structure of lambda
template<typename T>
struct traverser
{
	BiNode_<T> * const m_tree;

	typedef std::function<void(decltype(m_tree) const)> ApplierFunctor;

	enum order : char {
		PRE = 0,
		IN,
		POST
	};

	order m_order;

	traverser(BiNode_<T> * const _tree, order _order = IN) : m_tree(_tree), m_order(_order) {}

	void operator () (ApplierFunctor _applier)
	{
		if (m_order == PRE) _applier(m_tree);

		if (nullptr != m_tree->left())
		{
			traverser(m_tree->left(), m_order)(_applier);
		}

		if (m_order == IN) _applier(m_tree);

		if (nullptr != m_tree->right())
		{
			traverser(m_tree->right(), m_order)(_applier);
		}

		if (m_order == POST) _applier(m_tree);
	}
};

enum order : char {
	PRE = 0,
	IN,
	POST
};

template <typename T>
using ApplierFunctor = std::function<void (BiNode_<T> *)>;

template <typename T>
using ApplierDelegate = std::function<void (ApplierFunctor<T>)>;

template<typename T>
ApplierDelegate<T> traverseR(BiNode_<T> * _tree, order _order = IN)
{
	return [_tree, _order](ApplierFunctor<T> _applier){

		if (nullptr == _tree) return;

		if (_order == PRE) _applier(_tree);

		traverseR(_tree->left(), _order)(_applier);

		if (_order == IN) _applier(_tree);

		traverseR(_tree->right(), _order)(_applier);

		if (_order == POST) _applier(_tree);
	};
}

template<typename T>
ApplierDelegate<T> traverseNR(BiNode_<T> * _tree, order _order = IN)
{
	auto pre_ = [_tree](ApplierFunctor<T> _applier){
		std::stack<decltype(_tree)> s;

		auto node = _tree;

		if (nullptr != node)
		{
			s.push(node);
		}

		while (!s.empty())
		{
			auto top = s.top();
			s.pop();

			_applier(top);

			if (nullptr != top->right())
			{
				s.push(top->right());
			}

			if (nullptr != top->left())
			{
				s.push(top->left());
			}
		}
	};

	auto in_  = [_tree](ApplierFunctor<T> _applier){
		std::stack<decltype(_tree)> s;

		auto node = _tree;

		do 
		{
			while (nullptr != node)
			{
				s.push(node);
				node = node->left();
			}

			while (!s.empty())
			{
				auto top = s.top();
				s.pop();

				_applier(top);

				if (nullptr != top->right())
				{
					node = top->right();
					break;
				}
			}
		} while (!s.empty() || nullptr != node);
	};

	auto post_ = [_tree](ApplierFunctor<T> _applier){
		std::stack<decltype(_tree)> s;
		std::set<decltype(_tree)> touched;

		auto node = _tree;

		do 
		{
			while (nullptr != node)
			{
				s.push(node);
				node = node->left();
			}

			while (!s.empty())
			{
				auto top = s.top();

				if (nullptr != top->right() && touched.count(top) == 0)
				{
					touched.insert(top);
					node = top->right();
					break;
				}

				s.pop();
				_applier(top);

			}
		} while (!s.empty() || node != nullptr);
	};

	if (_order == PRE) return pre_;
	else if (_order == IN) return in_;
	else if (_order == POST) return post_;
	else return pre_;
}

template<typename T>
ApplierDelegate<T> traverseL(BiNode_<T> * _tree)
{
	return [_tree](ApplierFunctor<T> _applier){
		std::queue<decltype(_tree)> q;

		auto node = _tree;

		if (nullptr != node)
		{
			q.push(node);
		}

		while (!q.empty())
		{
			auto first = q.front();
			q.pop();

			_applier(first);

			if (nullptr != first->left())
			{
				q.push(first->left());
			}

			if (nullptr != first->right())
			{
				q.push(first->right());
			}
		}
	};
}

template <typename T>
class BiNode_
{
public:
	typedef T value_type;
	typedef BiNode_<value_type> _Myt;

public:
	BiNode_(value_type _val = value_type()) : m_left(nullptr), m_right(nullptr), m_val(_val) {}

	BiNode_(_Myt const &_rhs) : BiNode_() { deep_copy(_rhs); }

	BiNode_(_Myt &&_rhs) { swap(_rhs); }

	BiNode_& operator = (_Myt _rhs)
	{
		swap(_rhs);
		return *this;
	}

	~BiNode_()
	{
		if (nullptr != m_left)  delete m_left;
		if (nullptr != m_right) delete m_right;
	}

	value_type const value() const { return m_val; }
	value_type& value() { return m_val; }
	_Myt const * left() const { return m_left; }
	_Myt*& left() { return m_left; }
	_Myt const * right() const { return m_right; }
	_Myt*& right() { return m_right; }

	_Myt& operator = (value_type _val) { m_val = _val; }

	bool isFull() const
	{
		auto ret = false;

		return ret;
	}

	bool isComplete() const
	{
		auto ret = false;

		return ret;
	}

	_Myt * search(value_type const _val)
	{
		if (m_val == _val) return this;

		if (nullptr != m_left)
		{
			auto ret = m_left->search(_val);

			if (nullptr != ret) return ret;
		}

		if (nullptr != m_right)
		{
			return m_right->search(_val);
		}

		return nullptr;
	}

	size_t count() const 
	{
		size_t lc = 0;
		size_t rc = 0;

		if (nullptr != m_left)  lc = m_left->count();
		if (nullptr != m_right) rc = m_right->count();

		return lc + rc + 1;
	}

	size_t height() const
	{
		size_t lh = 1;
		size_t rh = 1;

		if (nullptr != m_left)  lh += m_left->height();
		if (nullptr != m_right) rh += m_right->height();

		return std::max(lh, rh);
	}

	bool isEqual(_Myt const * const _rhs) const
	{
		if (this == _rhs)
		{
			return true;
		}

		auto _isequal = (m_val == _rhs->m_val);
		_isequal &&= (nullptr != m_left) && (nullptr != _rhs->m_left) && m_left->isEqual(_rhs->m_left);
		return _isequal && nullptr != m_right && nullptr != _rhs->m_right && m_right->isEqual(_rhs->m_right);
	}

	bool isSame(_Myt const * const _rhs) const
	{
		if (this == _rhs)
		{
			return true;
		}

		auto _isequal = nullptr != m_left && nullptr != _rhs->m_left && m_left->isSame(_rhs->m_left);
		return _isequal && nullptr != m_right && nullptr != _rhs->m_right && m_right->isSame(_rhs->m_right);
	}

	bool operator == (_Myt const * const _rhs) const
	{
		return isEqual(_rhs);
	}

	void print_out() const
	{
		std::queue< _Myt const* > q;
		q.push(this);
		printf("BiNode:\n");
		while (!q.empty())
		{
			auto qtop = q.front(); q.pop();

			printf("%d", qtop->value());

			if (nullptr != qtop->m_left) q.push(qtop->m_left);
			if (nullptr != qtop->m_right) q.push(qtop->m_right);

			printf("\n");
		}
	}

public:
	template <typename T>
	class Iterator
	{
	public:
		Iterator(T * const _node = nullptr) { recursive_add_left(_node); }
		Iterator(Iterator const &_rhs) { m_s = _rhs.m_s; }
		Iterator(Iterator &&_rhs) { swap(_rhs); }

		Iterator& operator = (Iterator _rhs)
		{
			swap(_rhs);
			return *this;
		}

		bool operator == (Iterator const &_rhs) { return **this == *_rhs; }
		bool operator != (Iterator const &_rhs) { return **this != *_rhs; }

		Iterator& operator ++ ()
		{
			this->next();
			return *this;
		}

		Iterator const operator ++ (int)
		{
			auto tmp = *this;
			this->next();
			return tmp;
		}

		T * operator*() const { return m_s.empty() ? nullptr : m_s.top(); }

	private:
		void next() 
		{
			if (m_s.empty()) return;

			auto top = m_s.top();
			m_s.pop();

			if (nullptr != top->m_right)
			{
				recursive_add_left(top->m_right);
			}
		}

		void recursive_add_left(T * _node)
		{
			while (nullptr != _node)
			{
				m_s.push(_node);
				_node = _node->m_left;
			}
		}

		void swap(Iterator &_rhs) { std::swap(m_s, _rhs.m_s); }

		std::stack<T *> m_s;
	};


	Iterator<_Myt> begin() { return Iterator<_Myt>(this); }
	Iterator<_Myt> end()   { return Iterator<_Myt>(); }

	Iterator<_Myt const> cbegin() const { return Iterator<_Myt const>(this); }
	Iterator<_Myt const> cend()   const { return Iterator<_Myt const>(); }

private:
	void swap(_Myt &_rhs)
	{
		std::swap(m_left, _rhs.m_left);
		std::swap(m_right, _rhs.m_right);
		std::swap(m_val, _rhs.m_val);
	}

	// only used in copy-constructor
	void deep_copy(_Myt const &_rhs)
	{
		if (nullptr != _rhs.m_left)
		{ 
			m_left = new _Myt(*_rhs.m_left);
		}
		if (nullptr != _rhs.m_right)
		{
			m_right = new _Myt(*_rhs.m_right);
		}
		m_val = _rhs.m_val;
	}

private:
	_Myt *m_left;
	_Myt *m_right;
	
	value_type m_val;
};

