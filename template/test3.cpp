#include <iostream>

using namespace std;


//类型模版参数+非类型模版参数
template<class T, int N>    //非类型模版参数必须是常量，不能修改
class Array {
public:
    
private:
    T _a[N];
};

int main()
{
    Array<int, 10> arr1;
    Array<double, 100> arr2;
    return 0;
}