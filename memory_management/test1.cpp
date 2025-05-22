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
    int* p4 = new int[4];  //申请4个int 16字节的空间
    delete p2;
    delete[] p4;
}


class A {

public:
    A()
        :_a(0)
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

int main()
{
    A* p1 = (A*)malloc(sizeof(A));  //单纯申请空间
    A* p2 = new A;  //申请空间+构造函数初始化

    free(p1);   //释放空间
    delete p2;  //先析构函数 后释放空间
    return 0;
}