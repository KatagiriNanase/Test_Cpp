#include <iostream>

using namespace std;

/* --------------继承与静态成员--------------- */

namespace test1
{
    class Persion {

    public:
        Persion()
        {
            _count++;
        }
    protected:
        string _name; //姓名

    public:
        //整个继承体系里面只有一个这样的成员,无论派生出多少个子类，都只有一个static成员实例
        static int _count; //统计人的个数
    };

    int Persion::_count = 0;

    class Student :public Persion {

    protected:
        int _stuNum;    //学号

    };

    void test1()
    {
        Student s1;
        Persion p1;
        Student s2;
        cout << Persion::_count << endl;
        p1._count++;
        cout << Student::_count << endl;
        s2._count += 2;
        cout << Student::_count << endl;

    }


}



/* --------------多继承--------------- */


namespace test2
{
    class Person
    {
    public:
        string _name; // 姓名
    };

    class Student : virtual public Person
    {
    protected:
        int _num; //学号
    };

    class Teacher : virtual public Person   //
    {
    protected:
        int _id; // 职工编号
    };

    class Assistant : public Student, public Teacher
    {
    protected:
        string _majorCourse; // 主修课程
    };

    void test1()
    {
        Assistant a;
        //菱形继承带来的二义性，无法知道此时访问的是Student类的_name还是Teacher类的_name
        //虚继承解决，此时访问的是同一个_name
        a._name = "peter";

        //数据冗余
        a.Student::_name = "xxx";
        a.Teacher::_name = "yyy";

    }

    
}


/* --------------继承和组合--------------- */
/**
 * 1.符合is-a关系，使用继承
 * 2.符合has-a关系，使用组合
 * 3.都可以，优先使用组合，因为高内聚、低耦合
 * 
 */


int main()
{

    test1::test1();
    return 0;

}