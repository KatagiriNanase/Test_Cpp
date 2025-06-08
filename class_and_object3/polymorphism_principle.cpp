#include <iostream>

using namespace std;

class A
{
public:
    virtual void fun1() {}
    virtual void fun2() {}

protected:
    int _a;
};

class B :public A
{
public:

};

/* ----------单继承和多继承关系的虚函数表 --------------*/
class Base {
public:
    virtual void func1() { cout << "Base::func1" << endl; }
    virtual void func2() { cout << "Base::func2" << endl; }
private:
    int a;
};

class Derive :public Base {
public:
    virtual void func1() { cout << "Derive::func1" << endl; }
    virtual void func3() { cout << "Derive::func3" << endl; }
    virtual void func4() { cout << "Derive::func4" << endl; }
private:
    int b;
};


typedef void (*VF_Ptr) (); //函数指针类型重定义

void PrintVFTable(VF_Ptr* pTable)
{
    for (size_t i = 0;pTable[i] != 0;++i)
    {
        printf("vfTable[%d]:%p\n", i, pTable[i]);
    }
    cout << endl;
}

int main()
{
    // A a;
    // cout << sizeof(a) << endl;
    // B b;

    /* 函数指针的定义 */
    // void (*p) ();

    Base b;
    Derive d;
    PrintVFTable((VF_Ptr*)(*(int*)&b));
    PrintVFTable((VF_Ptr*)(*(int*)&d));



    return 0;
}