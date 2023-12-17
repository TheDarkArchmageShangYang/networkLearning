## 支持QUIC的CURL安装及libcurl库的使用
记住安装过程中的<somewhere1/2/3>，在其他部分的编译中有用
#### 构建quictls
```
git clone --depth 1 -b openssl-3.1.4+quic https://github.com/quictls/openssl
cd openssl
./config enable-tls1_3 --prefix=<somewhere1>
make
make install
```
#### 构建nghttp3
```
cd ..
git clone -b v1.1.0 https://github.com/ngtcp2/nghttp3
cd nghttp3
autoreconf -i -I /usr/share/aclocal/
./configure --prefix=<somewhere2> --enable-lib-only
make
make install
```
#### 构建ngtcp2
```
cd ..
git clone -b v1.1.0 https://github.com/ngtcp2/ngtcp2
cd ngtcp2
autoreconf -i -I /usr/share/aclocal/
./configure PKG_CONFIG_PATH=<somewhere1>/lib64/pkgconfig:<somewhere2>/lib/pkgconfig LDFLAGS="-Wl,-rpath,<somewhere1>/lib64" --prefix=<somewhere3> --enable-lib-only
make
make install
```
#### 构建curl
```
cd ..
git clone https://github.com/curl/curl
cd curl
autoreconf -i -I /usr/share/aclocal/
LDFLAGS="-Wl,-rpath,<somewhere1>/lib64" ./configure --with-openssl=<somewhere1> --with-nghttp3=<somewhere2> --with-ngtcp2=<somewhere3>
make
make install
```
如果没有权限装在/usr/local下，可以把第五步命令改成
```
LDFLAGS="-Wl,-rpath,<somewhere1>/lib64" ./configure --with-openssl=<somewhere1> --with-nghttp3=<somewhere2> --with-ngtcp2=<somewhere3> --prefix=<somewhere4>
```
然后在<somewhere4/bin>中使用./curl来运行(因为linux基本都自带curl，所以直接用curl访问会使用自带的curl而不是新装的)
#### 测试
仅使用HTTP/3:
```
curl -v --http3-only https://nghttp2.org:4433/
```
使用HTTP/3并允许回退到HTTP/2或HTTP/1.1:
```
curl -v --http3 https://nghttp2.org:4433/
```
#### libcurl库使用
程序中需要添加
```
#include <curl/curl.h>
```
编译时使用如下命令
```
gcc/g++ <文件名.c/cpp> -o <可执行文件名> -lcurl
```
如果curl的安装没有sudo权限，此时-lcurl仍然指向老的curl(一般为7.81.0)，需要使用如下命令
```
g++ <文件名.cpp> -o <可执行文件名> -I <curl地址/include/> -L <curl地址/lib/> -lcurl -Wl,-rpath=<curl地址/lib>
```
注意#include中头文件是curl/curl.h，所以-I只需要到/include就可以了
#### 使用
1.curl的-k选项可以忽略SSL证书验证<br>
2.curl的--libcurl <file.c>可以把执行的命令转换为c语言输出到该文件，但是不是100%准确<br>
3.curl的-v选项可以展示详细信息，方便查看包头<br>
4.curl的--http3-only不允许HTTP回退，--http3允许回退<br>
5.libcurl库的使用详见https://curl.se/libcurl/c/<br>
