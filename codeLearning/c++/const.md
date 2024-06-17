## const

指针本身是一个对象,但是它又指向另一个对象,这就是指针的两种属性

- 对于指针本身是一个常量,即指针的指向是一个常量,不能改变指针的指向,称为顶层const,形如

```c++
int* const p = &a; // const修饰p,即指针本身,又称常量指针
```

- 对于指针指向的对象是一个常量,即指针指向的地址的值是一个常量,不能改变指针指向内存的值,称为底层const

```c++
const int* p = &a; // const修饰int* p,即指针指向的内存的值,又称指针常量
```

普通指针可以转换为顶层const和底层const

顶层const在赋值时可以忽略此属性

底层const在赋值时不能忽略此属性

顶层const可以转换为底层const,底层const不能转换为顶层const

```c++
int a = 0;
int* p = &a;

const int* p1 = p; // 正确
int* const p2 = p; // 正确

int* const p3 = p1; // 错误,底层const在赋值时不能忽略此属性
const int* p4 = p2; // 正确,顶层const在赋值时可以忽略此属性

int* p5 = p1; // 错误,底层const在赋值时不能忽略此属性
int* p6 = p2; // 正确,顶层const在赋值时可以忽略此属性

const int* const p7 = p1; // 正确
const int* const p8 = p2; // 正确

const int* p9 = p7; // 正确
int* const p10 = p7; // 错误,p7有底层const属性
```

## 注意事项

1.

```c++
const int a = 0;
const int* p = &a; // 此时&b相当于const int*,只能初始化给底层const,写成int*或int const*均会报错
```

