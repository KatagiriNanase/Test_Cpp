#ifndef __STACK_HPP__
#define __STACK_HPP__

#include <new>

class Stack {
public :
	Stack(int size = 10);

	void push(int data);

	int pop(void);

private:
	int* _a;
	int _size;
	int _capacity;

};


#endif /* __STACK_H__ */
