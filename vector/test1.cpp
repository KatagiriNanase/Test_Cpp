#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


void vector_test1()
{
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);

    for (size_t i = 0;i < v1.size();++i)
    {
        cout << v1[i] << ' ';
    }
    cout << endl;

    vector<int> v2;
    v2.push_back(10);
    v2.push_back(20);
    v2.push_back(30);
    v2.push_back(40);

    v1 = v2;

    for (size_t i = 0;i < v1.size();++i)
    {
        cout << v1[i] << ' ';
    }
    cout << endl;


}

void vector_test2()
{
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);

    /* --------- 遍历修改数据 --------- */
    //1. operator[] +size
    for (size_t i = 0;i < v1.size();++i)
    {
        v1[i] *= 2;
    }

    //2. 迭代器(普通正向迭代器，可读可写)
    vector<int>::iterator v1_i = v1.begin();
    // basic_string<char>::insert
    while (v1_i != v1.end())
    {
        cout << *v1_i << ' ';
        v1_i++;
    }
    cout << endl;

    //3. 范围for->>由编译器替换成迭代器支持的
    for (auto e : v1)
    {
        cout << e << ' ';
    }


}


void PrintVector(const vector<int>& v)
{
    vector<int>::const_iterator it = v.begin();
    while (it != v.end())
    {
        cout << *it << ' ';
        it++;
    }
    cout << endl;
}



void vector_test3()
{
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);

    /* 反向迭代器 */
    vector<int>::reverse_iterator rit = v.rbegin();
    while (rit != v.rend())
    {
        cout << *rit << ' ';
        rit++;
    }
    cout << endl;
    //v.at(4)=5; at访问会抛异常

}

void vector_test4()
{
    vector<int> v;
    v.push_back(50);
    v.push_back(3);
    v.push_back(8);
    v.push_back(12);

    /* v.insert(v.begin(), 0);
    PrintVector(v);
    cout << v.capacity() << endl;

    v.erase(v.begin(), v.end());
    PrintVector(v);
    cout << v.capacity() << endl; */

    /* 指定删除5，用算法库里的find */
    vector<int>::iterator pos = find(v.begin(), v.end(), 5);
    if (pos != v.end())
    {
        v.erase(pos);
    }

    for (auto e : v)
    {
        cout << e << ' ';
    }
    cout << endl;

    sort(v.begin(), v.end());
    for (auto e : v)
    {
        cout << e << ' ';
    }

    cout << endl;

    int a = 1;
    a >>= 1;
    cout << a;

}

/* 迭代器失效 */
void vector_test5()
{
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(30);
    v.push_back(4);
    v.push_back(5);
    v.push_back(6);
    v.push_back(7);

    vector<int>::iterator it = v.begin();

    while (it != v.end())
    {
        if ((*it) % 2 == 0)     //删除it后，此时的it就失效了
            it = v.erase(it);   //erase会返回删除的it的下一个位置的迭代器
        else
            it++;
    }

    PrintVector(v);

}

int main()
{
    // vector_test1();
    // vector_test2();
    // vector_test3();
    // vector_test4();
    vector_test5();

    return 0;
}