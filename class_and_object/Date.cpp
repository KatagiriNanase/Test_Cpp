#define _CRT_SECURE_NO_WARNINGS

#include "Date.hpp"

using namespace std;


//��ȡ�·�����
int Date::GetMonthDay(const int year,const int month) const
{
	static int days[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	int day = days[month];
	if (month == 2 && (year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		day += 1;

	return day;
}

//���캯��--- 1.��������Ϊ������ 2.����ʵ����ʱ�Զ�����
Date::Date(int year, int month, int day)
	//��ʼ���б���Ա������()���г�ʼ��
	:_year(year)
	,_month(month)
	,_day(day)
{}

//�������캯��	--���û��ʵ������������캯��������Ĭ�ϻ�ʵ��һ�����ն���һ���ֽ�һ���ֽڸ��ƵĿ���������ǳ����
Date::Date(const Date& d)
{
	_year = d._year;
	_month = d._month;
	_day = d._day;
}

//��ʾ���ں���
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

/* ���û�ж��������ֵ���أ���������Ĭ��ʵ��һ����ֵ���� */
Date& Date::operator=(const Date& d)
{
	if (this != &d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}

	//���˺������ڣ�ʹ������
	return *this;
}

//��������
//~Date();

// Date::~Date()
// {
// 	cout << "������������" << endl;
// }

