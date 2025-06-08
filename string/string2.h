#ifndef __STING2_H__
#define __STING2_H__

#include <string.h>
#include <assert.h>


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

        void reserve(size_t n)
        {
            if (n > _capacity)
            {
                char* str_tmp = new char[n + 1];
                strcpy(str_tmp, _str);
                delete[] _str;
                _str = str_tmp;
                str_tmp = nullptr;
                _capacity = n;
            }
        }

        void push_back(const char ch)
        {
            /* 空间满了增容 */
            if (_capacity == _size)
            {
                size_t newcapacity = (_capacity == 0) ? 2 : (_capacity * 2); //保证_capacity一开始为0时候能有2byte空间
                reserve(newcapacity);
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
                reserve(newcapacity);
            }

            strcpy(_str + _size, str);
            _size += len;
        }

        //s+='a'
        string& operator+=(const char ch)
        {
            push_back(ch);
            return *this;
        }

        //s+="hello"
        string& operator+=(const char* str)
        {
            append(str);
            return *this;
        }

        string& insert(size_t pos, char ch)
        {
            assert(pos <= _size);
            if (_capacity == _size)
            {
                size_t newcapacity = 2 * _capacity + 1;
                reserve(newcapacity);
            }

            size_t end = size();  //从'/0'开始挪
            while (end >= pos)
            {
                _str[end + 1] = _str[end];
                end--;
            }
            _str[pos] = ch;
            _size++;

            return *this;
        }

        string& insert(size_t pos, const char* str)
        {
            assert(pos <= _size);
            size_t len = strlen(str);
            if (_size + len > _capacity)
            {
                size_t newcapacity = _size + len;
                reserve(newcapacity);
            }

            int end = size();

            while (end >= pos)
            {
                _str[end + len] = _str[end];
                --end;
            }

            strncpy(_str + pos, str, len);
            _size += len;
            return *this;
        }

        void resize(size_t n, char c = '\0')
        {
            //截断
            if (n < _size)
            {
                _size = n;
                _str[_size] = '\0';
            }
            //拓展
            else
            {
                if (n > _capacity)
                {
                    reserve(n);
                }

                for (size_t i = _size;i < n;++i)
                {
                    _str[i] = c;
                }
                _size = n;
            }
        }

        string& erase(size_t pos = 0, size_t len = npos)
        {
            assert(pos < _size);
            if (len >= _size - pos)
            {
                _str[pos] = '\0';
                _size = pos;
            }
            else
            {
                size_t end = pos + len;
                while (end <= _size)
                {
                    _str[end - len] = _str[end];
                    ++end;
                }
                _size -= len;
            }
            return *this;
        }

        size_t find(char c, size_t pos = 0) const
        {
            assert(pos < _size);

            for (size_t i = pos;i < _size;++i)
            {
                if (_str[i] == c)
                    return i;
            }
            return npos;
        }

        size_t find(const char* s, size_t pos = 0) const
        {
            const char* sub = strstr(_str, s);
            if (!sub)
                return npos;
            else
                return sub - _str;
        }

        bool operator<(const string& s) const
        {
            int ret = strcmp(_str, s._str);
            return ret < 0;
        }

        bool operator==(const string& s) const
        {
            int ret = strcmp(_str, s._str);
            return (ret == 0);
        }

        bool operator<=(const string& s) const
        {
            return (*this < s) || (*this == s);
        }

        bool operator>(const string& s) const
        {
            return !(*this <= s);
        }

        bool operator>=(const string& s) const
        {
            return !(*this < s);
        }

        bool operator!=(const string& s) const
        {
            return !(*this == s);
        }
    private:
        char* _str;
        size_t _size;   //已经有多少个有效字符     '\0'不算有效字符
        size_t _capacity;   //能存多少个有效字符 
        static size_t npos;
    };

    size_t nanase::string::npos = -1;

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
        char ch = 0;
        while (1)
        {
            ch = in.get();
            if (ch == ' ' || ch == '\n')
                break;
            else
                s += ch;
        }
        return in;
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
        s1 += 'w';
        cout << s1 << endl;
        s1 += "orld";
        cout << s1 << endl;
        s1 += 'b';
        cout << s1 << endl;

    }

    void test_string4()
    {
        string s1;
        s1 += "aaaa";
        s1 += ' ';
        s1 += "bbbb";
        cout << s1;
    }

    void test_string5()
    {
        string s("hello");
        cout << s << endl;
        s.insert(3, "ggg");
        cout << s << endl;
    }

    void test_string6()
    {
        string s("hello");
        cout << s.size() << '\t' << s.capacity() << endl;
        s.resize(2);
        cout << s.size() << '\t' << s.capacity() << endl;
        s.resize(10, 'a');
        cout << s.size() << '\t' << s.capacity() << endl;

    }

    void test_string7()
    {
        string s("helloworld");
        // cout << s << endl;
        // s.erase(2, 2);
        // cout << s << endl;
        // s.erase(3);
        // cout << s << endl;

        cout << s.find("owo") << endl;
        cout << s.find("ord") << endl;
    }

    void test_string8()
    {
        string s;
        cin >> s;
        cout << s;
    }

}


#endif /* __STING2_H__ */