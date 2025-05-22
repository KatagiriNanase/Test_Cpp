#define _CRT_SECURE_NO_WARNINGS

#include "Date.hpp"

using namespace std;


//获取月份天数
int Date::GetMonthDay(const int year,const int month) const
{
	static int days[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	int day = days[month];
	if (month == 2 && (year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		day += 1;

	return day;
}

//构造函数--- 1.以类名作为函数名 2.对象实例化时自动调用
Date::Date(int year, int month, int day)
	//初始化列表：成员变量用()进行初始化
	:_year(year)
	,_month(month)
	,_day(day)
{}

//拷贝构造函数	--如果没有实现这个拷贝构造函数，函数默认会实现一个按照对象一个字节一个字节复制的拷贝函数（浅拷贝
Date::Date(const Date& d)
{
	_year = d._year;
	_month = d._month;
	_day = d._day;
}

//显示日期函数
void Date::ShowDate()
{
	cout << _year << '-' << _month << '-' << _day << endl;
}

//d1==d2 d1.operator(d2)
bool Date::operator==(const Date& d)
{
	return this->_year == d._year
		&& this->_month == d._month
		&& this->_day == d._day;
}

bool Date::operator!=(const Date& d)
{
	return !(*this == d);
}

//operator<
bool Date::operator<(const Date& d)
{
	if (this->_year < d._year)
		return true;
	else if (this->_year == d._year && this->_month < d._month)
		return true;
	else if (this->_year == d._year && this->_month == d._month && this->_day < d._day)
		return true;
	else
		return false;
}

//operator<=
bool Date::operator<=(const Date& d)
{
	return *this < d || *this == d;
}

//operator>
bool Date::operator>(const Date& d)
{
	return !(*this <= d);
}

//operator>=
bool Date::operator>=(const Date& d)
{
	return !(*this < d);
}

//operator+
Date Date::operator+(const int day) const
{
	Date d(*this);
	d._day += day;
	while (d._day > GetMonthDay(_year, _month))
	{
		d._day -= GetMonthDay(d._year, d._month);
		d._month += 1;
		if (d._month == 13)
		{
			d._year += 1;
			d._month = 1;
		}
	}

	return d;
}

//operator+=
Date& Date::operator+=(int day)
{
	_day += day;
	while (_day > GetMonthDay(_year, _month))
	{
		_day -= GetMonthDay(_year, _month);
		_month += 1;
		if (_month == 13)
		{
			_year += 1;
			_month = 1;
		}
	}

	return *this;
}

/* 如果没有定义这个赋值重载，编译器会默认实现一个赋值函数 */
Date& Date::operator=(const Date& d)
{
	if (this != &d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}

	//出了函数还在，使用引用
	return *this;
}

//析构函数
//~Date();

// Date::~Date()
// {
// 	cout << "析构函数测试" << endl;
// }

