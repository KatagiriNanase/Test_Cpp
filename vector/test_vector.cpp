#include <iostream>
#include "vector.h"
#include <string>
using namespace std;

void print_vector(const vector<int> v)
{
    //迭代器遍历
    vector<int>::const_iterator it = v.begin();
    while (it != v.end())
    {
        cout << *it << ' ';
        it++;
    }
    cout << endl;
}

void test_vector1()
{
    vector<int> v;
    v.push_back(0);
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);

    print_vector(v);
    cout << endl;
    //范围for遍历
    for (auto& e : v)
    {
        e += 1;
        cout << e << ' ';
    }
    cout << endl;
    v.push_back(5);
    cout << v.size() << endl;
    cout << v.capacity() << endl;

    //operator[] 遍历
    for (size_t i = 0;i < v.size();++i)
    {
        v[i] -= 1;
        cout << v[i] << ' ';
    }
    cout << endl;
}

void test_vector2()
{
    vector<int> v;
    v.push_back(0);
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    v.push_back(6);

    print_vector(v);

    vector<int>::iterator it = v.begin();
    while (it != v.end())
    {
        if (*it % 2 == 0)
            it = v.erase(it);
        else
            it++;
    }

    print_vector(v);

}


void test_vector3()
{
    vector<int> v;
    v.reserve(10);
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);

    print_vector(v);
    cout << "size:" << v.size() << endl
        << "capacity:" << v.capacity() << endl << endl;

    v.resize(12);
    print_vector(v);
    cout << "size:" << v.size() << endl
        << "capacity:" << v.capacity() << endl << endl;

    v.resize(8);
    print_vector(v);
    cout << "size:" << v.size() << endl
        << "capacity:" << v.capacity() << endl << endl;

    v.resize(4);
    print_vector(v);
    cout << "size:" << v.size() << endl
        << "capacity:" << v.capacity() << endl << endl;

}

void test_vector4()
{
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);

    vector<int> v2(v);
    print_vector(v);

    v2.pop_back();
    v = v2;
    print_vector(v);


}

void test_vector5()
{
    vector<string> v;
    v.push_back("1111");
}

int main()
{
    // test_vector1();
    // test_vector2();
    // test_vector3();
    // test_vector4();

    return 0;
}