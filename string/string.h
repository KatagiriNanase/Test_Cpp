#ifndef __STRING_H__
#define __STRING_H__

#include <string.h>
#include <iostream>

using std::cout;
using std::endl;

/* ------>>>>>>>简单实现string类<<<<<<<<------ */
namespace nanase
{
    class string {
    public:

        /*  string()
            :_str(new char) //防止strlen解引用nullstr
        {
            _str[0] = 0;
        }

        string(const char* str)
            //:_str(str)    ダメです!!  这样_str指向的就是代码区的字符串了，不能修改
            :_str(new char[strlen(str) + 1])
        {
            strcpy(_str, str);  //strcpy也会将'\0'拷贝过去
        } */

        string(const char* str = "") //""这里面啥也没有，里面就相当于存了一个'\0'的数组，大小为1，因此会开一个字节的空间
            :_str(new char[strlen(str) + 1])
        {
            strcpy(_str, str);
        }

        //拷贝构造函数-> 深拷贝
        string(const string& s)
            :_str(new char[strlen(s._str) + 1])   //开一个
        {
            strcpy(_str, s._str);
        }

        ~string()
        {
            delete[] _str;
            _str = nullptr;
        }
        size_t size() const
        {
            return strlen(_str);    //strlen是会进行解引用，遇到'\0'后才会停下来，因此如果遇到nullstr就会抛异常
        }

        char& operator[](size_t i)
        {
            return _str[i];
        }

        string& operator=(const string& s)
        {
            if (this != &s) //指针是可以比较的
            {

                char* tmp_str = new char[strlen(s._str) + 1];
                strcpy(tmp_str, s._str);
                delete[] _str;
                _str = tmp_str;
                tmp_str = nullptr;
                return *this;
            }

        }

        const char* c_str() const
        {
            return _str;
        }



    private:
        char* _str;

    };

    void test_string1()
    {
        string s1;
        string s2("hello world");

        for (size_t i = 0;i < s2.size();++i)
        {
            s2[i] += 1;
            cout << s2[i] << ' ';
        }

        for (size_t i = 0;i < s1.size();++i)
        {
            //s1[i] += 1;
            cout << s1[i] << ' ';
        }
    }

    void test_string2()
    {
        string s1("hello");
        string s2(s1);

        cout << s1.c_str() << endl;
        cout << s2.c_str() << endl;

        string s3("world");
        s3 = s1;    //依旧浅拷贝

    }

}


#endif /* __STRING_H__ */
