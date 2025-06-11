#include "list.h"
#include <iostream>

using namespace std;

void test_list1()
{
    list<int> lt;
    for (size_t i = 0;i < 5;++i)
        lt.push_back(i);

    list<int>::iterator it = lt.begin();
    while (it != lt.end())
    {
        cout << *it << ' ';
        ++it;
    }

}

struct Date
{
    int _year = 0;
    int _month = 1;
    int _day = 1;
};

void test_list2()
{
    list<Date> lt;
    lt.push_back(Date());
    lt.push_back(Date());
    lt.push_back(Date());

    Date* p = new Date;

    list<Date>::iterator it = lt.begin();
    while (it != lt.end())
    {
        //原本应该是it->->_year，但是为了可读性，编译器特殊处理了一下
        cout << it->_year << '-' << it->_month << '-' << it->_day << endl;
        cout << (*it)._year << '-' << (*it)._month << '-' << (*it)._day << endl << endl;
        ++it;
    }

}

int main()
{
    // test_list1();
    test_list2();
    return 0;
}