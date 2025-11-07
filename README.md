# C++ 学习笔记

>学嵌入式的茶余饭后小甜点 ((´・ω・)つ旦)   
让我慢慢品味Cpp的语法糖吧

## 类与对象

### 1. 类的基本概念
```cpp
// 基础的类定义示例
class Neko {
public:
    Neko(string name) : m_name(name) {} // 构造函数
private:
    string m_name; // 成员变量
};
```

### 2. 范围for循环
```cpp
vector<int> v = {1, 2, 3};
// 使用auto关键字自动推导类型
for(auto &n : v){
    cout << n << " ";
}
```

引用机制提供了更高效的访问方式。

2025年5月7日
***

### 3. 构造函数与析构函数
```cpp
class TimeKeeper {
public:
    // 默认构造函数
    TimeKeeper() = default;
    
    // 带参数构造函数
    TimeKeeper(int h, int m) : hour(h), minute(m) {}
    
    // 析构函数
    ~TimeKeeper() { cout << "对象生命周期结束" << endl; }
};
```

### 4. 拷贝控制
```cpp
// 拷贝构造函数
TimeKeeper::TimeKeeper(const TimeKeeper& tk) {
    hour = tk.hour + 1;  // 深度拷贝示例
}

// 赋值运算符重载
TimeKeeper& operator=(const TimeKeeper& tk) {
    if(this != &tk) {  // 自赋值检查
        hour = tk.hour;
    }
    return *this;
}
```

### 5. Const成员函数
```cpp
int getHour() const { 
    // const成员函数保证不修改对象状态
    return hour * 60;  // 返回分钟数
}
```

### 重要事项
| 概念                | 注意事项                      |
|---------------------|-----------------------------|
| 默认拷贝构造        | 浅拷贝可能引发内存问题        |
| 赋值运算符          | 必须检查自赋值情况            |
| const成员函数       | 保证对象状态不被修改          |

***

### 6. explicit关键字
```cpp
explicit A(int a) :_a(a) {} 
// 阻止隐式类型转换
```

### 7. 成员初始化列表
```cpp
B(int a, int& ref) 
    : _aobj(a)    // 成员初始化
    , _ref(ref)   // 引用成员初始化
    , _n(a) {}    // 普通成员初始化
```

### 8. 友元函数
```cpp
friend ostream& operator<<(...);
// 允许外部函数访问私有成员
```

### 常见编程问题
| 问题类型        | 解决方案                  |
|----------------|--------------------------|
| 忘记explicit   | 在构造函数前添加explicit  |
| 初始化顺序错误  | 严格按照声明顺序初始化    |
| 友元滥用        | 谨慎使用友元关系          |

---

### 特别注意事项
`TestE()`中存在隐式转换风险  
`Solution s1 = 10` 这种写法可能产生非预期行为

### 编程指南
1. 构造函数前考虑使用explicit关键字
2. 成员初始化列表顺序与声明顺序保持一致
3. 注意匿名对象的生命周期管理

2025年5月22日
***   

## 内存管理

### 1. new操作符
```cpp
A* p3 = new A;  
// 完成两个操作：
// 1. 调用operator new分配内存
// 2. 调用构造函数初始化对象
```

### 2. 定位new
```cpp
new(p1)A;   // 在已分配内存上构造对象
p1->~A();   // 显式调用析构函数
```

### 内存操作解析
#### new操作分解
```cpp
A* p3 = new A;  
// 等价于：
// 1. void* memory = operator new(sizeof(A))
// 2. A* obj = static_cast<A*>(memory)
// 3. obj->A()  // 调用构造函数
```

#### malloc函数
```cpp
A* p1 = (A*)malloc(sizeof(A));  
// 仅分配原始内存，不调用构造函数
```

#### delete操作分解
```cpp
delete p3;  
// 完成两个操作：
// 1. p3->~A()  // 调用析构函数
// 2. operator delete(p3)  // 释放内存
```   

#### 内存操作对比表
| 操作          | 功能描述                  | 注意事项                  |
|--------------|-------------------------|-------------------------|
| new          | 分配内存并构造对象        | 背后调用operator new+构造 |
| operator new | 原始内存分配              | 可被重载                |
| malloc       | C风格内存分配            | 不调用构造函数          |
| delete       | 析构对象并释放内存        | 先调用析构再释放内存    |
| free         | C风格内存释放            | 不调用析构函数          |

#### 数组内存管理
```cpp
void Test4() {
    A* arr2 = new A[4];     // 分配对象数组
    delete[] arr2;          // 必须使用delete[]
}
```

#### 安全的内存使用模式
```cpp
// 推荐用法
auto* safe_obj = new ClassName(args...);
// ... 使用对象
delete safe_obj;

// 高级用法（需谨慎）
void* raw_mem = operator new(1024);
new(raw_mem) DangerousClass;
```

