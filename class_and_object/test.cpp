#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

/* ��ĺ����洢���ڴ��еĴ������������������� */
class Date
{
public:
	//���캯��->�ڶ�����ʱ���õĺ���
	Date(int year, int mouth, int day)
	{
		this->_year = year;
		this->_mouth = mouth;
		this->_day = day;
	}

	Date()//���Զ����޲����Ĺ��캯�����������в����Ĺ��캯���๲�棨�������أ�
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
	//˽�г�Ա����
private:
	int _year;
	int _mouth;
	int _day;
};

int main()
{
	int arr[5] = { 1,2,3,4,5 };
	Date d1;//���ܼ�����Date d1()
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