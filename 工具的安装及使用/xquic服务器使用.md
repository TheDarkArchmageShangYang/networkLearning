## 安装

[参考链接](https://github.com/alibaba/tengine/tree/master/modules/ngx_http_xquic_module)

```
# 下载 Tongsuo，示例中下载 8.3.2 版本
wget -c "https://github.com/Tongsuo-Project/Tongsuo/archive/refs/tags/8.3.2.tar.gz"
tar -xf 8.3.2.tar.gz

# 下载 xquic，示例中下载 1.6.0 版本
wget -c "https://github.com/alibaba/xquic/archive/refs/tags/v1.6.0.tar.gz"
tar -xf v1.6.0.tar.gz

# 下载 Tengine 3.0.0 以上版本，示例从 master 获取最新版本，也可下载指定版本
git clone https://github.com/alibaba/tengine.git

# 编译 Tongsuo
cd Tongsuo-8.3.2
./config --prefix=/home/fzchen/xquic/babassl
make
make install
export SSL_TYPE_STR="babassl"
export SSL_PATH_STR="${PWD}"
export SSL_INC_PATH_STR="${PWD}/include"
export SSL_LIB_PATH_STR="${PWD}/libssl.a;${PWD}/libcrypto.a"
cd ../

# 编译 xquic 库
cd xquic-1.6.0/
mkdir -p build
cd build
cmake -DXQC_SUPPORT_SENDMMSG_BUILD=1 -DXQC_ENABLE_BBR2=1 -DXQC_DISABLE_RENO=0 -DSSL_TYPE=${SSL_TYPE_STR} -DSSL_PATH=${SSL_PATH_STR} -DSSL_INC_PATH=${SSL_INC_PATH_STR} -DSSL_LIB_PATH=${SSL_LIB_PATH_STR} ..
make
cd ../../

# 编译 Tengine
cd tengine

# 注：xquic 依赖 ngx_http_v2_module，需
要参数 --with-http_v2_module
./configure   --prefix=/home/fzchen/xquic/tengine-install   --sbin-path=sbin/tengine   --with-xquic-inc="../xquic-1.6.0/include"   --with-xquic-lib="../xquic-1.6.0/build"   --with-http_v2_module   --without-http_rewrite_module   --add-module=modules/ngx_http_xquic_module   --with-openssl="../Tongsuo-8.3.2"

make
make install
```
## 运行

在tengine-install目录下新增nginx.conf文件
```
worker_processes  1;
user root;
error_log  logs/error.log debug;
events {
    worker_connections  1024;
}
xquic_log   "pipe:rollback /home/fzchen/xquic/tengine-install/logs/xquic.log baknum=10 maxsize=1G interval=1d adjust=600" info;
http {
    include       /home/fzchen/xquic/tengine-install/conf/mime.types;
    default_type  application/octet-stream;
    xquic_ssl_certificate        /home/fzchen/cert/fullchain.pem;
    xquic_ssl_certificate_key    /home/fzchen/cert/privkey.pem;
    xquic_congestion_control bbr;
    xquic_socket_rcvbuf 5242880;
    xquic_socket_sndbuf 5242880;
    xquic_anti_amplification_limit 5;
    xquic_log_level info;
    server {
        listen 8000 ssl http2;
        listen 8000 xquic reuseport;
        server_name udpcc-shh.dfshan.net;
        
        add_header Alt-Svc 'h3=":8000"; ma=2592000,h3-29=":8000"; ma=2592000;' always;
        
        ssl_protocols       TLSv1.3;
        ssl_certificate     /home/fzchen/cert/fullchain.pem;
        ssl_certificate_key /home/fzchen/cert/privkey.pem;
        location / {
            root    /home/fzchen/dash.js/;
            index index.html;

            autoindex on;
            autoindex_exact_size   on;
        }
    }
}
```
常用命令

```
# 指定配置文件启动
./tengine -c conf/nginx.conf
# 检查配置
./tengine -t
# 运行
./tengine
# 停止
./tengine -s stop
# 重新加载配置文件启动
./tengine -s reload
```
## 机制

### 处理收到的ACK包

xquic使用结构体 *<u>**xqc_ack_info_t**</u>* 来存储ACK包的数据，结构体定义在 ***<u>/src/transport/xqc_recv_recode.h:34</u>*** 

![image-20240410162249888](assets/xquic%E6%9C%8D%E5%8A%A1%E5%99%A8%E4%BD%BF%E7%94%A8/image-20240410162249888.png)

ACK包的处理函数在 ***<u>/src/transport/xqc_frame_parser.c:662</u>*** 的 ***<u>xqc_parse_ack_frame()</u>*** 但是该函数没有记录dcid_seq_num



以一个ACK为例

![image-20240410162717998](assets/xquic%E6%9C%8D%E5%8A%A1%E5%99%A8%E4%BD%BF%E7%94%A8/image-20240410162717998.png)

经过处理

```
n_ranges = 4;
ranges[0].high = 921;
ranges[0].low = 895;
ranges[1].high = 893;
ranges[1].low = 891;
ranges[2].high = 889;
ranges[2].low = 886;
ranges[3].high = 884;
ranges[3].low = 884;
```

每收到一个ACK，就调用 ***<u>/src/trsnaport/xqc_send_ctl.c:880</u>*** 的 ***<u>xqc_send_ctl_on_ack_received()</u>*** 函数

对于每个已发送但未被确认的包：例如892

1.判断该包号是否超过最大ACK(pkt_number > 921)

2.判断该包号属于哪个ranges中(pkt_num > ranges[i].high)

包号>884，继续下一个判断

包号>889，继续下一个判断

包号<893，在ranges[1]中

3.判断该包号是否被确认(pkt_num > ranges[i].low)

包号>891，该包号被这个ACK包确认

## 常见问题

#### 问题1

![image](assets/xquic%E6%9C%8D%E5%8A%A1%E5%99%A8%E4%BD%BF%E7%94%A8/17b9b03e-9450-4382-a7e8-0bb73acdfa56.png)

原因：共享库libxquic.so没有被添加到环境变量中

```
cd /etc/ld.so.conf.d
sudo vim xquic_cfz.conf

# 在xquic_cfz.conf中添加以下内容
/home/fzchen/xquic/xquic-1.6.0/build

sudo ldconfig
```
#### 问题2

![image](assets/xquic%E6%9C%8D%E5%8A%A1%E5%99%A8%E4%BD%BF%E7%94%A8/b6a6443c-fe40-47cc-b932-7cf997fc726b.png)

原因：tengine没有权限

```
sudo chown root tengine
sudo chmod u+s tengine
```

#### 问题3

有时候向服务器发送请求收不到响应

原因：可能是后台开了多个tengine

```
ps -aux | grep tengine
sudo kill -9 端口号
```

