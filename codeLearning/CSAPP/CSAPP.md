# CS:APP

## 第1章 计算机系统漫游

```c
#include <stdio.h>

int main() {
    printf("hello world\n");
    return 0;
}
```

在unix系统上,从源文件到目标文件的转化分为4个阶段完成:

1.hello.c经过预处理器变成hello.i

2.hello.i经过编译器变成hello.s

3.hello.s经过汇编器变成hello.o

4.hello.o经过链接器变成hello.exe



1)预处理阶段

预处理器根据"#"开头的命令,修改c程序,比如hello.c中第一行的#include <stdio.h>告诉预处理器读取系统头文件stdio.h的内容,把它直接插入程序文本中

```
gcc -E hello.c  -o hello.i
```



2)编译阶段

```
gcc -S hello.i -o hello.s
```



3)汇编阶段

```
gcc -c hello.s -o hello.o
```



4)链接阶段

```
gcc hello.o -o hello
```

执行可执行文件hello

```
./hello
```

