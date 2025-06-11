#ifndef __LIST_H__
#define __LIST_H__

/* 类模板：链表节点 */
template<class T>
struct __list_node
{
    __list_node(const T& x = T())
        :_next(nullptr)
        , _prev(nullptr)
        , _data(x)
    {

    }

    __list_node<T>* _next;
    __list_node<T>* _prev;
    T _data;
};

/*---------- List迭代器 -----------*/
template<class T>
struct __list_iterator
{
    typedef __list_node<T> Node;
    /* 成员变量 */
    Node* _node;

    /* 构造迭代器 */
    __list_iterator(Node* node)     //拿节点指针就能够构造迭代器
        :_node(node)
    {

    }

    T& operator*()
    {
        return _node->_data;
    }

    //++it
    __list_iterator<T>& operator++()
    {
        _node = _node->_next;
        return *this;
    }

    /*     //it++
        __list_iterator<T> operator++(int)
        {
            __list_iterator<T> ori_it = *this;
            _node = _node->_next;
            return ori_it;
        } */

        //it!=
    bool operator!=(const __list_iterator<T>& it) const
    {
        return _node != it._node;
    }

    //it==
    bool operator==(__list_iterator<T>& it) const
    {
        return _node == it._node;
    }

    //it->
    T* operator->()
    {
        return &_node->_data;
    }

};


/*---------- 自定义list -----------*/
template<class T>
class list
{
public:
    typedef __list_node<T> Node;
    typedef __list_iterator<T> iterator;
public:
    //带头双向循环链表
    list()
    {
        _head = new Node;
        _head->_next = _head;
        _head->_prev = _head;
    }

    void push_back(const T& x)
    {
        /* 备份原尾节点 */
        Node* tail = _head->_prev;
        Node* newcode = new Node(x);

        tail->_next = newcode;
        newcode->_prev = tail;
        newcode->_next = _head;
        _head->_prev = newcode;
    }

    iterator begin() { return iterator(_head->_next); }   //匿名对象创建iterator

    //返回值不能为引用，因为匿名对象生命周期只在当前行，不能被绑定到iterator&上
    iterator end() { return iterator(_head); }
private:
    Node* _head;

};
#endif /* __LIST_H__ */