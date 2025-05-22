#define _CRT_SECURE_NO_WARNINGS

#include "Stack.hpp"

Stack::Stack(int size = 10)
{
	_capacity= _size = size;
	_a = new int[size];
}

Stack::~Stack()
{
	delete(_a);
	_a = nullptr;
	_size = _capacity = 0;
}

int pop(void);