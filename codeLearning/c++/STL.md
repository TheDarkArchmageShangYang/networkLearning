# STL

## 模板

为了减少重复工作

模板分为函数模板和类模板

### 函数模板

建立一个通用函数,其函数返回值类型和形参类型不指定,用虚拟类型代表

#### 语法

```c++
template<typename T>
函数声明或定义
```

- template声明创建模板
- typename表示后面的符号是一种数据类型,可以用class代替
- T通用数据类型,名称可以改

例如常见的交换函数

```c++
#include<iostream>
using namespace std;

void swapInt(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
} // 只适用于int类型

template<typename T>
void swap(T &a, T &b) {
	T temp = a;
	a = b;
	b = temp;
}

int main() {
    int a = 1, b =2;
    
    swapInt(a, b); // 正常方法
    swap(a, b); // 使用方法1,在传参时自动推导参数数据类型
    swap<int>(a, b); // 使用方法2,直接指定参数数据类型
    
    return 0;
}
```

注意事项:

1.自动类型推导时必须推导出一致的数据类型T,才能使用

2.模板必须确定T的类型才能使用,对于不需要传参的函数,只能使用第二种方法且必须指定,否则会报错

## 简介

STL(Standard Template Library,标准模板库)是c++标准库的一部分,不需要额外安装,只需要#include头文件.

STL六大组件:

容器(Container):各种数据结构,如动态数组(vector),单向链表(forward_list),双向链表(list),双端队列(deque),集合(set),映射(map)等

算法(Algorithm):各种常用算法,提供了执行各种操作的方式,包括对容器内容执行初始化,排序,搜索和转换等操作,如排序(sort),查找(find),copy,erase函数等

迭代器(Iterator):一种抽象的数据类型,用于访问容器中的元素

仿函数(Functor)

适配器(Adaptor)

分配器(allocator)

## 容器

容器分为序列式容器和关联式容器

序列式容器(Sequence containers):每个元素有固定位置,取决于插入时间和地点,和元素值无关,如vector,deque,list

- vector:动态数组
- forward_list:单向链表
- list:双向链表
- deque:双端队列
- priority_queue:优先级队列

关联式容器(Associated containers):元素位置取决与特定的排序原则,和插入顺序无关,如set,multiset,map,multimap

- set/multiset:有序集合,内部元素是一个值,根据元素值排序,set内相同数值的元素只能出现一次,multiset可以包含多个数值相同的元素,内部由二叉树实现
- map/multimap:有序映射,内部元素是键值对,根据元素键值排序,map内相同数值的元素只能出现一次,multimap可以包含多个数值相同的元素,内部由二叉树实现
- unordered_set:无序集合,元素顺序未定义
- unordered_map:无序映射,元素顺序未定义

注意:容器类自动申请和释放内存,无需new和delete

### vector

#### 介绍

vector为可以改变大小的数组容器

#### 实现原理

vector相当于一个动态数组,它的占用内存会随着数据的增多而进行扩容,每次扩容根据不同的操作系统变成原来的1.5/2倍.在进行扩容时会先在内存中找到一块满足需求的连续内存,把源数据拷贝到新内存块中,释放原内存.

vector存储了3个指针指向数组第一个元素,最后一个元素和已分配内存的末尾,所以在进行头部和尾部操作时时间复杂度为O(1),在进行数组中操作(如在第n个位置插入元素)时时间复杂度为O(n)

```
vector<int> vector1 = {1, 2, 3};
[ begin_ptr ] -> [ 1 ] [ 2 ] [ 3 ] [ _ ] [ _ ] <- capacity_ptr
                              ^
                              |
                         [ end_ptr ]
```



#### 常用操作

##### 头文件

```c++
#include <vector>
```

##### 构造&析构

==**一维初始化**==

