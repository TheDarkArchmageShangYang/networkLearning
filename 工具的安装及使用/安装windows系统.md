# 安装windows系统
## 通过官方下载工具下载镜像
1.下载官方安装工具

[下载地址](https://www.microsoft.com/zh-cn/software-download/windows10)

点击"立即下载工具"
![a31783408f3f43c38f862554191f6efc](assets/%E5%AE%89%E8%A3%85windows%E7%B3%BB%E7%BB%9F/1164785e-db97-439b-a3b7-a8155728e06c.png)
2.制作启动盘
打开安装工具，按照提示操作

3.安装Windows

按"del"或其他键进入Bios界面，在Boot界面选择Boot Option1为启动盘，退出Bios界面

进入Windows安装程序，按照提示操作

在分区格式化磁盘时，需要先把C盘进行格式化，需要分清哪个是C盘

## 通过其他途径下载镜像

1.从西安交通大学网络信息中心下载Windows镜像
2.下载安装Ultra ISO，打开ISO文件
![cdf683ec3daa46eda99eb8202b842473](assets/%E5%AE%89%E8%A3%85windows%E7%B3%BB%E7%BB%9F/5575bfc4-ae1c-41d6-9619-faa569478ef7.png)
3.启动，写入硬盘映像
![6ba20a558a8d4f9189303515b22fec41](assets/%E5%AE%89%E8%A3%85windows%E7%B3%BB%E7%BB%9F/18429d42-507a-4a2e-a0fd-cca0ab8bb8cd.png)
4.选择要写入的磁盘，点击写入
![71474325eb874e1aa055a86d235c05a1](assets/%E5%AE%89%E8%A3%85windows%E7%B3%BB%E7%BB%9F/bb9f0e2b-eb76-4722-b8e0-b4d676a3d23e.png)
![bd22b6714f7d4fb19fd999ce6bd0aab6](assets/%E5%AE%89%E8%A3%85windows%E7%B3%BB%E7%BB%9F/fedcaaf2-f18e-4f74-a700-5aa63338e127.png)
5.启动盘制作完毕，剩余部分与官方下载工具相同

## 注意事项

1.如果磁盘分区无法格式化，或者删除分区后无法重新建立分区

```
shift+F10打开dos界面
diskpart
list disk
select disk 0,选中要删除的磁盘
clean
convert gpt转化成gpt磁盘 / convert mbr转化成mbr磁盘
```
