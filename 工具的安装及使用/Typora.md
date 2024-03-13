# Typora

## 安装

链接：https://pan.baidu.com/s/1MMDVIa5EbYkON8WeyQtTJw?pwd=ee7x 
提取码：ee7x

把破解补丁.zip解压后把winmm.dll复制到Typora的根目录中

## 主题

主题名:Drake

Github链接:https://github.com/liangjingkanji/DrakeTyporaTheme?tab=readme-ov-file

英文字体:JetBrainsMono Patch

下载地址:https://github.com/liangjingkanji/JetBrainsMono-Patch/releases/

下载后找到ttf文件夹,全选右键安装

中文字体:HYZhengYuan

下载地址:https://www.hanyi.com.cn/productdetail?id=2915

## 使用

### 代码块

#### 自动设置语言

可以使用"```c++"来生成一个c++的代码块

也可以通过AHK插件来实现.

1.AHK下载链接:https://[autohotkey](https://so.csdn.net/so/search?q=autohotkey&spm=1001.2101.3001.7020).com/download/ahk-install.exe

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