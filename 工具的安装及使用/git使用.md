# git

[参考链接](https://blog.csdn.net/bjbz_cxy/article/details/116703787?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522171042946316800188588042%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=171042946316800188588042&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-1-116703787-null-null.142^v99^pc_search_result_base3&utm_term=git&spm=1018.2226.3001.4187)

## 创建本地空仓库

```shell
git init
```

## 把文件添加到缓存区

```shell
git add <filename>
```

如果不清楚哪些文件被改动过,可以用

```shell
git add --all
```

注意此时删除信息也会被记录进去,如果不想删除文件,可以用

```shell
git add .
```

如果已经添加到缓存区的文件被修改,需要再次将其添加到缓存区

## 把缓存区的内容提交到本地仓库

```shell
git commit -m "<string>"
```

我们需要使用-m选项来描述我们做了什么,如果不使用-m,会调用终端的编辑器让你输入信息,比较难用

## 查看历史提交日志

```shell
git log
```



## 更新到github上

```
git push origin <branch>
```
