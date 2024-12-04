# Typora

## 1 安装

链接：https://pan.baidu.com/s/1MMDVIa5EbYkON8WeyQtTJw?pwd=ee7x 
提取码：ee7x

把破解补丁.zip解压后把winmm.dll复制到Typora的根目录中

## 2 常用设置

### 2.1 主题

#### 2.1.1 主题下载

主题名:Drake

Github链接:https://github.com/liangjingkanji/DrakeTyporaTheme?tab=readme-ov-file

目前使用的是修改版

链接：https://pan.baidu.com/s/1VpcWOvbxZ_aGLGUQ5LQOfw?pwd=8h0b 
提取码：8h0b

#### 字体下载

英文字体:JetBrainsMono Patch

下载地址:https://github.com/liangjingkanji/JetBrainsMono-Patch/releases/

中文字体:HYZhengYuan

下载地址:https://www.hanyi.com.cn/productdetail?id=2915

下载后找到ttf文件夹,全选右键安装

#### 2.1.2 使用

1.确保已经下载Typora

2.依次点击**文件**->**偏好设置**->**外观**->**打开主题文件夹**

3.将下载的CSS文件复制到该文件夹

4.重启Typora,点击**主题**,选择想要的主题

### 2.2 其他设置

#### 2.2.1 通用

保存&恢复->自动保存

#### 2.2.2 图像

![image-20241006043929153](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20241203042554897.png)

默认设置使用的是绝对路径,此时插入的图片在其他主机/github上看不到.所以需要将插入的图片在git库中额外复制一份,同时使用相对路径来插入(使用绝对路径会由于路径问题看不到)

插入时自动转义图片并不关键,主要用于防止一些不兼容情况.

## 3 使用

### 3.1 代码块

#### 自动设置语言(?存疑)

可以使用"```c++"来生成一个c++的代码块(更好)

也可以通过AHK插件来实现(每次重启都要运行一次，加到开机启动项里)

1.AHK下载链接:https://autohotkey.com/download/ahk-install.exe

2.创建AHK文档

写一个AHK.ahk文档

```
#IfWinActive ahk_exe Typora.exe
{
    ; Ctrl+K c++Code    
    ; crtl 是 ^    k 是 k键
    ^k::addCode()
}
addCode(){
Send,{Asc 096}
Send,{Asc 096}
Send,{Asc 096}
SendInput, {Text}c++
Send,{Enter}
Return
}

```

3.运行AHK.ahk

现在可以通过Ctrl+k来直接创建一个c++代码块

Typora默认生成代码块的快捷键是Ctrl+Shift+k,在之前的文档中注意区分

### 3.2 段落划分

可以使用1/2/3/4/5/6级标题来划分

```
ctrl + 1/2/3/4/5/6
```

也可以使用小黑点、空心圆、小方框(不同主题可能会不同，在github主题如下)

- 小黑点(ctrl + shift + ] 或者 * + space)
  - 空心圆(小黑点的基础上，第二行Tab)，两次回车变回小黑点
    - 小方框(空心圆的基础上，第二行Tab)，两次回车变回空心圆

### 3.3 取消中文标点

在使用过程中,想要打出()或者插入代码块老是需要切换输入法,非常麻烦,并且中文标点在大多数时候不必要.所以可以直接关掉中文标点

win10为例:

右键屏幕右下角输入法图标->设置->常规->中文输入时使用英文标点(关->开)

### 3.4 插入图片

设置如2.2.2