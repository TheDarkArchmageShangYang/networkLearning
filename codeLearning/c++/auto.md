## 介绍

C++11引入了auto类型说明符,便于在不清楚变量类型是声明变量

## 推导规则

- 规则1：声明为auto（不是auto&）的变量，忽视掉初始化表达式的顶层const。即对有const的普通类型(int,double等)忽视const，对常量指针（顶层const）变为普通指针，对指向常量（底层const）的常量指针（顶层cosnt）变为指向常量的指针（底层const）。

- 规则2：声明为auto&的变量，保持初始化表达式的顶层const或volatile 属性。
- 规则3：若希望auto推导的是顶层const，加上const，即const auto。

顶层const和底层const详见const.md

学习中断https://blog.csdn.net/weixin_43744293/article/details/117440727?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522171855981216800188567304%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=171855981216800188567304&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-1-117440727-null-null.142^v100^pc_search_result_base3&utm_term=c%2B%2B%20auto&spm=1018.2226.3001.4187