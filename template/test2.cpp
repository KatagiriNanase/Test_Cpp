#include <iostream>
#include <assert.h>
using namespace std;
/*>>>>>>>>>-------- vector --------<<<<<<<<<*/
template<class T>
class vector {  //动增长的数组
public:
    //一般数据结构我们定义的构造函数不给空间
    vector()
        :_a(nullptr)
        , _size(0)
        , _capacity(0)
    {

    }
    vector(size_t n)
        :_a(new T[n])   //new T[n]返回了指针，初始化了_a
        , _size(0)
        , _capacity(n)
    {

    }
    ~vector()
    {
        delete[] _a;
        _a = nullptr;
        _size = _capacity = 0;
        cout << "~vector()" << endl;
    }
    //成员函数类内声明
    void push_back(const T& x); //如果这个T是个自定义类型，那如果是传值的方式就会进行拷贝构造，所以建议引用
    T pop_back();

    size_t size()
    {
        return _size;
    }

    //引用传返回值：1.可以修改返回的对象 2.减少拷贝
    T& operator[](size_t i)
    {
        return _a[i];
    }

private:
    T* _a;
    size_t _size;
    size_t _capacity;

};

//成员函数类外定义
template<class T>
void vector<T>::push_back(const T& x)
{
    //空间不够，需要进行增容
    if (_size == _capacity)
    {
        size_t newcapacity = _capacity == 0 ? 2 : _capacity * 2;
        T* tmp = new T[newcapacity];
        if (_a)
        {
            memcpy(tmp, _a, sizeof(T) * _size);
            delete[] _a;
        }
        _a = tmp;
        tmp = nullptr;
        _capacity = newcapacity;
    }

    _a[_size] = x;
    _size++;
}

template<class T>
T vector<T>::pop_back()
{
    assert(_size > 0);
    --_size;
}

int main()
{
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    //写入
    for (size_t i = 0;i < v.size();++i)
    {
        v[i] *= 2;
    }

    //读取
    for (size_t i = 0;i < v.size();++i)
    {
        cout << v[i] << ' ' << endl;
    }
    cout << endl;



    return 0;
}