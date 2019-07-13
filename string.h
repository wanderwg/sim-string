#pragma once
#include <string.h>
#include <algorithm>

namespace wg
{
	class string
	{
	public:
		typedef char* iterator;
	public:
		string(const char* str = "")
		{
			if (str == nullptr)
				str = "";
			_size = strlen(str);
			_str = new char[_size + 1];
			_capacity = _size;
		}
		string(size_t n, char ch)
			:_str(new char[n + 1])
			, _size(n)
			, _capacity(_size)
		{
			memset(_str, ch, _size);
			_str[_size] = '\0';
		}
		string(const string& s)
		{
			_capacity = s.capacity();
			_str = new char[_capacity + 1];
			strcpy(_str, s._str);
			_size = s.size();
		}
		string& operator=(const string& s)
		{
			if (this != &s)
			{
				char* pStr = new char[strlen(s._str) + 1];
				strcpy(pStr, s._str);
				delete[] _str;
				_str = pStr;
			}
			return *this;
		}
		////////////////////////////////////////////////////////
		//iterator
		iterator begin()
		{
			return _str;
		}
		iterator end()
		{
			return _str + _size;
		}

		///////////////////////////////////////////////////////
		//capacity
		size_t capacity()const
		{
			return _capacity;
		}
		size_t size()const
		{
			return _size;
		}
		bool empty()const
		{
			return _size == 0;
		}
		void clear()
		{
			_size = 0;
			_str[0] = '\0';
		}
		void resize(size_t newSize, char ch = 0)
		{
			size_t oldSize = size();
			if (newSize > oldSize)
			{
				if (newSize > capacity())
					reserve(newSize);
				memset(_str + _size, ch, newSize - oldSize);
			}
			_size = newSize;
			_str[_size] = '\0';
		}
		void reserve(size_t newCapacity)
		{
			if (newCapacity > capacity())
			{
				char* pStr = new char[newCapacity + 1];
				strcpy(pStr, _str);
				delete[] _str;
				_str = pStr;
				_capacity = newCapacity;
			}
		}
		////////////////////////////////////////////////////////////
		//access
		char& operator[](size_t index)
		{
			return _str[index];
		}
		const char& operator[](size_t index)const
		{
			return _str[index];
		}
		/////////////////////////////////////////////////////////////
		//modify
		string& operator+=(char ch)
		{
			push_back(ch);
			return *this;
		}
		string& operator+=(char* s)
		{
			int lsize = size();
			int rsize = strlen(s);
			char* pStr = new char[_size + rsize + 1];
			strcpy(pStr, _str);
			strcpy(pStr + lsize, s);
			delete[] _str;
			_str = pStr;
			_size = lsize + rsize;
			_capacity = lsize + rsize;
			return *this;
		}
		string& operator+=(const string& s)
		{
			int lsize = size();
			int rsize = s.size();
			char* pStr = new char[lsize + rsize + 1];
			strcpy(pStr, _str);
			strcpy(pStr + lsize, s._str);
			delete[] _str;
			_str = pStr;
			_size = lsize + rsize;
			_capacity = lsize + rsize;

			return *this;
		}
		void push_back(char ch)
		{
			if (_size == _capacity)
				reserve(_capacity * 2);
			_str[_size++] = ch;
		}
		string& append(char* str)
		{
			*this += string(str);
			return *this;
		}

		////////////////////////////////////////////////////
		//ÌØÊâ²Ù×÷
		const char* c_str()const
		{
			return _str;
		}
		size_t find(char ch, size_t pos = 0)
		{
			for (size_t i = pos; i < size(); ++i)
			{
				if (_str[i] == ch)
					return i;
			}
			return npos;
		}
		string substr(size_t pos = 0, size_t n = npos)
		{
			if (n == npos)
			{
				n = strlen(_str + pos);
			}
			string strRet(n + 1, 0);
			strncpy(strRet._str, _str + pos, n);
			return strRet;
		}
		bool operator>(const string& s)
		{
			if (strcmp(_str, s._str) > 0)
				return true;
			return false;
		}
		bool operator>=(const string& s);
		bool operator<(const string& s);
		bool operator<=(const string& s);
		bool operator==(const string& s);
		bool operator!=(const string& s);
	private:
		char* _str;
		size_t _capacity;
		size_t _size;
	public:
		const static size_t npos = -1;
	};

	ostream& operator<<(ostream& _cout, const string& s)
	{
		_cout << s.c_str();
		return _cout;
	}
}