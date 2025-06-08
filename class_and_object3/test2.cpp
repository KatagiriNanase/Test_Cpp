#include <iostream>

using namespace std;

/* --------------- 抽象类 ---------------*/
/**
 * 在虚函数的后面写上=0，则这个函数为纯虚函数
 * 包含纯虚函数的类叫做抽象类（也叫接口类），抽象类不等实例化出对象
 *  ========= 作用 =========
 *  1.强制派生类去完成重写
 *  2.表示抽象的类型。 抽象就是在现实中没有对应的实体的。
 */
namespace test1
{
    //抽象类
    class Car
    {
    private:
        virtual void Drive() = 0;   //不需要实现定义，纯虚函数
    };

    //派生
    class Benz :public Car
    {
    public:
        virtual void Drive() {} //必须重写纯虚函数，才能实例化
    };

    void test1()
    {
        /* 抽象类不允许被实例化 */
        // Car c1;

        /*  */
        Benz b1;
    }
}




int main()
{

    return 0;
}