```c++
// 构造空容器
vector<int> vector1;

// 构造具有n个val的容器
vector<int> vector1(10); // 定义一个长度为10的数组,初始值默认为0
vector<int> vector1(10, 1); // 定义一个长度为10的数组,初始值为1

// 根据迭代器构造容器
vector<int> vector1(vector2.begin(), vector2.begin()+3);
int num[5] = {1,2,3,4,5};
vector<int> vector1(num, num+5);

// 复制构造
vector<int> vector2(vector1);

// 移动构造
// 构造完成后,vector2拥有原vector1的内容(包括原来分配给vector1的内存),vector1为空
// 由于vector内部维护3个指针,分别指向第一个元素,最后一个元素和已分配内存的末尾.所以vector2只需要复制这三个指针,再重置vector1的3个指针
vector<int> vector2(std::move(vector1));

// 根据初始化列表构造容器
vector<int> a = {1,2,3,4,5};
```

==**二维初始化**==

```c++
// 行不可变,列可变
vector<int> a[5]; // 5行,列可变

// 行列均可变
vector<vector<int>> a;

// 行列均固定
vector<vector<int>> a(size1, vector<int>(size2, 0)) //有size1行,size2列,且初始值全为0
```

==**析构**==

```c++
~vector();
```



##### 迭代器

| 迭代器Iterators | 版本  | 返回值                                                       |
| --------------- | ----- | ------------------------------------------------------------ |
| begin()         | C++98 | 返回指向容器中第一个元素的迭代器                             |
| end()           | C++98 | 返回指向容器中最后一个元素后一个位置的迭代器<br />如果容器为空,end()=begin() |
| rbegin()        | C++98 | reverse_begin<br />返回指向最后一个元素的迭代器<br />这是反向迭代器,增加它会移向容器开头 |
| rend()          | C++98 | reverse_end<br />返回指向容器中第一个元素前一个位置的迭代器  |
| cbegin()        | C++11 | const_begin<br />返回指向容器中第一个元素的常量迭代器<br />begin()的const版本,可以移动,不能修改值 |
| cend()          | C++11 | const_end<br />返回指向容器中最后一个元素后一个位置的常量迭代器 |
| crbegin()       | C++11 | const_reverse_begin<br />返回指向最后一个元素的常量迭代器<br />rbegin()的const版本,可以移动,不能修改值 |
| crend()         | C++11 | const_reverse_end<br />返回指向容器中第一个元素前一个位置的常量迭代器 |



##### 容器容量

==**size()**==

返回实际元素数量

```c++
size_type size() const noexcept;
```

在不同位数的系统中,int等数据类型可能位数不同,所以需要使用size_t/size_type这样的数据类型来方便程序在不同系统中迁移.

在大多数情况下,size_type可以理解unsigned int(或unsigned long)



==**max_size()**==

返回容量的最大值,通常为$2^{31}-1$

```c++
size_type max_size() const noexcept;
```



==**resize()**==

调整容器大小，使其包含n个元素。
如果n小于当前元素数量，将容器缩减为其前n个元素，移除超出的元素
如果n大于当前元素数量，则通过在末尾插入足够多的元素来达到数量n。如果指定了val，则将新元素初始化为val的副本，否则，它们将被值初始化。
如果n大于当前容器容量，则自动重新分配已分配的存储空间。

```c++
void resize (size_type n);
void resize (size_type n, const value_type& val);
```



==**capacity()**==

返回当前容器容量
容量不一定等于元素个数。它可以相等或更大，额外的空间可以适应增长，而不需要在每次插入时重新分配。
当这个容量耗尽并且需要更多容量时，容器会自动扩展它（重新分配它的存储空间）。容量大小的理论限制由max_size给出。

```c++
size_type capacity() const noexcept;
```



==**empty()**==

判断容器中是否有元素,若无元素则返回true,有元素则返回false

```c++
bool empty() const noexcept;
```



==**reserve()**==

在当前容量不足n时,将容量设置为n

如果n小于当前容量,不会重新分配容量

如果n大于当前容量,重新分配存储空间,使容量增加到n

```c++
void reserve (size_type n);
```



