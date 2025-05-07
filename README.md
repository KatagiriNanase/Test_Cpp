# Test For Cpp

>学嵌入式的茶余饭后小甜点 ((´・ω・)つ旦)   
让我慢慢品味Cpp的语法糖吧

## 类与对象 

> "类什么的...最讨厌了喵...（趴"


1. **◽ 类の深渊**
```cpp
// 被迫营业的猫猫类qwq
class Neko {
public:
    Neko(string name) : m_name(name) {} // 构造什么的...手在抖喵...
private:
    string m_name; // 又要管理内存什么的...
};
```

2. **◽ 范围forの魔法**
```cpp
vector<int> v = {1,2,3};
// 自动模式启动...（眼神死
for(auto &n : v){
    cout << n << " "; // 手指已经不听使唤了喵...
}
```

引用还是蛮甜的……   

2025年5月7日
***
