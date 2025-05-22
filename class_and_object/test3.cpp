#include <iostream>

using namespace std;

class A {
public:
    //explicit 修饰构造函数 禁止隐式类型转换
    //explicit  A(int a)
    //    :_a(a)
    //{}

    explicit A(int a)
        :_a(a)
    {
    }

private:
    int _a;
};

class B {
public:
    B(int a, int& ref)
        : _aobj(a)
        , _ref(ref)
        , _n(a)
    {
    }
private:
    A _aobj;    //没有默认构造函数的自定义类型
    int& _ref;  //引用成员变量
    const int _n;

};

class Count {
public:
    //构造函数
    Count()
    {
        _count++;
    }
    //拷贝构造函数
    Count(const Count& c)
    {
        _count++;
    }
    //析构函数
    ~Count()
    {
        _count--;
    }

    static int& GetCount()
    {
        return _count;
    }
private:
    //静态成员变量的声明
    /*
     * 1.静态成员变量存放于静态区，被所有对象共享
     * 2.静态成员变量必须在类外面定义，
     * 3.静态成员有两种访问方式：类名:: 静态成员 or 对象.静态成员
     * 4.静态成员函数没有this指针，不能访问任何非静态成员
     *
     */
    static int _count;
};

//静态成员变量的定义
int Count::_count = 0;

void TestA()
{
    cout << Count::GetCount() << endl;
    Count c1, c2;
    Count c3(c1);
    cout << Count::GetCount() << endl;
}

/*>>>>>>>>>-------- 友元函数 --------<<<<<<<<<*/

class Date {
    //添加友元函数声明，使这个函数能够调用private成员变量
    friend ostream& operator<<(ostream& out, const Date& d);
    friend istream& operator>>(istream& in, Date& d);
public:
    Date(int year = 0, int month = 0, int day = 1)
        :_year(year)
        , _month(month)
        , _day(day)
    {

    }

    //operator<<
    /* ostream& operator<<(ostream& out) const
    {
        out << _year << '/' << _month << '/' << _day << endl;
        return out;
    } */
private:
    int _year;
    int _month;
    int _day;
};

//重载operator<<
ostream& operator<<(ostream& out, const Date& d)
{

    out << d._year << '/' << d._month << '/' << d._day << endl;
    return out;
}

//重载operator>>
istream& operator>>(istream& in, Date& d)
{
    in >> d._year >> d._month >> d._day;
    return in;
}

void TestB()
{
    Date d1(2025, 5, 22);
    Date d2;
    //d1 << cout;
    //d2 << cout;
    cin >> d1 >> d2;
    cout << d1 << d2;
}

/*>>>>>>>>>-------- 内部类 --------<<<<<<<<<*/
class C
{
private:
    static int k;
    int h;
public:
    class B // B是C的友元
    {
    public:
        void foo(const C& c)
        {
            //访问了C的私有成员变量
            cout << k << endl;//OK
            cout << c.h << endl;//OK
        }
    };
};

int C::k = 1;

void TestC()
{
    //用C中定义的类B实例化一个b
    C::B b;
    b.foo(C()); //C() 临时对象的构造
}


/*>>>>>>>>>-------- 匿名对象 --------<<<<<<<<<*/
class Solution
{
public:
    Solution(int i = 10)
    {
        cout << "Solution" << endl;
    }
    // Solution(const Solution& s)
    // {
    //     cout << "Copy Solution" << endl;
    // }
    int Sum_Solution(int n)
    {
        //...
        cout << "Sum_Solution()" << endl;
        return n;
    }

    ~Solution()
    {
        cout << "~Solution" << endl;
    }
};

void TestD()
{
    Solution s1;
    s1.Sum_Solution(10);
    //Solution(); 匿名对象的创建    声明周期就只有在这一行
    Solution().Sum_Solution(10);    //只有我这一行会使用这个创建对象，别人不需要使用
}

void TestE()
{
    Solution s1 = 10;      /**
     * 理论上来说，会先执行构造函数Solution(10) 创建一个临时对象
     * 进而通过拷贝构造，实例化s1
     * 但是编译器将拷贝构造优化了，相当于直接执行了构造函数
     * 注释掉拷贝构造函数也能运行
     */

}

int main()
{

    A a1(10);   //1.隐式类型转换->> A tmp(1) 2.浅拷贝 ->> a1=tmp 
    //TestA();
    //TestB();
    //TestC();
    //TestD();
    TestE();
    int i;
    while (cin >> i)
    {

    }
    return 0;
}