==**shrink_to_fit()**==

将内存大小减少到当前元素实际所使用的大小

```c++
void shrink_to_fit();
```



##### 访问元素

==**operator[]**==

重载了[]运算符,可以与访问数组元素一样通过下标访问vector中的元素

如果超过边界,不会抛出异常,会导致未定义的行为



==**at()**==

使用经过边界检查的索引访问元素

如果超过边界,抛出out_of_range异常



==**front()**==

返回容器中第一个元素的引用

对空容器调用会导致未定义的行为



==**back()**==

返回容器中最后一个元素的引用

对空容器调用会导致未定义的行为



- []运算符访问

```c++
for (int i = 0; i < vector1.size(); i++) {
    cout << vector1[i] << endl; 
}
```

- 迭代器访问

```c++
// 迭代器访问方法1,不推荐,对vector适用,但对其他容器不一定适用
vector<int>::iterator it = vector1.begin();
for (int i = 0; i < vector1.size(); i++) {
    cout << *(it + i) << endl; // a[i]和*(a.begin()+i)等价
}

// 迭代器访问方法2
vector<int>::iterator it;
for (it = a.begin(); it != a.end(); it++) {
    cout << *it << endl;
}
```

- 智能指针

```c++
for (auto val : a) {
    cout << val << endl;
}
```



##### 修改元素

==**assign()**==

用新元素替换原有元素

```c++
// 替换容器内容为[first, last)
template <class InputIterator>
void assign (InputIterator first, InputIterator last);
// 替换容器内容为n个val
void assign (size_type n, const value_type& val);
// 替换容器内容为初始化列表
// C++11新特性,允许{}包裹一组值来初始化或赋值
// vector1.assign({1,2,3})
void assign (initializer_list<value_type> il);
```





==**push_back()**==

在尾部添加一个元素,值为val

```c++
void push_back (value_type&& val);
void push_back (const value_type& val);
```



==**pop_back()**==

删除尾部最后一个元素

```c++
void pop_back();
```



==**insert()**==

在指定位置插入一个元素或多个元素

```c++
// 在it插入val
iterator insert (const_iterator position, value_type&& val);
iterator insert (const_iterator position, const value_type& val);
// 在it插入n个val
iterator insert (const_iterator position, size_type n, const value_type& val);
// 在it插入[first,last)
// 例如要在vector1的开头插入vector2全部元素时
// vector1.insert(vector1.begin(), vector2.begin(), vector2.end());
template <class InputIterator>
iterator insert (const_iterator position, InputIterator first, InputIterator last);
// C++11新特性,按照初始化列表插入元素
// vector1.insert(vector1.begin(), {1,2,3});
iterator insert (const_iterator position, initializer_list<value_type> il);

```





==**erase()**==

移除一个元素或一定范围内的元素

```c++
iterator erase (const_iterator position);
iterator erase (const_iterator first, const_iterator last);

// 使用范例
vector<int> val = {1, 2, 3, 4, 5, 6};
val.erase(val.begin()+4); // {1,2,3,4,6}
val.erase(val.begin(), val.begin()+1); // {3,4,6}
```



==**swap()**==

交换两个容器的所有元素

```c++
void swap (vector& x);
```



==**clear()**==

移除容器中所有元素,元素个数变为0,不一定会改变容量

```c++
void clear() noexcept;
```



==**emplace()**==

在it前面插入一个元素

emplace()在插入元素时，是在容器的指定位置直接构造元素，而不是先单独生成，再将其复制（或移动）到容器中。优先使用emplace().

```c++
template <class... Args>
iterator emplace (const_iterator position, Args&&... args);

// 使用范例
vector<int> val = {1, 3, 4, 5, 6};
auto it = val.emplace(val.begin()+1, 2); // {1,2,3,4,5,6}
```



==**emplace_back()**==

在尾部插入一个元素

emplace_back()的执行效率比push_back()高。优先使用emplace_back().

