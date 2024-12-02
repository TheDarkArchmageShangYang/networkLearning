# proxygen安装及使用
## 安装
```
git clone https://github.com/facebook/proxygen.git
cd proxygen/proxygen
./build.sh
cd _build/ && make test
cd ..
./install.sh
```
## 运行
###### 服务器

```
./hq --mode=server --h2port=<HTTP/2port> --port=<HTTP/3port> --protocol=h3 --cert=<cert> --key=<key> --static-root=./ --host=0.0.0.0 --connect_udp=true
```
--static-root为服务器运行的根目录，示例URL为https://udpcc-shh.dfshan.net:8000/index.html
###### 客户端
```
./hq --mode=client --path=<URL> --host=<host> --port=<port> --protocol=h3
```
本地访问时host为127.0.0.1，其他为服务器的公网IP
## 使用心得
1.安装时build.sh的31行需要sudo权限，没有权限可以直接把sudo删了或者直接不管<br>
2.第一次编译完成后，后续编译可以把build.sh的426-432行注释掉<br>
3.注意server的port对应的UDP端口和h2port对应的TCP的端口都要打开<br>
4.proxygen与certbot的证书冲突(疑似)<br>