### 技术要点
- operator new可以重载以实现自定义内存管理
- malloc/free不调用构造/析构函数
- new[]必须与delete[]配对使用
- 定位new适用于内存池等高级场景

2025年5月23日
***

## 模板编程

### 1. 函数模板
```cpp
template<typename T>
T Add(const T& a, const T& b) {
    return a + b;
}
```

#### 1.1 实例化方式
- **隐式实例化**：`Add(1.1, 2.2)` 编译器自动推导为`double`类型  
- **显式实例化**：`Add<double>(1, 2.2)` 显式指定模板类型  
- **匹配优先级**：普通函数 > 模板特化函数

#### 1.2 类型匹配
```cpp
Add(a1, d1);  // 错误：类型不一致
Add(a1, (int)d1);  // 正确：显式类型转换
```

### 2. 类模板
```cpp
template<class T>
class Stack_CPP {
    ~Stack_CPP() { delete[] _a; }  // 资源管理
};
```

#### 2.1 模板类优势
| C实现限制              | C++模板类解决方案           |
|-----------------------|---------------------------|
| 类型特异性             | `Stack_CPP<int>/<double>`  |
| 数据封装性差           | private访问控制           |
| 手动资源管理           | 构造/析构自动管理         |

#### 2.2 常见错误
```cpp
stack_cpp_double.~Stack_CPP();  // 错误：手动调用析构函数
```

---

#### 3. Vector模板实现
```cpp
template<class T>
void vector<T>::push_back(const T& x) {
    if(_size == _capacity) {
        // 注意：避免使用memcpy进行浅拷贝
    }
}
```

##### 3.1 核心设计
- **动态扩容**：容量按指数增长策略
- **元素访问**：`operator[]`返回引用
- **安全机制**：边界检查断言

##### 3.2 拷贝问题
```cpp
memcpy(tmp, _a, sizeof(T)*_size);  // 错误：对自定义类型不安全
```

---

#### 4. 模板编程规范
##### 4.1 基本规则
- 类外定义成员函数需包含模板前缀
- 模板声明与实现应在同一文件
- 类型不匹配时需显式指定类型

##### 4.2 安全措施
```cpp
static_assert(!is_pointer<T>::value, "不支持指针类型"); 
```

2025年5月23日
***

## String类

### 1. 构造函数
```cpp
string s1;                // 默认构造
string s2("ikun");        // C字符串构造
string s3(5, '6');        // 填充构造
string s4(s3);            // 拷贝构造
```

#### 注意事项
- 拷贝构造执行深拷贝
- `string(nullptr)` 导致未定义行为

---

### 2. 容量操作
```cpp
s.size();      // 当前元素数量（不包含终止符）
s.capacity();  // 分配的内存容量
s.empty();     // 判断是否为空
s.clear();     // 清空内容
s.reserve(100); // 预分配内存
s.resize(10);   // 调整大小
```

#### 容量管理
- `reserve` 只影响容量，不影响内容
- `resize` 会改变字符串长度和内容

---

### 3. 元素访问
```cpp
s[0] = 'A';                    // 下标访问
for(auto& ch : s) ch += 1;     // 范围for循环
auto it = s.begin();           // 迭代器访问
*it = 'S';                     // 通过迭代器修改
```

#### 迭代器类型
```cpp
s.rbegin();  // 反向迭代器
s.rend();    // 反向迭代器终点
```

---

### 4. 字符串操作
```cpp
s.push_back('!');       // 尾部添加字符
s.append("qwq");        // 追加字符串
s += "xxx";             // 字符串连接
const char* cp = s.c_str(); // 获取C风格字符串
s.find("na");           // 子串查找
s.substr(2, 5);        // 提取子串
```

#### 使用注意
- `c_str()` 返回指针可能失效
- `find` 失败返回 `string::npos`
- 注意字符串操作的性能影响

---

### 5. 输入输出
```cpp
string s = "ikun" + string(" loves cpp"); // 字符串连接
cin >> s;               // 输入操作
cout << s;              // 输出操作
getline(cin, s);        // 读取整行
if(s1 < s2) ...        // 字典序比较
```

#### 操作特性
- `operator+` 产生新字符串对象
- `getline` 会消耗输入流中的换行符
- 比较操作区分大小写

### 技术细节
`s[s.size()]` 返回终止符 `'\0'`，但修改此位置是未定义行为。

2025年5月27日
***

## 继承

### 继承基础概念
```cpp
class Base {};  
class Derived : public Base {};  
```
- **派生类**继承**基类**的成员变量和方法，实现代码复用
- 访问控制：
  - `public继承`：基类public→派生类public，protected→派生类protected
  - `protected继承`：基类成员在派生类中变为protected
  - `private继承`：基类成员在派生类中变为private（默认方式）

