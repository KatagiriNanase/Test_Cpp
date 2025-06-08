#include <iostream>

using namespace std;

namespace space1 {
    class Person {

    public:
        void Print()
        {
            cout << "name:" << _name << endl;
            cout << "age:" << _age << endl;
        }

    protected:
        string _name = "peter";
        int _age = 18;
    };

    //public继承
    class Student :protected Person {
    public:
        void fun()
        {
            Print();
        }
    protected:
        int _stuid; //学号
    };

    class Teacher :public Person {

    protected:
        int _jobid;
    };

}

namespace space2
{
    class Persion {
    public:

    protected:
        int _age;
        int _sex;
        string _name;
    };

    class Student : public Persion {
    public:

    protected:
        int _stuid;
    };

    void test2()
    {
        Persion p;
        Student s;


        //子类和父类之间的赋值兼容规则
        //1.子类对象可以赋值给父类对象/指针/引用    -->>> 切片/切割

        p = s;
        Persion* ptr = &s;  //指针只能访问到父类的成员变量
        Persion& ref = s;   //引用的别名也只是父类的成员变量的别名

        //s=p       //父类不能赋值给子类
        Student* sptr = (Student*)ptr;  //如果父类指针本身就指向的是子类对象，那经过强转就可以赋值

    }
}


namespace space3
{
    class Persion {
    public:

    protected:
        int _age = 10;
        int _sex = 1;
        string _name = "小李子";
    };

    class Student : public Persion {
    public:
        void Print()
        {
            cout << _stuid << endl;
            cout << _age << endl;       //当父类和子类同时有同名成员时，子类的成员隐藏的父类的成员，这里会优先寻找当前作用域下的成员（重定义）
            cout << Persion::_age << endl;  //指定作用域便可以访问了

        }

    protected:
        int _stuid = 111;
        int _age = 19;
    };

    void test1()
    {
        Student s;
        s.Print();
    }
}

namespace space4
{
    class A {
    public:
        void fun()
        {
            cout << 'A' << endl;
        }
    protected:

    };

    class B :public A {
    public:
        void fun()
        {
            cout << 'B' << endl;
        }
    };

    void test1()
    {
        B b;
        b.A::fun();
    }
}
//A和B的fun()的关系为重定义(隐藏)
//重载是需要在同一作用域内的


void test1()
{
    space1::Student s;
    space1::Teacher t;
    s.fun();
    t.Print();
}



int main()
{

    // space2::test2();
    space4::test1();
    return 0;
}