## for循环

### 常见for循环写法

```c++
int nums[] = {1, 2, 3, 4, 5};
int length = sizeof(nums) / sizeof(nums[0]);

// 写法1
for (int i = 0; i < length; i++) {
    cout << nums[i] << endl;
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
for (auto var : nums) {
    cout << var << endl;
}
```

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

