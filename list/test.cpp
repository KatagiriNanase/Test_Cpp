#include <list>
#include <iostream>
#include <algorithm>
using namespace std;

void print_list(const list<int>& l)
{
    list<int>::const_iterator it = l.begin();

    while (it != l.end())
    {
        cout << *it << ' ';
        it++;
    }
    cout << endl;
}

void test_list1()
{
    list<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);

    list<int>::iterator it = l.begin();
    while (it != l.end())
    {
        cout << *it << ' ';
        it++;
    }
    cout << endl;

    for (auto e : l)
    {
        cout << e << ' ';
    }
    cout << endl;
}

void test_list2()
{
    list<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    print_list(l);

    l.push_front(0);
    l.push_front(-1);
    l.push_front(-2);
    print_list(l);

    l.pop_back();
    l.pop_front();
    print_list(l);

    list<int>::reverse_iterator rit = l.rbegin();
    while (rit != l.rend())
    {
        cout << *rit << ' ';
        rit++;
    }
    cout << endl;

}

void test_list3()
{
    list<int> lt1;
    lt1.push_back(1);
    lt1.push_back(2);
    lt1.push_back(3);
    lt1.push_back(4);
    print_list(lt1);

    list<int> lt2;
    lt2.push_back(10);
    lt2.push_back(20);
    lt2.push_back(30);
    lt2.push_back(40);

    lt1 = lt2;
    print_list(lt1);

}

void test_list4()
{
    list<int> lt1;
    lt1.push_back(1);
    lt1.push_back(2);
    lt1.push_back(3);
    lt1.push_back(4);
    print_list(lt1);

    list<int>::iterator pos = find(lt1.begin(), lt1.end(), 3);
    if (pos != lt1.end())
    {
        lt1.insert(pos, 30);
        lt1.erase(pos);     //pos指向的位置还是3，并没有失效
    }
    print_list(lt1);
}

void test_list5()
{
    list<int> lt;
    lt.push_back(3);
    lt.push_back(1);
    lt.push_back(5);
    lt.push_back(2);
    print_list(lt);

    lt.sort();
    print_list(lt);

    lt.reverse();
    print_list(lt);
}

//迭代器失效--删除偶数
/**
 * vector的iterator insert(导致的增容问题reserve)、erase都会导致失效
 * list的iterator erase会导致失效
 *
 */
void test_list6()
{
    list<int> lt;
    for (size_t i = 0;i < 10;++i)
        lt.push_back(i);

    print_list(lt);
    list<int>::iterator it = lt.begin();
    /*  while(it!=lt.end())
     {
         if (*it % 2 == 0)
             lt.erase(it);       //一旦经过erase后，此迭代器就失效了
         it++;
     } */
    while (it != lt.end())
    {
        if (*it % 2 == 0)
            it = lt.erase(it);
        else
            it++;
    }
    print_list(lt);
}

int main()
{
    // test_list1();
    // test_list2();
    // test_list3();
    // test_list4();
    // test_list5();
    test_list6();
    return 0;
}