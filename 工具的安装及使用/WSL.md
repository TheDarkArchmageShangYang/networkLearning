# WSL安装和使用

## 安装

1. 以管理员身份运行 `powerShell` 

2. ```
   // 安装wsl,可能需要重启
   wsl --install
   // 查看可用的发行版
   wsl --list --online
   // 安装
   wsl --install -d Ubuntu-22.04
   // 查看WSL状态
   wsl -l -v
   // 如果显示WSL1,升级到WSL2
    wsl --set-default-version 2
    // 卸载Ubuntu 22.04
    wsl --unregister Ubuntu-22.04
   ```

## 使用

Win+R/PowerShell输入

```
wsl
```



使用vscode打开

vscode安装Remote Development插件

Power Shell输入

```
wsl
cd <文件夹>
code .
```

