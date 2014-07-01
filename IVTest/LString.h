#pragma once

#include <cstring>
#include <cassert>
#include <utility>

class LString
{
public:
	LString(size_t _sz = 0) : m_size(_sz), m_data(new char[_sz+1])
	{
		m_data[_sz] = '\0';

		printf("LString::constructor default\n");
	}

	LString(char const * _str) : LString(strlen(_str))
	{
		strcpy(m_data, _str);

		printf("LString::constructor str\n");
	}

	LString(LString const &_rhs) : LString(_rhs.m_size)
	{
		strcpy(m_data, _rhs.m_data);

		printf("LString::constructor copy\n");
	}

	LString(LString &&_rhs) : LString()
	{
		swap(_rhs);

		printf("LString::constructor move\n");
	}

	// this could avoid self assignment check
	LString& operator = (LString _rhs)
	{
		swap(_rhs);
		printf("LString::operator =\n");
		return *this;
	}

	LString& operator = (LString &&_rhs)
	{
		swap(_rhs);
		printf("LString::operator = move\n");
		return *this;
	}

	~LString()
	{
		delete[] m_data;
		printf("LString::deconstructor\n");
	}

	size_t len() const { return m_size; }
	char const * c_str() const { return m_data; }
	void swap(LString &_rhs)
	{
		std::swap(m_size, _rhs.m_size);
		std::swap(this->m_data, _rhs.m_data);
	}

	bool operator == (LString const &_rhs) const
	{
		return 0 == strcmp(m_data, _rhs.m_data);
	}

	bool operator < (LString const &_rhs) const
	{
		return strcmp(m_data, _rhs.m_data) < 0;
	}
	
	bool operator > (LString const &_rhs) const
	{
		return !this->operator <(_rhs);
	}

	char operator[] (size_t _idx) const
	{
		assert(_idx < m_size);

		return m_data[_idx];
	}

private:
	size_t m_size;
	char * m_data;
};