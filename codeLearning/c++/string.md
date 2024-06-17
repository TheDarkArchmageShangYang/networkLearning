# string

## 初始化

```c++
string str;
string str1(str); // str1是str的副本
string str1 = str;
string str("hello");
string str = "hello";
string str(n, 'c'); // 把str初始化为连续n个字符c组成的串
```

## string对象操作

### 输入

```c++
string str;
cin >> str; // 读取到下一处空白
getline(cin, str); // 读取一整行,直到换行符
```

### 获取string中的每个字符

```c++
1.使用下标运算符
string str = "hello";
s[0] = 'H';

2.使用迭代器
string str = "hello";
for (auto i = str.begin(); i != str.end(); i++){
	cout << *i  << ",";
}
```

### 库函数

#### length()

获取str长度

```c++
string str = "hello";
cout << str.length() << endl;
```



#### append()

插入到string对象末尾,等于'+'

```c++
string str = "hello";
str.append(", world!");
```

