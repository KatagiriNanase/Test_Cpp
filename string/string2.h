#ifndef __STING2_H__
#define __STING2_H__

#include <string.h>
#include <iostream>
#include <assert.h>

using std::cout;
using std::endl;



/* ------>>>>>>>能够增删查改的string类<<<<<<<<------ */
namespace nanase
{
    class string {
    public:
        typedef char* iterator;
        string(const char* str = "")
        {
            _size = strlen(str);
            _capacity = _size;

            _str = new char[_capacity + 1];
            strcpy(_str, str);
        }

        string(const string& s) //深拷贝
        {
            _size = s.size();
            _capacity = s.capacity();
            _str = new char[_capacity + 1];
            strcpy(_str, s._str);
        }

        //复制拷贝
        string& operator=(const string& s)
        {
            if (this != &s)
            {
                _size = s.size();
                _capacity = s.capacity();
                char* tmp_str = new char[_capacity + 1];
                delete[] _str;
                _str = tmp_str;
                tmp_str = nullptr;
                return *this;
            }

        }

        ~string()
        {
            delete[] _str;
            _str = nullptr;
            _size = _capacity = 0;
        }

        iterator begin() const
        {
            return _str;
        }

        iterator end() const
        {
            return _str + size();
        }

        size_t size() const
        {
            return _size;
        }

        size_t capacity() const
        {
            return _capacity;
        }

        char& operator[](size_t i)
        {
            assert(i < _size);
            return _str[i];
        }

        const char& operator[](size_t i) const
        {
            assert(i < _size);
            return _str[i];
        }

        const char* c_str() const
        {
            return _str;
        }


        void push_back(const char ch)
        {
            /* 空间满了增容 */
            if (_capacity == _size)
            {
                size_t newcapacity = (_capacity == 0) ? 2 : (_capacity * 2); //保证_capacity一开始为0时候能有2byte空间
                char* str_tmp = new char[newcapacity + 1];
                strcpy(str_tmp, _str);
                delete[] _str;
                _str = str_tmp;
                str_tmp = nullptr;
                _capacity = newcapacity;
            }

            _str[_size] = ch;
            _size++;
        }


        void append(const char* str)
        {
            size_t len = strlen(str);
            /* 增容 */
            if (_size + len > _capacity)
            {
                size_t newcapacity = _size + len;
                char* str_tmp = new char[newcapacity + 1];
                strcpy(str_tmp, _str);
                delete[] _str;
                _str = str_tmp;
                str_tmp = nullptr;
                _capacity = newcapacity;
            }

            strcpy(_str + _size, str);
            _size += len;
        }

    private:
        char* _str;
        size_t _size;   //已经有多少个有效字符     '\0'不算有效字符
        size_t _capacity;   //能存多少个有效字符 
    };

    //operator<<
    std::ostream& operator<<(std::ostream& out, const string& s)
    {
        for (size_t i = 0;i < s.size();++i)
        {
            cout << s[i];
        }
        return out;
    }

    //operator>>
    std::istream& operator>>(std::istream& in, string& s)
    {

    }


    void test_string1()
    {
        string s1;
        string s2("hello");
        cout << s2;
    }

    //三种遍历方式
    void test_string2()
    {
        string s1("hello");

        for (size_t i = 0;i < s1.size();++i)
        {
            cout << s1[i] << ' ';
        }
        cout << endl;

        string::iterator s1_it = s1.begin();
        while (s1_it != s1.end())
        {
            (*s1_it)--;
            cout << *s1_it;
            s1_it++;
        }
        cout << endl;

        //范围for是由迭代器支持的，这段代码最终会被编译器替换为迭代器
        //iterator begin() end()
        for (auto ch : s1)
        {
            cout << ch << ' ';
        }

    }

    void test_string3()
    {
        string s1("hello");
        cout << s1 << endl;
        s1.push_back('w');
        cout << s1;
    }

}


#endif /* __STING2_H__ */