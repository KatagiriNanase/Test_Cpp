/**
 *@file vector.h
 * @author nanase
 * @brief Simulate the implementation of vector
 * @version 0.1
 * @date 2025-06-09
 *
 *
 */
#pragma once
#include <string.h>
#include <assert.h>
template<class T>
class vector
{
public:
    typedef T* iterator;
    typedef const T* const_iterator;
    vector()
        :_start(nullptr)
        , _finish(nullptr)
        , _end_of_storage(nullptr)
    {

    }

    /*     vector(const vector<T>& v)
            :_start(new T[v.capacity()])
            , _finish(_start)
            , _end_of_storage(_start + v.capacity())
        {
            for (size_t i = 0;i < v.size();++i)
            {
                *_finish = v[i];
                ++_finish;
            }
        } */

    vector(const vector<T>& v)
        :_start(nullptr)
        , _finish(nullptr)
        , _end_of_storage(nullptr)
    {
        reserve(v.capacity());
        for (auto& e : v)
            push_back(e);
    }

    ~vector()
    {
        delete[] _start;
        _start = _finish = _end_of_storage = nullptr;
    }

    size_t size() const
    {
        return _finish - _start;
    }

    size_t capacity() const
    {
        return _end_of_storage - _start;
    }

    iterator begin()
    {
        return _start;
    }

    iterator end()
    {
        return _finish;
    }

    const_iterator begin() const
    {
        return _start;
    }

    const_iterator end() const
    {
        return _finish;
    }

    void reserve(size_t n)
    {
        if (n > capacity())
        {
            T* tmp = new T[n];
            size_t tmpSize = size();
            //size_t tmpCapacity = capacity();
            if (_start)     //考虑第一次增容的时候：不是空指针在搬数据，不然就直接用tmp
            {
                // memcpy(tmp, _start, sizeof(T) * capacity()); 按字节拷贝，浅拷贝
                for (size_t i = 0;i < tmpSize;++i)
                {
                    tmp[i] = _start[i]; //用string类赋值string类 调用T的operator= 深拷贝
                }
                delete[] _start;
            }

            _start = tmp;
            _finish = _start + tmpSize;
            // _end_of_storage = _start + tmpCapacity;
            _end_of_storage = _start + n;

        }
    }

    void push_back(const T& x)
    {
        /*      if (_finish == _end_of_storage)
             {
                 size_t newcapacity = capacity() == 0 ? 2 : 2 * capacity();
                 reserve(newcapacity);
             }
             *_finish = x;
             _finish++; */
             //相当于insert尾插
        insert(_finish, x);
    }

    void pop_back()
    {
        assert(_start < _finish);
        erase(_finish - 1);
    }

    void insert(iterator pos, const T& x)
    {
        assert(pos <= _finish);

        //记录pos的偏移值
        size_t offset = pos - _start;

        //容量不够增容，此时pos失效
        if (_finish == _end_of_storage)
        {
            size_t newcapacity = capacity() == 0 ? 2 : 2 * capacity();
            reserve(newcapacity);

            //重新计算pos的位置
            pos = _start + offset;
        }
        iterator end = _finish;

        //从end开始搬数据，pos位置的也要往后搬
        while (pos <= end)
        {
            *(end + 1) = *end;
            end--;
        }
        *pos = x;
        _finish++;

    }

    iterator erase(iterator pos)
    {
        assert(pos >= _start && pos < _finish);

        iterator it = pos;
        while (it != _finish)
        {
            *it = *(it + 1);
            it++;
        }
        _finish--;

        return pos;
    }

    void resize(size_t n, const T& val = T())   //T()是类型T的默认构造值，可以把他当成匿名对象
    {
        if (n > capacity())
        {
            iterator tmp = _finish;
            reserve(n);
            while (_finish < _end_of_storage)
            {
                *_finish = val;
                _finish++;
            }
        }
        else
        {
            if (n > size())
            {
                while (_finish < _start + n)
                {
                    *_finish = val;
                    _finish++;
                }
            }
            else
            {
                _finish = _start + n;
            }
        }
    }

    T& operator[](size_t i)
    {
        assert(i >= 0 && i < size());
        return _start[i];
    }

    const T& operator[](size_t i) const
    {
        assert(i >= 0 && i < size());
        return _start[i];
    }

    /*     vector<T>& operator=(const vector<T>& v)
        {
            if (this != &v)
            {
                delete[] _start;
                _start = new T[v.capacity()];
                memcpy(_start, v._start, sizeof(T) * v.size());
                _finish = _start + v.size();
                _end_of_storage = _start + v.capacity();
            }
            return *this;

        } */
        //现代写法
    vector<T>& operator=(vector<T> v)
    {
        swap(v);
        return *this;
    }


    void swap(vector<T>& v)
    {
        std::swap(_start, v._start);
        std::swap(_finish, v._finish);
        std::swap(_end_of_storage, v._end_of_storage);
    }

private:
    iterator _start;
    iterator _finish;
    iterator _end_of_storage;
};