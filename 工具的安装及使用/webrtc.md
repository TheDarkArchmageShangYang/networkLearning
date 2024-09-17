## 安装

### 安装Janus WebRTC服务器

1.安装依赖项

```shell
apt install libmicrohttpd-dev libjansson-dev \
	libssl-dev libsofia-sip-ua-dev libglib2.0-dev \
	libopus-dev libogg-dev libcurl4-openssl-dev liblua5.3-dev \
	libconfig-dev pkg-config libtool automake cmake
```

手动安装libnice,需要python3,Meson,Ninja

```shell
sudo apt-get install Meson Ninja-build
git clone https://gitlab.freedesktop.org/libnice/libnice
cd libnice
meson --prefix=/usr build && ninja -C build && sudo ninja -C build install
```

手动安装libsrtp

```shell
wget https://github.com/cisco/libsrtp/archive/v2.2.0.tar.gz
tar xfv v2.2.0.tar.gz
cd libsrtp-2.2.0
./configure --prefix=/usr --enable-openssl
make shared_library && sudo make install
```

手动安装libwebsockets

```c++
git clone https://libwebsockets.org/repo/libwebsockets
cd libwebsockets
# If you want the stable version of libwebsockets, uncomment the next line
# git checkout v4.3-stable
mkdir build
cd build
# See https://github.com/meetecho/janus-gateway/issues/732 re: LWS_MAX_SMP
# See https://github.com/meetecho/janus-gateway/issues/2476 re: LWS_WITHOUT_EXTENSIONS
cmake -DLWS_MAX_SMP=1 -DLWS_WITHOUT_EXTENSIONS=0 -DCMAKE_INSTALL_PREFIX:PATH=/usr -DCMAKE_C_FLAGS="-fpic" ..
make && sudo make install
```

2.编译

```shell
git clone https://github.com/meetecho/janus-gateway.git
cd janus-gateway
sh autogen.sh
./configure --prefix=/opt/janus
make
make install
make configs
```

使用nginx/tengine启动，此时还无法正常通话

### 安装coturn

```c++
sudo apt-get install libssl-dev
sudo apt-get install libevent-dev

git clone https://github.com/coturn/coturn 
cd coturn
./configure 
make && sudo make install
```

```c++
sudo nohup turnserver -L 0.0.0.0 --min-port 50000 --max-port 60000  -a -u xxx:123456 -v -f -r nort.gov &
```



### DASH服务器设置

```
sudo apt-get install ffmpeg
```

