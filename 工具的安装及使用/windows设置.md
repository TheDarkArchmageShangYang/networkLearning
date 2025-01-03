## 快捷键

1.win + 上下左右

功能:将页面设成全屏(上),最小化(下),左半屏(左),右半屏(右)

使用相反方向可以取消,如win + ->后win + <-可以恢复成原来

左右和上下搭配使用可以实现1/4屏

2.Alt + Tab

功能:快速切换界面

Alt + Tab呼出界面->按住Alt,松Tab->上下左右选择界面->松Alt呼出选择的界面

3.Ctrl + 数字

功能:切换网页

1-8对应第1-8个网页,9对应最后一个网页

## 设置

### 关闭锁屏界面广告

修改位置:设置->个性化->锁屏界面

1.个人锁屏界面从windows聚焦改成图片/幻灯片放映,否则图片上会显示几个搜索框,里面是对图片的介绍

2.锁定界面状态改成无,可以关掉天气,股票等

### 开机自启动

开机自启动优先级:服务>注册表>启动文件夹>计划

**服务**

Win+r->cmd,需要管理员权限

```
sc create 服务名 binPath=启动文件路径 start=auto
```

**注册表**

Win+R打开运行,输入regedit打开注册表,打开HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Run,新建字符串值,数值数据为程序位置

**启动文件夹**

Win+R打开运行,输入shell:startup,打开自启动目录

```shell
C:\Users\\[用户名]\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup
```

方法1.把要开机自启动的程序或者快捷方式复制到该文件夹下

注意:有些软件的exe文件启动需要一些dll文件,所以该方法不一定可行

方法2.创建script.bat,在脚本中启动exe文件

```shell
E:
cd \Snipaste
start Snipaste.exe
```

**计划**

此电脑(右键管理)->任务计划程序->创建任务

### 右键创建md文件

需要安装Typora

1.右键->新建->文本文档

2.输入以下内容

```
Windows Registry Editor Version 5.00
[HKEY_CLASSES_ROOT.md]
@=“Typora.exe”
[HKEY_CLASSES_ROOT.md\ShellNew]
“NullFile”=""
[HKEY_CLASSES_ROOT\Typora.exe]
@=“Markdown”
```

其中==@=“Typora.exe”==是Markdown编辑器的名字

==@=“Markdown”==是右键->新建时看到的文件名

3.关闭文件,右键->重命名为xxx.reg

4.双击运行

5.如果还是不能直接创建md就重启

## 软件

### Snipaste

下载地址https://dl.snipaste.com/win-x64-cn

#### 功能:截图

F1开始截图,会自动保存截图历史记录(保存的是整个屏幕,而不只是截图窗口)

建议加入开机启动项