例如现在`vector1 = {1,2,3}`,

`vector1.push_back(4)`将构造一个vector2为{1,2,3,4},然后让vector1=vector2

`vector1.emplace_back(4)`将直接在vector1中生成元素

```c++
template <class... Args>
void emplace_back (Args&&... args);

// 使用范例
vector<int> val = {1, 2, 4, 5, 6};
val.emplace(3); // {1,2,4,5,6,3}
```



##### 额外补充

1.

```c++
// 二维vector获取长度
int raw = a.size();
int column = a[0].size();
```

2.a.size()的数据类型是size_type,在64位系统中为long unsigned int(占用8字节),所以可能会出现

```c++
cout << a.size() << endl; // 输出2
cout << a.size() - 3 << endl // 输出18446744073709551615(2^64-1)
    
// 建议使用方法
int vectorSize = a.size();
```



### unordered_set

#### 介绍

unordered_set是无序集合

#### 常用操作

##### 头文件

```c++
#include <unordered_set>
using namespace std;
```

其他基本都和unordered_map相同

### unordered_map

#### 介绍

unordered_map为无序映射,是存储<key,value>键值对(std::pair类型)的关联式容器,其允许通过key快速地索引到对应的value.

在内部,unordered_map没有对<key,value>按照任何特定的顺序排序,为了在常数范围内找到key所对应的value,unordered_map将相同哈希值的键值对放在相同的桶里

map内部实现了一个红黑树,具有自动排序的功能,使用中序遍历可以把键值按照从小到大的顺序遍历.unordered_map内部实现了一个哈希表(散列表),将关键字映射到哈希表中的一个位置来访问记录,查找时间复杂度O(1)

| 映射          | 底层实现 | 是否有序 | 数值是否可以重复 | 能否更改数值 | 查询效率 | 增删效率 |
| ------------- | -------- | -------- | ---------------- | ------------ | -------- | -------- |
| map           | 红黑树   | key有序  | key不能重复      | key不能修改  | O(log n) | O(log n) |
| multimap      | 红黑树   | key有序  | key可重复        | key不能修改  | O(log n) | O(log n) |
| unordered_map | 哈希表   | key无序  | key不能重复      | key不能修改  | O(1)     | O(1)     |

#### 常用操作

##### 头文件

```c++
#include <unordered_map>
```

##### 定义

```c++
emplate <class Key, // 键值对中键的类型
class T, // 键值对中值的类型
class Hash = hash<Key>, // 容器内部存储键值对所用的哈希函数
class Pred = equal_to<Key>, // 判断各个键值对键相同的规则
class Alloc = allocator<pair<const Key,T>> // 指定分配器对象的类型
> class unordered_map;
```

前两个参数必须显式传值,除特殊情况外,最多只使用前4个参数

- <key,T>:确定键值对中键和值的类型
- Hash = hash\<key\>:指明容器在存储键值对时使用的哈希函数,默认使用STL标准库提供的hash\<key\>哈希函数,仅适用于基本数据类型(包括string)
- Pred = equal_to\<Key\>:指明容器中存储的各键值对判断是否相等的规则,默认使用STL标准库提供的equal_to\<Key\>规则,仅适用于可以直接用==比较的数据类型

总的来说,如果容器中存储的键值对的键为自定义类型时,默认的哈希函数和比较函数将不再使用,需要自己设计对应函数,并显式传递给Hash参数和Pred参数

##### 初始化

```c++
// 构造一个空容器
unordered_map <key, T> hash_map; // 形式
unordered_map <string, int> hash_map; // 范例

// 构造容器并赋值
unordered_map <string, int> hash_map{
    {"a", 1},
    {"b", 2},
    {"c", 3}
}; // 范例1
string s = "hello";
unordered_map <char, int> hash_map;
for (auto c : s) {
    map[c]++;
} // 范例2

// 拷贝构造一个容器
unordered_map <key, T> hash_map(hash_map1);

// 使用迭代器区间构造一个容器,使用其他容器(如vector)来可以,注意元素类型
unordered_map <key, T> hash_map(hash_map1.begin(),hash_map1.end());
```

