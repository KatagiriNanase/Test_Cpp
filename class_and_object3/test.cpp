/**
 *@file test.cpp
 * @author Nanase
 * @brief polymorphism
 * @date 2025-06-04
 *
 *
 *
 */

 /**
  * 构成多态的两个条件：
  * 1.必须通过基类的指针或者引用调用函数
  * 2.被调用的函数必须是虚函数，且派生类必须对基类的虚函数进行重写
  *
  */

#include <iostream>

using namespace std;

/* --------------- 多态 ---------------*/
/**
 * 普通函数的继承是一种实现继承，派生类继承了基类函数，可以使用函数，继承的是函数的实现。
 * 虚函数的继承是一种接口继承，派生类继承的是基类虚函数的接口，目的是为了重写，达成多态，继承的是接口。
 * 所以如果不实现多态，不要把函数定义成虚函数。
 */
namespace test1
{
    class Person {

    public:
        virtual void BuyTicket()
        {
            cout << "Person::买票-全价" << endl;
        }


    };

    class Student :public Person {

    public:
        virtual void BuyTicket()    //此virtual关键词可以省略
        {
            cout << "Student::买票-半价" << endl;
        }

    };


    void fun(Person& p)
    {
        p.BuyTicket();
    }

    void fun(Person* p)
    {
        p->BuyTicket();
    }

    /* -----------TEST FUNCTION -----------*/

    void test1()
    {
        Person p1;
        Student s1;

        fun(p1);
        fun(s1);

        fun(&p1);
        fun(&s1);
    }
}


/* --------------- 协变 ---------------*/
/**
 * 一般而言，重写虚函数的条件为函数名，返回值和参数都相同.
 * 基类虚函数返回基类对象的指针或者引用，派生类虚函数返回派生类对象的指针或者引用时，称为协变。
 * 
 */
namespace test2
{

    class A {};
    class B : public A {};

    class Person {

    public:
        virtual A* BuyTicket()
        {
            cout << "Person::买票-全价" << endl;
            return nullptr;
        }
    };

    class Student :public Person {

    public:
        virtual B* BuyTicket()    //此virtual关键词可以省略
        {
            cout << "Student::买票-半价" << endl;
            return nullptr;
        }

    };


    void fun(Person& p)
    {
        p.BuyTicket();
    }

    void fun(Person* p)
    {
        p->BuyTicket();
    }

}

/* --------------- 虚函数->析构 ---------------*/
/**
 * 在基类的析构前写上virtual后，派生类与基类就满足了多态的两个条件
 * delete会去调用自定义类型的虚构，且析构已经为虚函数，并且已经进行重写；
 * 当指针类型为基类指针时，满足了通过基类的指针去调用虚函数。
 * 此时，当delete的为派生类指针时，就会去调用派生类的析构；当后面接的为基类指针时，就会调用基类的析构
 * 至此，构成多态
 *
 */
namespace test3
{
    class Person {
    public:
         ~Person()  
        {
            cout << "~Person()" << endl;
        }

    protected:
        int _age;
    };

    class Student :public Person{
    public:
         ~Student()
        {
            cout << "~Student()" << endl;
        }

    protected:
        int _stuId;
    };

    void test1()
    {
        //Person* p1 = new Person;
        Person* s1 = new Student;
        //delete p1;
        delete s1;
    }
}

/* --------------- 动态绑定&静态绑定 ---------------*/
namespace test4
{
    class  A
    {
    public:
        virtual void func(int val = 1) { cout << "A->" << val << endl; }
        virtual void test() { func(); }
    };

    class B :public A
    {
    public:
        /**
         * 由于val的值由A::fun()的声明决定了（编译时绑定），所以val=1
         * 可以理解为对于虚函数的重写，只重写了函数体的部分，而对于函数参数则已经确定了
         *
         */
        void func(int val = 0) { cout << "B->" << val << endl; }
        
    };

    void test1()
    {
        B* p = new B;
        p->test();
    }
}

/* --------------- override & final ---------------*/
/**
 * 1.被final修饰的函数不能被重写 （我是最终的一个函数了，我不能被重写了）
 * 2.被final修饰的类不能被继承（最终类）
 *
 * ========= override ==========
 * 1.override检查派生类虚函数是否重写了基类某个虚函数，如果没有重写编译报错
 */
namespace test5
{
    class Person //final final修饰了类后，此类不可再被继承（最终类）
    {
    public:
        virtual ~Person() //添加了final修饰后，Stduent不可在重写        
        {
            cout << "~Person()" << endl;
        }

    protected:
        int _age;
    };

    class Student :public Person {
    public:
        virtual ~Student()
        {
            cout << "~Student()" << endl;
        }

    protected:
        int _stuId;
    };

    class Car
    {
    public:
        virtual void Drive() 
        {
        }
    };
    
    class Benz :public Car
    {
    public:
        virtual void Drive() override   
        {
            cout << "Benz-舒适" << endl;
        }
    };

    void test1()
    {
        //Person* p1 = new Person;
        Person* s1 = new Student;
        //delete p1;
        delete s1;
    }
}


int main()
{

    // test1::test1();
    // test3::test1();
    test4::test1();

    return 0;
}
  