#include <iostream>

using namespace std;


class Person
{
public:
    Person(const char* name = "peter")
        : _name(name)
    {
        cout << "Person()" << endl;
    }
    Person(const Person& p)
        : _name(p._name)
    {
        cout << "Person(const Person& p)" << endl;
    }
    Person& operator=(const Person& p)
    {
        cout << "Person operator=(const Person& p)" << endl;
        if (this != &p)
            _name = p._name;
        return *this;
    }
    ~Person()
    {
        cout << "~Person()" << endl;
    }
protected:
    string _name; // 姓名
};


class Student :public Person {

public:
    Student(int stuid, const char* name)
        :_stuid(stuid)
        //,_name(name)  _name不是Student类的成员，都是分开初始化的;
        , Person(name)   //显示初始化
    {

    }

    Student(const Student& s)
        :_stuid(s._stuid)
        , Person(s)  //子类对象直接传引用父类对象---赋值兼容
    {

    }

    //s2=s3
    Student& operator=(const Student& s)
    {
        if (this != &s)
        {
            _stuid = s._stuid;  //先完成派生类的赋值
            Person::operator=(s);   //再调用基类的赋值函数
        }
        return *this;
    }

    ~Student()
    {
        //~Person();        //子类的析构函数和父类的析构函数构成隐藏，因为他们的名字会被编译器统一处理成destructor，如果不指定类域，就变成仍然是调用自己的析构
        //Person::~Person();    
        //并且析构函数不需要你去显式调用，他会自动取调用
        //这样才能保证先析构子类，后析构父类
        cout << "~Student()" << endl;
    }
protected:
    int _stuid;

};

/**
 * 1.派生类在初始化的时候会分父类的初始化和自己本身的初始化
 *      父类就调自己的构造，子类就调自己的构造
 * 2.如果要在初始化子类的时候初始化父类，就得在子类内调用父类的构造
 *
 * 3.派生类的默认拷贝构造：会先调用父类的拷贝构造，然后在进行派生类的浅拷贝
 *
 */

int main()
{
    Student s1(10, "nanase");
    // Student s2(s1);

    // Student s3(20, "sora");
    // s2 = s3;

    return 0;
}