##### 迭代器定义

```c++
unordered_map <Key, T>::iterator it;
(*it).first;             // the key value (of type Key)
(*it).second;            // the mapped value (of type T)
(*it);                   // the "element value" (of type pair<const Key,T>) 
```

##### 遍历

```c++
for (auto it = map.begin(); it != map.end(); it++) {
    if (it->second != 0){
        ...;
    }
}

for (auto it : map) {
    if (it.second != 0) {
        ...;
    }
}
```

注意:

- 基于迭代器遍历关联型容器时,auto推导出来是迭代器类型,需要用it->first,it->second取出键值对
- 基于范围的for循环遍历关联型容器时,auto推导出来是std::pair<key, value>类型,需要用it.first,it.second取出键值对

##### 方法函数

| 代码                   | 含义                                                         |
| ---------------------- | ------------------------------------------------------------ |
| a.size()               | 返回键值对个数                                               |
| a.max_size()           | 返回容器所能容纳键值对的最大个数                             |
| a.empty()              | 判断是否为空,为空返回true,否则返回flase                      |
| a.emplace(key,value)   | 在容器中添加键值对<key, value>                               |
| a.insert(it,key,value) | 向迭代器it插入一个键值对                                     |
| a.erase(it)            | 删除it指向的键值对,返回指向下一个元素的迭代器                |
| a.erase(key)           | 删除键为key的键值对,返回删除的元素数量,在map里非0即1         |
| a.begin()              | 返回第一个键值对的迭代器                                     |
| a.end()                | 返回最后一个键值对后一个位置的迭代器                         |
| a.cbegin()             | 和begin相同,但是增加了const属性,返回的迭代器不能用于修改键值对 |
| a.cend()               | 和cbegin()类似                                               |
| a.bucket_count()       | 返回容器中桶的数量                                           |
| a.max_bucket_count()   | 返回容器最多可以使用多少个桶                                 |
| a.bucket_size(n)       | 返回第n个桶中存储键值对的数量                                |
| a.bucket(key)          | 返回以key为键的键值对所在桶的编号                            |
| a.rehash(n)            | 将当前容器使用桶的数量设为n                                  |
| a.at(key)              | 返回容器中存储的键key对应的值,越界会抛出异常                 |
| a.find(key)            | 查询以key为键的键值对,如果存在则返回对应迭代器,否则返回最后一个键值对后一个位置的迭代器(end()方法返回的迭代器) |
| a.clear()              | 清空a中的元素                                                |
| a.count(key)           | 查询关键字为key的元素个数,非0即1                             |

注意在使用count或find进行判断时

```c++
if (myHashMap.count(i)) {...} // 正确
if (myHashMap.find(i)) {...} // 错误
if (myHashMap.find(i) != myHashMap.end()) {...} //正确
```



### set



## 算法

### 简介

STL的算法库提供了很多种算法,可以用来处理各种数据结构,例如数组,栈,队列等

#### 头文件

```c++
// <algorithm>是所有STL头文件中最大的一个,范围涉及比较,交换,查找,遍历,复制,修改等
#include <algorithm>

// <functional>定义了一些模板类,用以声明函数对象
#include <functional>

// <numeric>只包括几个在序列上进行简单数学运算的模板函数
#include <numeric>
```

### 遍历算法

#### **for_each**

**功能:遍历容器**

**函数原型**

```c++
#include <algorithm>

for_each(iterator begin, iterator end, func); // 遍历容器元素
```

例子

```c++
vector<int> myVector{1, 2, 3, 4, 5};

void print1(int val) {
    cout << val << endl;
}

for_each(myVector.begin(), myVector.end(), print1);
```

### 查找算法

#### **find**

**功能:按值查找元素,找到则返回该元素的迭代器,找不到则返回end()返回的迭代器**

**函数原型**

