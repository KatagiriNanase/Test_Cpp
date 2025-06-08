#include <iostream>


using namespace std;

/*>>>>>>>>>-------- string constructor --------<<<<<<<<<*/
void Test1()
{
    string s1;
    string s2("hello");
    string s3(s2);
    string s4(10, 'a');
    string s5 = "hello";    //先构造临时变量，后拷贝构造->>>编译器优化为直接构造
    string s6 = s2;     //拷贝构造

    cout << s1 << endl << s2 << endl << s3 << endl << s4 << endl;

    s1 = s2;
    cout << s1 << endl;

}

/*>>>>>>>>>-------- string member function --------<<<<<<<<<*/
void Test2()
{
    string s("12345");
    s.push_back('6');
    s.append("78");
    s += '1';
    s += "1111";

    string s1;
    s1 += "Katagiri";
    s1 += '_';
    s1 += "Nanase";
    cout << s1 << endl;
}

void Test3()
{
    string s("12345");
    int val = 0;
    for (size_t i = 0;i < s.size();++i)
    {
        val *= 10;
        val += (s[i] - '0');
    }
    cout << val;
}

void Test4()
{
    string s1("hello");
    string s2(s1, 1, 2);
    string s3(s1, 1, 8);
    string s4(s1, 1, string::npos); //不填或者显示填npos，超出原有string的长度，就相当于将剩余的字符全都拿过来构造

    cout << s1 << endl;
    cout << s2 << endl;
    cout << s3 << endl;
    cout << s4 << endl;

}

/*>>>>>>>>>-------- 迭代器 --------<<<<<<<<<*/

//正向迭代器
void Test5()
{
    string s1("hello");
    s1 += ' ';
    s1 += "world";

    /* -------迭代器遍历------- */
    // string::iterator it = s1.begin();
    auto it = s1.begin();
    //写
    while (it != s1.end())
    {
        *it += 1;
        it++;
    }
    //读
    it = s1.begin();
    while (it != s1.end())  //s1.end()返回的是string最后一个字符的+1位
    {
        cout << *it << ' ';
        it++;
    }
    cout << endl;

    /* -------范围for遍历------- */     //C++11 
    //原理：编译时被替换为迭代器
    for (auto ch : s1)
    {
        cout << ch << ' ';
    }
    cout << endl;

    /* -------反向遍历------- */
    string s2("hello world");
    string::iterator s_it = s2.end() - 1;
    while (s_it != s1.begin() - 1)
    {
        cout << *s_it << ' ';
        s_it--;
    }
    cout << endl;
}

//const 迭代器
int string2num(const string& str)
{
    // auto cs_it = str.begin();
    string::const_iterator cs_it = str.begin();
    int val = 0;
    while (cs_it != str.end())
    {
        val *= 10;
        val += *cs_it - '0';
        cs_it++;
    }
    return val;
}

//const反向迭代器
int string2reverse_num(const string& str)
{
    // string::const_reverse_iterator cs_rit = str.rbegin();
    auto cs_rit = str.rbegin();
    int val = 0;
    while (cs_rit != str.rend())
    {
        val *= 10;
        val += *cs_rit - '0';
        cs_rit++;
    }
    return val;
}

//反向迭代器
void Test6()
{
    string s1("hello world");
    //倒着遍历
    string::reverse_iterator s_rit = s1.rbegin();
    while (s_rit != s1.rend())
    {
        cout << *s_rit << ' ';
        s_rit++;
    }
    cout << endl;

    string s2("123456");
    cout << string2num(s2) << endl;
    cout << string2reverse_num(s2) << endl;
}

//capacity
void Test7()
{
    string s1("hello world");
    string s2(18, 'h');

    cout << s1.capacity() << endl;
    cout << s2.capacity() << endl;
    s1 += "11111";
    s2 += "1111";
    cout << s1.capacity() << endl;
    cout << s2.capacity() << endl;
    s1.clear();
    cout << s1 << endl;
    cout << s1.capacity() << endl;  //清除了字符，但是没有释放空间
}

void Test8()
{
    string s;
    //s.reserve(100); //直接申请扩容
    s.resize(100, 'x');
    size_t sz = s.capacity();
    for (int i = 0;i < 100;++i)
    {
        if (sz != s.capacity())
        {
            sz = s.capacity();
            cout << "capacity change:" << sz << endl;
        }
        s.push_back(1);
    }
}

//insert & erase
void Test9()
{
    string s("13456");
    s.insert(s.begin(), '0');
    cout << s << endl;
    s.insert(2, "2");
    cout << s << endl;
    s.erase(2);
    cout << s << endl;
}

int main()
{
    //Test3();
    //Test4();
    // Test5();
    // Test6();
    //Test7();
    // Test8();
    //Test9();

    string s("hello");
    cout << s << endl;
    //s.erase(2, 2);
    cout << s << endl;
    return 0;
}