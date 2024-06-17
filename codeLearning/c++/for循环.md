## for循环

### 常见for循环写法

```c++
int nums[] = {1, 2, 3, 4, 5};
int length = sizeof(nums) / sizeof(nums[0]);
vector <int> myvector(10);

// 写法1
for (int i = 0; i < length; i++) {
    cout << nums[i] << endl;
} // 也适用于容器
for (vector <char>::iterator it = myvector.begin(); it != myvector.end(); it++) {
    cout << *it << endl;
} // 也适用于容器

// 写法2
for_each (nums, nums + length, [](int item) {
    cout << item + 1 << endl;
}); // 也适用于容器

// 写法3,C++11新特性,基于范围的for循环
for (int var : nums) {
    cout << var << endl;
} // 也适用于容器
// 与另一个新特性自动类型推断(auto)结合,但是注意拷贝问题,详见auto.md
for (auto var : myvector) {
    cout << var << endl;
}
```

注意事项:

1.对于存储char字符的数组,末尾有'\0';而对于容器,没有'\0'

2.对于第一种方法,auto推导出来是迭代器类型;对于第三种方法,auto推导出来是元素类型.

例如对于一个map,第一种方法auto推导出来用it->first和it->second来取出键值对;第二种方法auto推导出来是std::pair类型,用it.first和it.second来取出键值对

第三种方式形如

```c++
for (declaration : expression){
    //循环体
}
```

declaration既可以是普通变量,也可以是引用.如果在遍历过程中需要修改元素的值,必须使用引用形式.否则,建议使用const &形式的变量(避免了底层复制变量的过程,效率更高),也可以定义普通变量.

### C++11带有初始化列表的for循环

```c++
for (int it : {1, 2, 3, 4, 5}) {
    cout << it << endl;
}
```

### C++17结构化绑定的for循环

用于遍历关联容器(如map)中的键值对

```c++

map<std::string, int> scores = {{"Alice", 90}, {"Bob", 80}, {"Charlie", 70}};

for (const auto& [name, score] : scores) {
    cout << name << ": " << score << endl;
}
```

