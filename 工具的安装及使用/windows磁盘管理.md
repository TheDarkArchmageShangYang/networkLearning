## windows磁盘管理
路径:<br>
控制面板->系统和安全->管理工具->创建并格式化硬盘分区<br>
#### C盘和D盘之间还有个恢复分区
如图:
![a9aaa1c840054356a449687bd71884d3](https://github.com/TheDarkArchmageShangYang/networkLearning/assets/149142839/b34a2a7e-0b3a-43cc-991b-1de0014e5d7f)
解决方法：
win+r,cmd
```
C:\WINDOWS\system32>diskpart
DISKPART> list disk

  磁盘 ###  状态           大小     可用     Dyn  Gpt
  --------  -------------  -------  -------  ---  ---
  磁盘 0    联机              465 GB  6144 KB        *
  磁盘 1    联机              931 GB      0 B        *

DISKPART> select disk 0

磁盘 0 现在是所选磁盘。

DISKPART> list partition

  分区 ###       类型              大小     偏移量
  -------------  ----------------  -------  -------
  分区      1    系统                 260 MB  1024 KB
  分区      2    保留                  16 MB   261 MB
  分区      3    主要                 248 GB   277 MB
  分区      4    恢复                 974 MB   249 GB
  分区      5    主要                 215 GB   250 GB

DISKPART> select partition 4

分区 4 现在是所选分区。

DISKPART> delete partition override

DiskPart 成功地删除了所选分区。
```
![e2b747d12c7b48a6ab6eefc49e3b56b0](https://github.com/TheDarkArchmageShangYang/networkLearning/assets/149142839/020f31fc-9dbc-49a5-a3fa-2e57161a7761)
#### D盘压缩卷在D盘之后，无法给C盘扩展卷