### 赋值兼容性
```cpp
Base* ptr = &derived_obj;  // 正确：向上转型
// Derived* ptr = &base_obj; 错误：向下转型需要显式转换
```
- **向上转型**：派生类对象可以视为基类对象
- **向下转型**：需要使用`dynamic_cast`且基类需包含虚函数

### 函数重写与虚函数
```cpp
class BaseClass {
public:
    virtual void display() { cout << "Base implementation"; }
};

class DerivedClass : public BaseClass {
public:
    void display() override { cout << "Derived implementation"; }
};
```
- **函数遮蔽**：派生类同名函数隐藏基类函数
- **虚函数**：基类使用`virtual`，派生类建议使用`override`

### 多重继承
```cpp
class Employee {};
class Engineer {};
class Developer : public Employee, public Engineer {};
```
- **菱形继承问题**：
```cpp
class Human {};
class Employee : virtual public Human {};   // 虚继承
class Engineer : virtual public Human {};    
```
- 虚继承确保最基类在派生类中只有一份实例

### 构造顺序
构造顺序：`基类构造 → 成员对象构造 → 派生类构造`  
析构顺序与构造顺序相反

2025年6月8日
***

## 多态

### 多态概念
```cpp
class Base {
public:
    virtual void behavior() { cout << "Base behavior"; }
};

class Derived : public Base {
public:
    void behavior() override { cout << "Derived behavior"; }
};

void demonstrate(Base* obj) {
    obj->behavior(); // 根据实际对象类型调用相应实现
}
```
- **定义**：同一接口在不同对象上呈现不同行为
- **意义**：提高代码灵活性和可扩展性

### 多态实现条件
1. **继承关系**：派生类继承基类
2. **虚函数重写**：派生类覆盖基类虚函数
3. **指针/引用调用**：通过基类指针或引用操作派生类对象
```cpp
Base* obj = new Derived();
obj->behavior();  // 触发多态

Derived temp;
temp.behavior(); // 不触发多态
```

### 虚函数机制
```cpp
class AbstractBase {
public:
    virtual void pure_virtual() = 0; // 纯虚函数
    virtual void default_impl() { cout << "Default implementation"; } 
    virtual ~AbstractBase() {} // 虚析构函数
};
```
- **virtual关键字**：启用动态绑定
- **纯虚函数**：
  - `virtual 返回类型 函数() = 0;`
  - 包含纯虚函数的类为抽象类
- **性能考量**：每个对象增加虚表指针开销

### 虚函数重写要求
| 要素        | 要求                      | 常见错误       |
|-------------|--------------------------|----------------|
| 函数签名    | 完全一致                 | 参数类型错误   |
| 返回类型    | 协变允许返回派生类型     | 返回类型不匹配 |
| const限定   | 必须一致                 | 遗漏const      |
| override    | C++11建议使用            | 未使用override |

```cpp
class ErrorExample : public AbstractBase {
public: 
    void pure_virtual(int) override; // 错误：签名不同
    void default_impl() const override; // 错误：const修饰符不一致
};
```

### 重载/覆盖/隐藏对比
| 类型 | 作用域     | 要求                  | 多态性 | 示例 |
|------|------------|-----------------------|-------|------|
| 重载 | 同一类中   | 函数参数不同          | 否    | `void f(int); void f(double);` |
| 覆盖 | 继承关系   | 虚函数+相同签名       | 是    | `virtual void vf() override;` |
| 隐藏 | 继承关系   | 非虚函数/参数不同     | 否    | 基类函数被派生类同名函数隐藏 |

### 抽象类
```cpp
class AbstractClass {
public:
    virtual void interface() = 0; // 纯虚函数
    virtual ~AbstractClass() {} // 虚析构函数
};

class ConcreteClass : public AbstractClass {
public:
    void interface() override { cout << "Concrete implementation"; }
};
```
- **核心特征**：至少包含一个纯虚函数
- **设计目的**：定义接口规范，强制派生类实现
- **使用限制**：不能实例化抽象类

### 多态原理分析

#### 虚函数表(vtable)
```cpp
// 编译器生成的虚函数表结构
struct Base_VTable {
    void (*behavior)(Base*); // 函数指针
    // ...其他虚函数
};

// 对象内部结构
class Base {
private:
    Base_VTable* __vptr; // 指向虚函数表
};
```

#### 动态绑定机制
```cpp
obj->behavior(); // 编译时转换为：
obj->__vptr[0](obj); // 通过虚表间接调用
```
- **动态绑定过程**：
  1. 通过对象地址获取虚表指针
  2. 在虚表中查找目标函数
  3. 传递this指针执行函数调用

