## tc限制带宽等
#### 基础命令
###### 查看网卡
```
ifconfig
```
一般为lo和eth0两个网卡
###### 查看网卡配置
```
tc qdisc show dev eth0
```
###### 删除网卡配置
```
sudo tc qdisc del dev eth0 root
```
#### 用netem限制RTT和丢包率
###### 限制RTT
```
tc qdisc add dev eth0 root netem delay 10ms
```
注意这是在原RTT的基础上增加10ms，而不是把RTT设置为10ms
###### 限制丢包率
```
tc qdisc add dev eth0 root netem loss 5%
```
###### 同时限制RTT和丢包率
```
tc qdisc add dev eth0 root netem delay 10ms loss 5%
```
#### 用tbf限制带宽
```
tc qdisc add dev eth0 root tbf rate 1mbit latency 10ms burst 15kb
```
rate表示带宽，latency表示数据包在队列中最长等待时间，burst表示缓冲区
#### 同时限制带宽和RTT/丢包率
```
sudo tc qdisc add dev eth0 root handle 1: tbf rate 1mbit buffer 1600 limit 3000
sudo tc qdisc add dev eth0 parent 1:1 handle 10: netem delay 100ms loss 10%
```
#### 注意事项
1.tc qdisc add dev ...的命令中add表示增加配置，也可以改成change表示覆盖，del表示删除
2.[参考网站](https://plantegg.github.io/2016/08/24/Linux%20tc%20qdisc%E7%9A%84%E4%BD%BF%E7%94%A8%E6%A1%88%E4%BE%8B/)
