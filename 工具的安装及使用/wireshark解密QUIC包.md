# wireshark解密QUIC包
QUIC包经过加密，解密之前看不到HTTP等协议
#### 操作步骤
1.打开一个命令行，开启抓包
```
sudo tcpdump -i eno1 -w 1.pcap host 60.204.136.199
```
2.另起一个命令行，设置环境变量
```
export SSLKEYLOGFILE=/home/fzchen/sslkeylog.log
```
也可以通过其他方式改变环境变量

浏览器会在每次https会话结束后，把会话数据解密的key记录到该文件中。wireshark通过访问该文件使用里面的key就可以解密捕获到的https会话数据

3.访问QUIC服务器

4.停止抓包，用wireshark打开抓到的包
打开[编辑]-[首选项]-[协议]-[TLS]-[(pre)-Master-Secret log filename]，选中sslkeylog.log
得到解密后的QUIC包
![image](https://github.com/TheDarkArchmageShangYang/networkLearning/assets/149142839/d8c104ef-0429-4d4d-9f56-3d08d2d474ee)
