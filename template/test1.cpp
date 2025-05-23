#include <iostream>

using namespace std;



/*>>>>>>>>>-------- 函数模版 --------<<<<<<<<<*/
template<typename T>
T Add(const T& a, const T& b)
{
    return a + b;
}

/**
 * 1.非模版函数可以和同名模版函数同时存在
 * 2.同名函数模版可以被实例化为这个同名的非模版函数
 * 3.调用时会优先调用这个非模版函数；如果模版函数能实例化出一个更好匹配的函数，那么将选择模版函数
 */
int Add(int a, int b)
{
    return a + b;
}

void Test1()
{
    int a1 = 10, a2 = 20;
    double d1 = 1.1, d2 = 2.2;

    /* 隐式实例化：让编译器根据实参推演模版参数的实际类型 */
    Add(a1, a2);
    Add(d1, d2);

    /* 显示实例化：在函数名后的<>中指定模板参数的实际类型 */
    Add<int>(a2, a1);
    Add<double>(d2, d1);
    Add<double>(a1, d1);    //编译器进行隐式类型转换
    //Add(a1, d1);      //编译报错
    Add(a1, (int)d1);   //强制类型转化

}

/*>>>>>>>>>-------- 类模版 --------<<<<<<<<<*/

/* ------C语言实现栈------- */
typedef int STDataType;

typedef struct Stack_C {
    STDataType* _a;
    int _size;
    int _capacity;
}Stack_C;

void Stack_CInit(Stack_C* ps)
{
}

void Stack_CDistroy(Stack_C* ps)
{
}

void Stack_CPush(Stack_C* ps, STDataType x)
{
}

STDataType Stack_CPop(Stack_C* ps)
{
}

void Test2()
{
    /**
     * 1.忘记初始化和销毁                                   -> 构造函数+析构函数
     * 2.没有封装，谁都可以修改结构体的数据                    -> 类+访问限定符
     * 3.如果想同时定义两个栈，一个栈int，一个栈double，做不到   -> 模版
     *
     */
    Stack_C st_c;
    Stack_CInit(&st_c);
    Stack_CPush(&st_c, 1);
    Stack_CPush(&st_c, 2);
    Stack_CPush(&st_c, 3);
    //非法修改
    st_c._capacity = 0;
    Stack_CDistroy(&st_c);


}/* ------END_C语言实现栈------- */

/* ------CPP实现栈------- */
template<class T>
class Stack_CPP {
public:
    Stack_CPP(T* a = nullptr, int size = 0, int capacity = 0)
        :_a(nullptr)
        , _size(size)
        , _capacity(capacity)
    {
        cout << "Stack_CPP()" << endl;
    }

    ~Stack_CPP()
    {
        delete[] _a;
        _a = nullptr;
        _size = _capacity = 0;
        cout << "~Stack_CPP()" << endl;
    }

    void push(T a)
    {

    }

    T pop()
    {

    }
private:
    T* _a;
    int _size;
    int _capacity;
};

void Test3()
{
    Stack_CPP<int>  stack_cpp_int;
    stack_cpp_int.push(1);
    stack_cpp_int.push(2);
    stack_cpp_int.push(3);

    Stack_CPP<double> stack_cpp_double;
    stack_cpp_double.push(1.1);
    stack_cpp_double.push(2.2);
    stack_cpp_double.push(3.3);

    stack_cpp_double.~Stack_CPP();
}

int main()
{
    //Test1();
    Test3();
    return 0;
}