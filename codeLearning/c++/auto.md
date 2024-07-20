## 介绍

C++11引入了auto类型说明符,便于在不清楚变量类型是声明变量

## 推导规则

- 规则1：声明为auto(不是auto&)的变量，忽视掉初始化表达式的顶层const或volatile属性
  - 对有const的普通类型(int,double等)忽视const

  - 对常量指针(顶层const)变为普通指针

  - 对指向常量(底层const)的常量指针(顶层cosnt)变为指向常量的指针(底层const)

- 规则2：声明为auto&的变量，保留初始化表达式的顶层const或volatile属性
- 规则3：若希望auto推导的是顶层const,加上const,即const auto
- 规则4:如果初始化表达式是引用,则去除引用语义

顶层const和底层const详见const.md

### 例子

一般情况

```c++
int a = 0;

auto p = a; // p为int类型
auto p = &a; // p为int*类型
```

规则1情况

```c++
const int a = 0, b = 1;

auto p = a; // p为int类型,顶层const被忽略
p = 5; // p的值可以被改变

auto p1 = &a; // p1为const int*类型
p1 = 5; // 错误
p1 = &b; // 正确,p1的指向可以改
```

```c++
int a = 0;

int* const p1 = &a;
const int* p2 = &a;
const int* const p3 = &a;

auto p4 = p1; // p4为int*类型
auto p5 = p2; // p5为const int*类型
auto p6 = p3; // p6为const int*类型
```

规则2情况

```c++
int a = 0;
const int b = 0;

auto &p1 = a; // p1为int &类型
auto &p2 = b; // p2为const int &类型
auto &p3 = 10; // 错误,不能给非常量引用绑定值

const auto &p4 = a; // p3为const int &类型(由于规则3)
const auto &p5 = b; // p4为const int &类型(由于规则3)
const auto &p6 = 10; // 正确,可以给常量绑定值

auto &p7 = &a; // 错误,无法从int*转换为int* &
auto &p8 = &b; // 错误,无法从 const int*转换为从const int* &
const auto &p9 = &a; // p9为int* const &
const auto &p10 = &b; // p10为const int* const &
```

p7和p8错误的原因详见引用.md

规则3情况

```c++
int a = 0;
const int b = 0;

auto p1 = a; // p1为int类型
const auto p2 = a; // p2为const int类型
auto p3 = b; // p3为int类型
const auto p4 = b; // p4为const int类型

auto p5 = &a; // p5为int*类型
const auto p6 = &a; // p6为int* const类型
auto p7 = &b; // p7为const int*类型
const auto p8 = &b; // p8为const int* const类型
```

规则4情况

```c++
int a = 0;
int &b = a;

auto p1 = b; // p1为int类型
auto &p2 = b; // p2为int &类型
```



## 使用

1.代替冗长复杂的变量声明

通常在使用迭代器的时候使用

```c++
vector<int> a(10);

// 正常方法
for (vector<int>::iterator it = a.begin(); it != a.end(); it++) {
    cout << *it << endl;
}

// 使用auto
for (auto it = a.begin(); it != a.end(); it++) {
    cout << *it << endl;
}
```

2.使用模板参数时,用于声明依赖模板参数的变量

```c++
template <typename _Tx,typename _Ty>
void Multiply(_Tx x, _Ty y)
{
    auto v = x + y;
    cout << v << endl;
}
```

函数需要获取x+y的值,但是x,y都是模板类型,我们无法知道其类型,这时就可以使用auto。

3.模板函数依赖于模板参数的返回值

```c++
template <typename _Tx, typename _Ty>
auto multiply(_Tx x, _Ty y)->decltype(x*y)
{
    return x * y;
}
```

返回值依赖于x,y的类型,所以需要提前查询x,y的类型,需要用到decltype操作,它是C++11标准引入的新的运算符,其目的也是解决泛型编程中有些类型由模板参数决定,而难以表示它的问题

## 注意事项

1.auto变量必须在定义时初始化,类似于const关键字

2.初始化为数组时,auto推导类型为指针;初始化为数组且使用auto &,推导类型为数组类型

```c++
int a[3] = {1, 2, 3};

auto p1 = a; // p1为int*类型
auto &p2 = a; // p2为int [3]类型
```

3.函数或者模板参数不能声明为auto

```c++
void func(auto a)  //错误
{
    //... 
}
```

4.auto并不是真正的类型,只是一个占位符

```c++
cout << sizeof(auto) << endl; // 错误
cout << typeid(auto).name() << endl; // 错误
```

5.定义在一个auto序列的变量必须被推导成同一类型