```c++
#include <algorithm>

find(iterator begin, iterator end, value);
```

例子

```c++
vector<int> myVector{1, 2, 3, 4, 5};

auto it = find(myVector.begin(), myVector.end(), 5);
```

#### count

**功能:统计元素个数,返回元素个数**

**函数原型**

```c++
#include <algorithm>

count(iterator begin, iterator end, value);
```

例子

```c++
vector<int> myVector{1, 2, 3, 4, 5};

int num = find(myVector.begin(), myVector.end(), 5);
```

## 适配器

### 简介

如果类(或函数)的成员,功能与类(或函数)B类似,但有一些不同,可以通过封装B来实现A,从而把B的接口转化为A的接口.

STL的适配器分为三类:

- 容器适配器
- 仿函数适配器
- 迭代器适配器

### 容器适配器

STL提供的栈和队列并不是容器,而是容器适配器.stack和queue封装其他容器,修饰其接口来满足逻辑结构(stack先入后出,queue先入先出)的需求.

默认情况下,底层容器使用deque(双端队列)来实现stack和queue.

**deque的缺点**

- 随机访问效率低(由于其分段式的结构,使其在跨越不同缓冲区的时候会消耗时间,导致效率低)
- 不适合遍历(在遍历时需要频繁检测迭代器是否到达某个缓冲区的边界,导致效率低)

**deque的优点**

- 相比于vector,deque减少了空间浪费(在数据量较少,deque数据集中在几个缓冲区,可以基本忽略缺点;头插和头删的效率远高于vector)
- 相比于list,deque支持随机访问,且空间利用率比较高

**为什么用deque作为stack和queue的底层容器**

- stack和queue都只能在两端访问数据,stack先进先出,queue先进后出,都不支持遍历和随机读取.所以deque的缺点都不会体现
- deque支持头插尾插,头删尾删(且效率高于vector).提供"整体连续的空间,提高了空间的使用率(vector有空间冗余,list需要存储额外字段)

#### stack

stack是栈

主要API:

容器容量:size(),empty()

访问元素:top()

修改元素:push(item),emplace(item),pop()

**头文件**

```c++
#include <stack>
```

**构造函数**

```c++
```





#### queue

queue是队列

主要API:

容器容量:size(),empty()

访问元素:front(),back()

修改元素:push(item),emplace(item),pop()

**头文件**

```c++
#include <queue>
```

**构造函数**

```c++
```





#### priority_queue

priority_queue是优先级队列

主要API:

容器容量:size(),empty()

访问元素:top()

修改元素:push(item),emplace(item),pop()

**头文件**

```c++
#include <queue>
```

**构造函数**

```c++
// 构造一个int优先队列
// 优先队列默认使用vector作为底层容器,使用其他容器需要指定
// 优先队列默认使用less<int>(大顶堆)作为排序方法,使用greater<int>(小顶堆)需要指定
priority_queue<int, deque<int>, less<int>> pq;
priority_queue<int> pq;

// 构造一个结构体优先队列
struct node {
    int index;
    int val;
    bool operator < (const node b) const { return index < b.index; }
}
priority_queue<node> pq;

// 构造自定义类型的优先队列
struct cmp {
    bool operator()(const ListNode* a, const ListNode* b) {
        // 小值优先
        // 如果返回true,则表示a的优先级低,b的优先级高
    	return a->val > b->val;
	}
}
// ListNode*表示优先队列中存储的元素类型
// vector<ListNode*>表示存储 ListNode* 指针的容器类型
// cmp表示优先队列的比较器
priority_queue<ListNode*, vector<ListNode*>, cmp> pq;

// 使用lambda表达式构造自定义类型的优先队列
auto cmp = [](const ListNode* a, const ListNode* b) {
    return a->val > b->val;
}
priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> pq;

// 有捕获的lambda表达式
auto cmp = [&nums](const int& a, const int& b) {
    return nums[a] > nums[b];
};
priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);
```
