#include <iostream>

using namespace std;

class A {
public:
    //explicit ���ι��캯�� ��ֹ��ʽ����ת��
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
    A _aobj;    //û��Ĭ�Ϲ��캯�����Զ�������
    int& _ref;  //���ó�Ա����
    const int _n;

};

class Count {
public:
    //���캯��
    Count()
    {
        _count++;
    }
    //�������캯��
    Count(const Count& c)
    {
        _count++;
    }
    //��������
    ~Count()
    {
        _count--;
    }

    static int& GetCount()
    {
        return _count;
    }
private:
    //��̬��Ա����������
    /*
     * 1.��̬��Ա��������ھ�̬���������ж�����
     * 2.��̬��Ա���������������涨�壬
     * 3.��̬��Ա�����ַ��ʷ�ʽ������:: ��̬��Ա or ����.��̬��Ա
     * 4.��̬��Ա����û��thisָ�룬���ܷ����κηǾ�̬��Ա
     *
     */
    static int _count;
};

//��̬��Ա�����Ķ���
int Count::_count = 0;

void TestA()
{
    cout << Count::GetCount() << endl;
    Count c1, c2;
    Count c3(c1);
    cout << Count::GetCount() << endl;
}

/*>>>>>>>>>-------- ��Ԫ���� --------<<<<<<<<<*/

class Date {
    //�����Ԫ����������ʹ��������ܹ�����private��Ա����
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

//����operator<<
ostream& operator<<(ostream& out, const Date& d)
{

    out << d._year << '/' << d._month << '/' << d._day << endl;
    return out;
}

//����operator>>
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

/*>>>>>>>>>-------- �ڲ��� --------<<<<<<<<<*/
class C
{
private:
    static int k;
    int h;
public:
    class B // B��C����Ԫ
    {
    public:
        void foo(const C& c)
        {
            //������C��˽�г�Ա����
            cout << k << endl;//OK
            cout << c.h << endl;//OK
        }
    };
};

int C::k = 1;

void TestC()
{
    //��C�ж������Bʵ����һ��b
    C::B b;
    b.foo(C()); //C() ��ʱ����Ĺ���
}


/*>>>>>>>>>-------- �������� --------<<<<<<<<<*/
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
    //Solution(); ��������Ĵ���    �������ھ�ֻ������һ��
    Solution().Sum_Solution(10);    //ֻ������һ�л�ʹ������������󣬱��˲���Ҫʹ��
}

void TestE()
{
    Solution s1 = 10;      /**
     * ��������˵������ִ�й��캯��Solution(10) ����һ����ʱ����
     * ����ͨ���������죬ʵ����s1
     * ���Ǳ����������������Ż��ˣ��൱��ֱ��ִ���˹��캯��
     * ע�͵��������캯��Ҳ������
     */

}

int main()
{

    A a1(10);   //1.��ʽ����ת��->> A tmp(1) 2.ǳ���� ->> a1=tmp 
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