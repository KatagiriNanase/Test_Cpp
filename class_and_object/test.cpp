#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

/* 类的函数存储于内存中的代码区，不会存放于类内 */
class Date
{
public:
	//构造函数->在对象构造时调用的函数
	Date(int year, int mouth, int day)
	{
		this->_year = year;
		this->_mouth = mouth;
		this->_day = day;
	}

	Date()//可以定义无参数的构造函数，可以与有参数的构造函数相共存（函数重载）
	{
		_year = 1;
		_mouth = 0;
		_day = 0;
	}
	void Init(int year, int mouth, int day)
	{
		_year = year;
		_mouth = mouth;
		_day = day;
	}

	void ShowInfo()
	{
		cout << _year << "-" << _mouth << "-" << _day << endl;
	}
	//私有成员变量
private:
	int _year;
	int _mouth;
	int _day;
};

int main()
{
	int arr[5] = { 1,2,3,4,5 };
	Date d1;//不能加括号Date d1()
	Date d2(2025,5,7);
	d2.ShowInfo();
	d1.ShowInfo();

	for (auto e : arr)
	{
		e *= 2;
		cout << e << ' ';
	}
	cout << endl;
	for (auto i : arr)
	{
		cout << i << ' ';
	}
	return 0;
}