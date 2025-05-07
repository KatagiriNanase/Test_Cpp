#include <iostream>
#include <vector>
// #include <stdio.h>
using namespace std;
#include <string>

void fun(int &x)
{
    x = 100;
}

void test4()
{
    int a = 0;
    fun(a);
    cout << a;
}

void test3()
{
    struct stu
    {
        int grade;
        float score;
    };
    stu arr[2] = {0};

    for (int i = 0; i < 2; i++)
    {
        cin >> arr[i].grade >> arr[i].score;
    }
    for (int i = 0; i < 2; i++)
    {
        cout << arr[i].grade << ' ' << arr[i].score << endl;
    }
}

void test2()
{
    string s = "hello vscode";
    string s1 = s.substr(6, 6);
    string s2 = s.substr(0, 5);
    cout << s2 << endl
         << s1;
}
void test1()
{
    string s1;
    getline(cin, s1);
    cout << s1.length();
}

void test5()
{
    vector<int> v1;
    v1.resize(8, 1);
    cout << v1[0];
}

void test6()
{

    vector<int> a;
    cout << a.size() << endl;

    for (int i = 0; i < 10; i++)
    {
        a.push_back(i);
    }
    cout << a.size() << endl;
    for (int i = 0; i < 10; i++)
    {
        cout << a[i] << " " << endl;
    }
}

int main()
{
    test6();
    return 0;
}