#### 静态绑定
```cpp
Derived temp;
temp.behavior(); // 编译时确定函数地址
```
- **早绑定**：编译期解析函数地址
- **适用场景**：非虚函数调用
- **性能优势**：避免运行时查找开销

### 继承模型中的虚表结构

#### 单继承模型
```cpp
class BaseA {
public:
    virtual void func_a() {}
};

class DerivedA : public BaseA {
public:
    virtual void func_b() {}
    void func_a() override {}
};
```

#### 多重继承
```cpp
class InterfaceA {
public:
    virtual void method_a() {}
};

class InterfaceB {
public:
    virtual void method_b() {}
};

class Implementation : public InterfaceA, public InterfaceB {
public:
    void method_a() override {}
    void method_b() override {}
};
```

#### 虚继承
```cpp
class CommonBase {
public:
    virtual void common_method() {}
};

class Derived1 : virtual public CommonBase {};
class Derived2 : virtual public CommonBase {};

class FinalClass : public Derived1, public Derived2 {};
```

2025年6月8日
***

## Vector容器

### Vector接口概览

#### 容量管理
```cpp
size();      // 当前元素数量
capacity();  // 分配的内存容量
empty();     // 判断是否为空
resize(n);   // 调整元素数量
reserve(n);  // 预分配内存空间
```

#### 元素操作
```cpp
push_back(val);   // 尾部添加元素
pop_back();       // 删除尾部元素
insert(pos, val); // 指定位置插入
erase(pos);       // 删除指定元素
clear();          // 清空所有元素
operator[];       // 下标访问元素
at(i);            // 带边界检查的访问
```

---

### 迭代器失效问题

| 操作         | 失效范围                 | 后果             |
|--------------|--------------------------|------------------|
| `push_back`  | 容量不足时全部迭代器失效 | 未定义行为       |
| `insert`     | 插入点及之后的迭代器     | 数据访问错误     |
| `erase`      | 被删元素及之后的迭代器   | 悬垂指针访问     |

```cpp
// 迭代器失效示例
vector<int> v = {1, 2, 3};
auto it = v.begin() + 1;
v.insert(v.begin(), 0);
// it已失效，不能再使用
cout << *it; // 未定义行为
```

**正确做法**：修改容器后重新获取迭代器

---

### Vector实现原理

#### 核心数据结构
```cpp
template<class T>
class myvector {
private:
    T* _start;          // 数组起始位置
    T* _finish;         // 最后一个元素的下一个位置
    T* _end_of_storage; // 存储空间末尾
};
```

#### 关键方法实现
```cpp
void push_back(const T& val) {
    if (_finish == _end_of_storage) {
        reserve(capacity() == 0 ? 4 : capacity() * 2); // 动态扩容
    }
    *_finish = val; // 构造新元素
    _finish++;      // 更新尾指针
}

iterator erase(iterator pos) {
    assert(pos >= _start && pos < _finish); // 边界检查
    iterator it = pos + 1;
    while (it != _finish) {
        *(it - 1) = *it; // 前移元素
        it++;
    }
    _finish--; 
    return pos; // 返回新位置的迭代器
}
```

---

### 深拷贝问题

在实现**reserve**方法时的常见错误：

```cpp
// 错误实现 - 浅拷贝问题
void reserve(size_t n) {
    if (n > capacity()) {
        T* tmp = new T[n];
        if (_start) {
            memcpy(tmp, _start, sizeof(T) * size()); // 浅拷贝
            delete[] _start;
        }
        // ...更新指针
    }
}
```

#### 问题分析
1. **浅拷贝**：memcpy直接复制内存，对包含指针的类不安全
2. **资源管理**：新旧vector指向同一资源，导致双重释放
3. **对象语义**：破坏类的拷贝语义

#### 正确实现
```cpp
// 深拷贝实现
for(size_t i = 0; i < size(); i++) {
    tmp[i] = _start[i]; // 调用拷贝赋值运算符
}
```

**内存布局对比**：
```
错误做法（浅拷贝）：
原内存: [对象1] [对象2] → memcpy → 新内存: [相同资源指针1] [相同资源指针2]
                                      导致资源重复释放

正确做法（深拷贝）：
原内存: [对象1] [对象2] → 深拷贝 → 新内存: [新资源1] [新资源2]
                                      独立的资源管理
```

---

### 总结要点

1. **容量管理**：理解capacity与size的区别，合理预分配内存
2. **元素操作**：注意push_back/insert可能引发的扩容操作
3. **迭代器安全**：修改容器后必须重新获取迭代器
4. **资源管理**：实现容器时注意深拷贝与资源所有权

2025年6月11日
***