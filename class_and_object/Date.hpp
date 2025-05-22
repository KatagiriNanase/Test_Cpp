#ifndef __DATE_HPP__
#define __DATE_HPP__
#include <iostream>

class Date {
public:
    //获取月份天数
    int GetMonthDay(const int year,const int month) const;

    //构造函数--- 1.以类名作为函数名 2.对象实例化时自动调用
    Date(int year = 0, int month = 0, int day = 0);


    //拷贝构造函数
    Date(const Date& d);


    //显示日期函数
    void ShowDate();


    //d1==d2 d1.operator(d2)
     bool operator==(const Date& d);

    //operator!=
     bool operator!=(const Date& d);

    //operator<
     bool operator<(const Date& d);

    //operator<=
    bool operator<=(const Date& d);


    //operator>
    bool operator>(const Date& d);


    //operator>=
    bool operator>=(const Date& d);


    //operator+
    Date operator+(const int day) const;

    Date& operator+=(int day);

    //operator=
    Date& operator=(const Date& d);

    //析构函数
    //~Date();


private:
    int _year;
    int _month;
    int _day;

};

#endif /* __DATE_HPP__ */