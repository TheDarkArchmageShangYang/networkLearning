## 使用dash.js+caddy的服务器搭建
#### 安装caddy
```
git clone https://github.com/caddyserver/caddy.git
cd caddy/cmd/caddy
go build
caddy upgrade
```
如果发生caddy: command not found，将caddy/cmd/caddy下的caddy文件移动到/usr/bin目录下

#### caddy使用

###### 配置Caddyfile

把Caddyfile文件放在caddy目录下
```
localhost {
    respond "Hello, world!"
}
udpcc.dfshan.net（域名） {
    root * /home/admin/fzchen/video/output（stream.mpd所在的文件夹）
    encode gzip
    file_server
}
```
###### 打开

```
caddy start
```
###### 关闭

```
caddy stop
```
#### 获取原视频：mp4格式，相机拍一个
#### 安装编码器ffmpeg

```shell
sudo apt install ffmpeg
```

转码视频：
```shell
ffmpeg -i pre_video.mp4 -s 640*360 -c:v libx264 -b:v 1000k -keyint_min 48 -g 48 -sc_threshold 0 -an video_640x360_1000k.mp4//等多个格式
```
#### 安装bento4
```
wget https://www.bok.net/Bento4/binaries/Bento4-SDK-1-6-0-640.x86_64-unknown-linux.zip
unzip Bento4-SDK-1-6-0-640.x86_64-unknown-linux.zip
vim /etc/profile
source /etc/profile
```
在/etc/profile中添加以下内容：
```
BENTO4_PATH=/home/xxx/Bento4-SDK-1-6-0-640.x86_64-unknown-linux/bin
export PATH=$PATH:$BENTO4_PATH
```
#### 视频切片

```
mp4fragment --fragment-duration 2000 video_640x360_1000k.mp4 fra_640x360_1000k.mp4
mp4dash fra_640x360_1000k.mp4 fra_640x360_500k.mp4
```

文件目录如下：
output/

├── stream.mpd

└── video/

    └── avc1/
    
        ├── 1/
        
        ├── 2/
        
            ├── init.mp4
            
            ├── seg-1.m4s
            
            ├── ...
            
            └── seg-327.m4s
#### 测试

使用dash.js写一个视频播放器，放在stream.mpd同一文件夹下

```
<!doctype html>
<html>
    <head>
        <title>Dash.js Rocks</title>
        <style>
            video {
                width: 640px;
                height: 360px;
            }
        </style>
    </head>
    <body>
        <div>
            <video id="videoPlayer" controls></video>
        </div>
        <script src="./dash.all.min.js"></script>
        <script>
            (function(){
                var url = "./stream.mpd";
                var player = dashjs.MediaPlayer().create();
                player.initialize(document.querySelector("#videoPlayer"), url, true);
            })();
        </script>
    </body>
</html>
```
下载dash.all.min.js，放在stream.mpd同一文件夹下：
```
wget http://cdn.dashjs.org/latest/dash.all.min.js
```
## dash.js代码分析

针对参考播放器dash-if-reference

dash.js播放设置选项如下：
![image](https://github.com/TheDarkArchmageShangYang/networkLearning/assets/149142839/7d2f75f4-f6cf-415a-b193-655e25c97ad5)

#### 一些默认项的设置

在 /src/core/settings.js 中，可以设置播放选项的初始勾选情况，计算带宽的参数等

#### 执行ABR算法的流程

##### 前端记录使用哪些ABR算法

首先通过 **<u>*main.js: 564*</u>** 判断是否勾选了ABR Options中的Use Custom ABR Rules,记录在 **<u>*currentConfig.streaming.abr.useDefaultABRRules*</u>** 

如果是，将 **<u>*/samples/dash-if-reference/app/rules*</u>** 下的ABR算法加入到ABR算法列表中;如果否，将这些算法移除

在 <u>***main.js:2332***</u> 调用 **<u>*main.js:2143 setAbrRules()*</u>** 函数，根据播放设置记录是否勾选了 **<u>*InsufficientBufferRule*</u>** 等算法，以及使用哪种ABR Strategy。在main.js:631 中将勾选的算法加入到ABR算法列表中。在 main.js:532 设置使用哪种ABR Strategy

##### 后端读取使用哪些ABR算法

在 /src/streaming/rules/abr/ABRRulesCollection.js:61 中根据之前记录的数据来选择是否创建对应算法的工厂

