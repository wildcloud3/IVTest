#pragma once

template <typename value_type>
class SList
{
public:
	typedef struct Node_
	{
		Node_ *m_next;
		value_type m_val;
	} Node;

	SList(Node const * _node = NULL) : m_head(_node) {}

	SList(SList const &_slist) : SList(_slist.m_head) {}
	SList(SList &&_slist) : SList(_slist.m_head) {}

	~SList()
	{
		while (nullptr != m_head)
		{
			delete m_head->m_next;
		}
	}

	Node* append(Node * const _node)
	{
		return _node;
	}

	Node* insert(Node * const _node)
	{
		return _node;
	}

	bool empty() const { return NULL == m_head; }

private:
	Node *m_head;
};