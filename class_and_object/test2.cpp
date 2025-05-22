#define _CRT_SECURE_NO_WARNINGS

#include "Date.hpp"
using namespace std;

int main()
{
    Date d1;
    Date d2(2025, 5, 15);
    Date d3 = (d2 + 1000);
    Date d4 = d3;
    //d1.ShowDate();
    //d1 += 10;
    //d1.ShowDate();
    //d3.ShowDate();
    //d4.ShowDate();
    //d4 = d1;
    //d4.ShowDate();

    cout << (d1 == d2) << endl;
    cout << (d1.operator<=(d2)) << endl;

    //运算符重载
    d3 = d2 = d1;    

    return 0;
}