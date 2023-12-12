## 支持QUIC的CURL安装

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
./configure PKG_CONFIG_PATH=<somewhere1>/lib64/pkgconfig:<somewhere2>/lib64/pkgconfig LDFLAGS="-Wl,-rpath,<somewhere1>/lib64" --prefix=<somewhere3> --enable-lib-only
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
#### 测试
仅使用HTTP/3:
```
curl --http3-only https://nghttp2.org:4433/
```
使用HTTP/3并允许回退到HTTP/2或HTTP/1.1:
```
curl --http3 https://nghttp2.org:4433/
```

#### 使用
使用的是ngtcp2，与quicgo不兼容，使用--http3-only选项访问使用quicgo+caddy搭建的网页无法访问
