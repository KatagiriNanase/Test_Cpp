#include <iostream>
#include <stdio.h>
using namespace std;


/*>>>>>>>>>-------- 内存划分区域 --------<<<<<<<<<*/
void Test1()
{
    char char2[] = "abcd";  //char2为4个char大小的数组，内存内依次放着a,b,c,d四个字符
    const char* pChar3 = "abcd";  //pChar3为指针，指向在常量区内的字符串常量"abcd"
    int* ptr1 = (int*)malloc(sizeof(int) * 4);  //ptr1是存放在栈中的指针,而*ptr存在于堆中
    free(ptr1);
}



/*>>>>>>>>>-------- 分配内存 --------<<<<<<<<<*/
void Test2()
{
    //C 函数
    int* p1 = (int*)malloc(sizeof(int));
    int* p3 = (int*)malloc(sizeof(int) * 4);
    free(p1);
    free(p3);

    //C++ 操作符
    int* p2 = new int(4);  //申请一个int 4字节空间，初始化为4 
    int* p4 = new int[4];  //申请4个int 16字节的空间 不能加()初始化
    delete p2;
    delete[] p4;
}


class A {

public:
    A(int a = 0)
        :_a(a)
    {
        cout << "A()" << endl;
    }

    ~A()
    {
        cout << "~A()" << endl;
    }
private:
    int _a;
};

/*>>>>>>>>>-------- new & malloc --------<<<<<<<<<*/
//C
typedef struct ListNode_C {
    int _val;
    struct ListNode_C* _next;
    struct ListNode_C* _prev;
}ListNode_C;

ListNode_C* BuyListNode_C(int val)
{
    ListNode_C* pNode = (ListNode_C*)malloc(sizeof(ListNode_C));
    pNode->_next = NULL;
    pNode->_prev = NULL;
    pNode->_val = val;
    return pNode;
}

//Cpp
struct ListNode_CPP
{
    int _val;
    ListNode_CPP* _next;
    ListNode_CPP* _prev;

    ListNode_CPP(int val = 0)
        :_val(val)
        , _next(nullptr)
        , _prev(nullptr)
    {

    }
};

void Test3()
{
    //C
    ListNode_C* node_c = BuyListNode_C(1);

    //Cpp
    ListNode_CPP* node_cpp = new ListNode_CPP;  //自定义类型的指针，new申请内存+调用构造函数
    ListNode_CPP* node_cpp2 = new ListNode_CPP(5); //括号()调用构造函数

}

/*>>>>>>>>>-------- operator new & operator delete --------<<<<<<<<<*/

void Test4()
{
    A* p1 = (A*)operator new(sizeof(A));    //operator new 申请失败抛出异常（面向对象的处理）
    A* p2 = (A*)malloc(sizeof(A));          //malloc 申请失败返回0

    A* p3 = new A;      //new=operator new + 调用构造函数

    operator delete(p1);    //operator delete 最终也是调用free进行空间的释放,只是为了和operator new 成对出现
    free(p2);       //C
    delete p3;      //delete=调用析构函数 + operator delete

    A* arr2 = new A[4]; //new T[]=operator new[] +调用构造函数,operator new[]调用的是operator new
    A* arr = (A*)operator new[](sizeof(A) * 4);

    operator delete[](arr2);    //多次调用析构函数后调用operator delete

}

/*>>>>>>>>>-------- 定位new --------<<<<<<<<<*/

//定位new表达式是在已分配的原始内存空间中调用构造函数初始化一个对象
/**
 * 使用格式 new(place_address)type(initializer-list)
 * 其中，place_address是一个指针，initializer-list是类型的初始化列表
 *
 */
void Test5()
{
    /* --------malloc-------- */
    A* p1 = (A*)malloc(sizeof(A));  //只分配了空间给p1，并没有初始化p1指向的那块空间
    new(p1)A;   //模拟调用构造函数
    p1->~A();   //模拟调用析构函数

    /* --------new-------- */
    A* p2 = new A;
    new(p2)A(1);
    p2->~A();

    /* --------operator new-------- */
    A* p3 = (A*)operator new(sizeof(A));
    new(p3)A(4);
    p3->~A();

}

int main()
{
    //A* p1 = (A*)malloc(sizeof(A));  //单纯申请空间
    //A* p2 = new A;  //申请空间+构造函数初始化
    //free(p1);   //释放空间
    //delete p2;  //先析构函数 后释放空间
    //Test3();
    //Test4();
    Test5();
    return 0;
}
