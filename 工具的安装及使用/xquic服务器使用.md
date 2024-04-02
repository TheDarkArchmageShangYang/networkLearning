[参考连接](https://github.com/alibaba/tengine/tree/master/modules/ngx_http_xquic_module)
## 安装
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
./config --prefix=/home/fzchen/worknew/babassl
make
make install
export SSL_TYPE_STR="babassl"
export SSL_PATH_STR="${PWD}"
export SSL_INC_PATH_STR="${PWD}/include"
export SSL_LIB_PATH_STR="${PWD}/libssl.a;${PWD}/libcrypto.a"
cd ../

# 编译 xquic 库
cd xquic-1.6.0/
mkdir -p build; cd build
cmake -DXQC_SUPPORT_SENDMMSG_BUILD=1 -DXQC_ENABLE_BBR2=1 -DXQC_DISABLE_RENO=0 -DSSL_TYPE=${SSL_TYPE_STR} -DSSL_PATH=${SSL_PATH_STR} -DSSL_INC_PATH=${SSL_INC_PATH_STR} -DSSL_LIB_PATH=${SSL_LIB_PATH_STR} ..
make
cd ../../

# 编译 Tengine
cd tengine

# 注：xquic 依赖 ngx_http_v2_module，需要参数 --with-http_v2_module
./configure   --prefix=/home/fzchen/worknew/tengine-install   --sbin-path=sbin/tengine   --with-xquic-inc="../xquic-1.6.0/include"   --with-xquic-lib="../xquic-1.6.0/build"   --with-http_v2_module   --without-http_rewrite_module   --add-module=modules/ngx_http_xquic_module   --with-openssl="../Tongsuo-8.3.2"

make
make install
```
## 使用
在tengine-install目录下新增nginx.conf文件
```
worker_processes  1;
user root;
error_log  logs/error.log debug;
events {
    worker_connections  1024;
}
xquic_log   "pipe:rollback /usr/local/tengine/logs/tengine-xquic.log baknum=10 maxsize=1G interval=1d adjust=600" info;
http {
    xquic_ssl_certificate        /home/fzchen/cert/fullchain.pem;
    xquic_ssl_certificate_key    /home/fzchen/cert/privkey.pem;
    xquic_congestion_control bbr;
    xquic_socket_rcvbuf 5242880;
    xquic_socket_sndbuf 5242880;
    xquic_anti_amplification_limit 5;
    server {
        #listen 80 default_server reuseport backlog=4096;
        listen 8000 default_server reuseport backlog=4096 ssl http2;
        listen 8000 default_server reuseport backlog=4096 xquic;
        #listen 8000 xquic reuseport;
        server_name udpcc-shh.dfshan.net;
        add_header Alt-Svc 'h3=":8000"; ma=2592000,h3-29=":8000"; ma=2592000' always;
        ssl_certificate     /home/fzchen/cert/fullchain.pem;
        ssl_certificate_key /home/fzchen/cert/privkey.pem;
        location / {
            root   /home/fzchen/worknew/tengine-install;
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
## 常见问题
#### 问题1

![image](https://github.com/TheDarkArchmageShangYang/networkLearning/assets/149142839/17b9b03e-9450-4382-a7e8-0bb73acdfa56)
```
vim /etc/ld.so.conf

# 在ld.so.conf中添加以下内容
/home/fzchen/worknew/xquic-1.6.0/build

sudo ldconfig
```
sudo权限无法编辑ld.so.conf，root用户可以

#### 问题2

![image](https://github.com/TheDarkArchmageShangYang/networkLearning/assets/149142839/b6a6443c-fe40-47cc-b932-7cf997fc726b)
```
sudo chown root tengine
sudo chmod u+s tengine
```
