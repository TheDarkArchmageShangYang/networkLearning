## inotify

### 安装

```
sudo apt-get install inotify-tools
```

如果遇到了E: Unable to locate package inotify-tools的问题

方法1:

```
sudo apt-get update
sudo apt-get install inotify-tools
```

方法2:

inotify-tools包通常在universe仓库中,如果这个仓库没有启动,你需要手动启用

```
sudo add-apt-repository universe
sudo apt-get update
sudo apt-get install inotify-tools
```

