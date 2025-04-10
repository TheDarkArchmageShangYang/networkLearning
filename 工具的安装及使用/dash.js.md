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
mp4dash fra_640x360_1000k.mp4
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
## 运行项目

windows需要先安装node.js，如果直接运行以下命令会报错，建议在git bash里运行

```
cd dash.js
npm install --force
npm run build
npm run start
```



## dash.js代码分析

针对参考播放器dash-if-reference

dash.js播放设置选项如下：
![image](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20241203043501224.png)

### 一些默认项的设置

#### 修改初始播放设置

在 /src/core/settings.js 中，可以设置播放选项的初始勾选情况，计算带宽的参数等

部分选项修改比较简单，如选项loop

只要在main.js:307修改

```
$scope.loopSelected = false;
```

部分选项修改比较复杂，如选项fastSwitchingABR，默认开启，但是可能会重复请求视频块，所以需要关闭

在index.html定义如下：

```
<label class="topcoat-checkbox" data-toggle="tooltip" data-placement="right"
       title="Enables faster ABR switching (time to render). Only when the new quality is higher than the current.">
    <input type="checkbox" id="fastSwitchCB" ng-model="fastSwitchSelected"
           ng-change="toggleFastSwitch()" ng-checked="fastSwitchSelected">
    Fast Switching ABR
</label>
```

<label>标签：

- class="topcoat-checkbox"：指定了该标签的样式类，通常用于引用特定的 CSS 样式。
- data-toggle="tooltip"：启用了工具提示功能，表示鼠标悬停在标签上时会显示提示文本。
- data-placement="right"：工具提示的位置，表示工具提示会显示在复选框的右侧。
- title 属性：工具提示的文本内容。这里是 "Enables faster ABR switching (time to render). Only when the new quality is higher than the current."，用于解释复选框的功能。

<input>标签：

- type="checkbox"：定义了一个复选框输入控件。
- id="fastSwitchCB"：为复选框指定了一个唯一的 ID，便于在其他地方引用。
- ng-model="fastSwitchSelected"：AngularJS 指令，用于将复选框的状态绑定到控制器中的 fastSwitchSelected变量。复选框的选中状态会同步到该变量中。
- ng-change="toggleFastSwitch()"：AngularJS 指令，当复选框的状态改变时，会调用控制器中的 toggleFastSwitch函数。
- ng-checked="fastSwitchSelected"：AngularJS 指令，用于初始化复选框的选中状态，根据 fastSwitchSelected 变量的值决定是否选中复选框。

1.修改默认值(可有可无，实际无影响)

在main.js:314

```
$scope.fastSwitchSelected = true;
```

默认值为true，将其改为false

2.在系统初始化完后再更新设置

在main.js:2350 init()函数中，会请求一个XMLHttpRequets对象，并根据此修改设置，其中fastSwitchEnabled默认为开启

所以需要在请求完之后额外修改想要的参数

```
(function init() {

        ////////////////////////////////////////
        //
        // Configuration file
        //
        ////////////////////////////////////////
        let reqConfig = new XMLHttpRequest();
        reqConfig.onload = function () {
            if (reqConfig.status === 200) {
                let config = JSON.parse(reqConfig.responseText);
                if ($scope.player) {
                    $scope.player.updateSettings(config);
                }
                //modify the setting after the request by cfz
                $scope.player.updateSettings({
                    'streaming': {
                        'buffer': {
                            'fastSwitchEnabled': $scope.fastSwitchSelected
                        }
                    }
                });
            } else {
```

3.调用复选框触发的函数(部分选项需要)

注意以上修改完只是在播放设置选项页面里设置，对于部分选项如是否使用默认ABR，如果勾选，还会触发其他效果，这部分需要额外添加代码。对于fastSwitchingEnabled选项来说不需要。

如想要设置默认使用自定义的ABR算法

在main.js:2235 setAdditionalAbrOptions()函数中

```c++
function setAdditionalAbrOptions() {
    var currentConfig = $scope.player.getSettings();
    $scope.fastSwitchSelected = currentConfig.streaming.buffer.fastSwitchEnabled;
    $scope.videoAutoSwitchSelected = currentConfig.streaming.abr.autoSwitchBitrate.video;
    $scope.customABRRulesSelected = !currentConfig.streaming.abr.useDefaultABRRules;
    // add by cfz
    $scope.toggleUseCustomABRRules();
}
```

这样才能默认使用自定义的ABR算法

#### 默认URL地址修改

main.js:38

```
$scope.selectedItem = {
    url: 'https://dash.akamaized.net/envivio/EnvivioDash3/manifest.mpd'
};
```



### 默认ABR逻辑

- 主要规则：使用**DYNAMIC**算法，在**ThroughputRule**和**BolaRule**之间切换。切换条件为
  - 初始化：**ThroughputRule**
  - 缓冲区长度低于**0.5*stableBufferTime**时，切换成**ThroughputRule**
  - 缓冲区长度超过**stableBufferTime**时，切换成**BolaRule**
- 次要规则：与主要规则选择的码率对比，取较小值
  - **InsufficientBufferRule** // 避免缓冲，当缓冲区长度较低时，采用更为保守的吞吐量估计
  - **SwitchHistoryRule** // 避免比特率快速切换，如果从某高比特率切换到低比特率，不允许在8个视频块内切换回去
  - **DroppedFramesRule** // 如果在某比特率下丢帧过多，不允许切换到该比特率以及更高的比特率
  - **AbandonRequestRule** // 如果视频块下载过程中有卡顿的风险，取消下载当前视频块，下载比特率更低的视频块

**ThroughputRule**和BolaRule切换的函数定义在**/src/streaming/controllers/AbrController.js:854 _updateDynamicAbrStrategy()**函数中

**stableBufferTime**计算在**/src/streaming/models/MediaPlayerModel.js:217 getStableBufferTime()**中，允许快速切换时为20s，不允许时为12s

### 执行ABR算法的流程

#### 前端记录使用哪些ABR算法

首先通过 **main.js: 564** 判断是否勾选了ABR Options中的Use Custom ABR Rules,记录在 **currentConfig.streaming.abr.useDefaultABRRules**

如果是，将 **/samples/dash-if-reference/app/rules** 下的ABR算法加入到ABR算法列表中;如果否，将这些算法移除

在 **main.js:2332** 调用 **main.js:2143 setAbrRules()** 函数，根据播放设置记录是否勾选了 **InsufficientBufferRule** 等算法，以及使用哪种ABR Strategy。在**main.js:631** 中将勾选的算法加入到ABR算法列表中。在 main.js:532 设置使用哪种ABR Strategy



#### 后端读取使用哪些ABR算法

在 **/src/streaming/rules/abr/ABRRulesCollection.js:61** 中根据之前记录的数据来选择是否创建对应算法的工厂(设计模式中的工厂模式)

以BolaRule算法为例，先调用函数 **BolaRule(context)** ，该函数定义在 **/src/streaming rules/abr/BolaRule.js:59** 。在该函数中

586行，又调用了 **/src/core/FactoryMaker.js:135** 的函数，该函数定义了 **create()** 函数，最后在 **ABRRulesCollection.js** 中被调用，创建**BolaRule**的工厂



#### 从ABR算法中获取比特率

**/src/streaming/controllers/ScheduleController.js:135 schedule()** 会调用 **AbrController.js:609 checkPlaybackQuality()** 来检查新视频块的比特率与上一个视频块是否相同

**checkPlaybackQuality()** 函数中调用 **ABRRulesCollection.js:203 getMaxQuality()** 来获取新视频块的比特率，如果与上一个视频块的比特率不同，则修改比特率

getMaxQuality() 函数先获取所有当前已启动的ABR算法，然后调用 **getMinSwitchRequest()** 函数，根据ABR算法的优先级 strong->default->weak 的顺序来选择优先级最高且最小(不同算法算出来的相同优先级的比特率取最小的)的比特率。



#### 添加自定义ABR算法

**main.js:564** 添加想要添加的算法

**index.html** 添加算法所在的JS文件



### 在前端网页上添加一些显示参数

参考页面如下

![image-20240423154621871](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20241203043514610.png)

以上内容在 **/samples/dash-if-reference-player/index.html:1001** 行定义

例如第一项 **Buffer Length**，代码如下

```javascript
<div class="text-success">
	<input id="videoBufferCB" type="checkbox" ng-model="chartState.video.buffer.selected"
           ng-change="enableChartByName('buffer', 'video')">
    <label class="text-primary" for="videoBufferCB" data-toggle="tooltip"
           data-placement="top"
           title="The length of the forward buffer, in seconds">Buffer Length : </label> {{videoBufferLength}}
</div>
```

第一行使用了 **Bootstrap** 的样式类 **"text-success"** ，表示文本颜色为绿色。 **Bootstrap** 是一个前端框架。

第二行定义了一个复选框，分析如下

- **id="videoBufferCB"** 表示该复选框ID为 **"videoBufferCB"**
- **type="checkbox"** 表示输入框类型为复选框
- **ng-model="chartState.video.buffer.selected"** 使用 **Angular JS** 的 **ng-model** 指令，将该复选框与 **Angular JS** 控制器中的数据模型进行绑定
- **ng-change="enableChartByName('buffer', 'video')"** 当复选框的状态改变时，调用 **Angular JS** 中的 **enableChartByName()** 函数，传递 **buffer** 和 **video** 作为参数

第三行是一个标签元素，分析如下

- **class="text-primary"** 使用了 **Bootstrap** 的样式类 **"text-primary"**，表示文本颜色为蓝色
- **for="videoBufferCB"** 表示点击标签会触发复选框 **videoBufferCB** 的状态改变
- **data-toggle="tooltip" data-placement="top" title="The length of the forward buffer, in seconds"** 表示鼠标悬停在标签上时，标签上方会出现提示信息"The length of the forward buffer, in seconds" 。
- **{{videoBufferLength}}** 这是 Angular JS的语法，用于在HTML中插入变量值，这里将显示变量 **videoBufferLength** 的值



函数 enableChartByName() 定义在 /samples/dash-if-reference-player/app/main.js:2019 

主要作用是图像数量未满时根据复选框是否选中来画图/去除图像，如果图像数量已满且复选框已选中则全部设为未选中

其中每一项的初始是否勾选，颜色，标签等设置在136行



数据的读取在main.js:2061 updateMetrics()函数中

部分参数的计算如带宽、下载时间等在main.js:1921 calculateHTTPMetrics()函数中

请求时间的计算在1934行根据tresponse(客户端接收到响应的第一个字节的时间) - trequest(客户端发出HTTP请求的时间)

下载时间的计算在1951行根据_tfinish(客户端接收到响应的最后一个字节的时间) - tresponse(客户端接收到响应的第一个字节的时间)

##### 添加一些参数？

1.在index.html:1001行左右添加复选框

```javascript
<div class="text-success">
    <input id="videoRebufferTimeCB" type="checkbox" ng-model="chartState.video.rebufferTime.selected"
           ng-change="enableChartByName('rebufferTime', 'video')">
    <label class="text-primary" for="videoRebufferTimeCB" data-toggle="tooltip"
           data-placement="top"
           title="The total rebuffer time of the video">Rebuffer Time
        :</label> {{videoRebufferTime}} ms
</div>
```

2.在main.js:136行左右的audio和video中添加,自己找个颜色

```javascript
rebufferTime: { data: [], selected: true, color: '#326e88', label: 'Rebuffer Time (ms)' }
```

如果只添加在video，控制台会报错，但是能运行

3.获取想要输出的数据

4.在main.js:2063 updateMetrics()中添加以下内容

```javascript
// 显示具体数值,用来传递给刚刚定义的label
$scope[type + 'RebufferTime'] = $scope.rebufferTime;

// 画图
$scope.plotPoint('rebufferTime', type, $scope.rebufferTime, time);
```

5.此时播放初始界面通常如下:视频平均清晰度:kbps

我们希望改成视频平均清晰度:0kbps

在main.js:272左右增加

```c++
$scope.videoRebufferTime = 0;
```



### 播放流程

#### 核心逻辑

##### 前后端连接

网页有播放/暂停按钮，定义如下:

```javascript
<div id="playPauseBtn" class="btn-play-pause" data-toggle="tooltip" data-placement="bottom"
	title="Play/Pause">
	<span id="iconPlayPause" class="icon-play"></span>
</div>
```

触发函数定义在**/contrib/akamai/controlbar/ControlBar.js:1054**

- **/contrib/akamai/controlbar/ControlBar.js:171 _onPlayPauseClick()**
  - **ControlBar.js:147 togglePlayPauseBtnState()**
  - **/src/streaming/MediaPlayer.js:596 isPaused()**
    - **/src/streaming/controllers/PlaybackController.js:296 isPaused()**
  - **MediaPlayer.js:596 play()** // 根据按钮情况执行play()或pause()
    - **PlaybackController.js:296 play()**
      - **/src/streaming/models/VideoModel.js:294 play()**
        - **PlaybackController.js:855**
          - **PlaybackController.js:606 _onPlaybackStart()**
            - **eventBus.trigger(Events.PLAYBACK_STARTED...)**
  - **MediaPlayer.js:596 pause()**
    - **PlaybackController.js:296 pause()**
      - **/src/streaming/models/VideoModel.js:313 pause()**
        - **PlaybackController.js:858**
          - **PlaybackController.js:624 _onPlaybackPaused()**
            - **eventBus.trigger(Events.PLAYBACK_PAUSED...)**

播放主逻辑：事件**Events.PLAYBACK_STARTED**

##### 事件监听器注册：

- **/src/streaming/controllers/StreamController.js:123 registerEvents()**
  - **eventBus.on(MediaPlayerEvents.PLAYBACK_STARTED, _onPlaybackStarted...);**

- **/src/streaming/controllers/ScheduleController.js:76 initialize()**
  - **eventBus.on(MediaPlayerEvents.PLAYBACK_STARTED _onPlaybackStarted...)**

##### 触发事件&函数调用

- **/src/streaming/controllers/PlaybackController.js:606 _onPlaybackStart()**
  - **eventBus.trigger(Events.PLAYBACK_STARTED...)**
    - **/src/streaming/controllers/ScheduleController.js:389 _onPlaybackStarted()**
      - **ScheduleController.js:103 startScheduleTimer()** // 设置计时器，在 **/src/code/Setting.js** 中，将默认值设为500ms，计时器结束后，该函数调用 **schedule()** 函数。
        - **ScheduleController.js:135 schedule()**  // 判断当前是否需要请求下一个视频块，如果不需要，就会重新调用**startScheduleTimer()** 函数继续阻塞500ms

##### 核心函数调用

- **/src/streaming/controllers/ScheduleController.js:135 schedule()**
  
  - **ScheduleController.js:214 _shouldScheduleNextRequest()** // 判断是否请求下一个视频块
  
  - **/src/streaming/controllers/AbrController.js:609 checkPlaybackQuality()** // 检查新视频块的比特率与上一个视频块是否相同
  
    - **/src/streaming/rules/abr/ABRRulesCollection.js:203 getMaxQuality()**
      - **ABRRulesCollection.js:146 _getRulesWithChange()** // 获取启用的ABR算法
      - **ABRRulesCollection.js:150 getMinSwitchRequest()** // 根据ABR算法的优先级 strong->default->weak 的顺序来选择优先级最高且最小(不同算法算出来的相同优先级的比特率取最小的)的比特率。
    - **AbrController.js:737 _changeQuality()** //需要切换比特率时
  
    - **ScheduleController.js:165 _getNextFragment()** // 不需要切换比特率时



- **AbrController.js:737 _changeQuality()** //需要切换比特率
  - **eventBus.trigger(Events.QUALITY_CHANGE_REQUESTED...)**
    - **/src/streaming/controllers/StreamProcessor.js:768 _onQualityChanged()**
      - **/src/streaming/Stream.js:739 prepareQualityChange()**
        - **/src/streaming/StreamProcessor.js:641 prepareQualityChange()**
          - **/src/dash/controllers/RepresentationController.js:312 prepareQualityChange()**
            - **/src/dash/controllers/RepresentationController.js:318 _setCurrentVoRepresentation()**
              - **/src/dash/DashAdapter.js:89 convertRepresentationToRepresentationInfo()**
            - **/src/dash/controllers/RepresentationController.js:223 _addRepresentation()**
              - **eventBus.trigger(MediaPlayerEvents.REPRESENTATION_SWITCH...)**
                - **PlaybackController.js _onRepresentationSwitch()**
          - **/src/streaming/StreamProcessor.js:686 _prepareForForceReplacementQualitySwitch()** // 4个if..else if语句，固定比特率时触发
          - **/src/streaming/StreamProcessor.js:714 _prepareForAbandonQualitySwitch()** // Options勾选AbandonRequestsRule或者自定义ABR设置为abandonFragmentRules时触发
          - **/src/streaming/StreamProcessor.js:730 _prepareForFastQualitySwitch()** // Options勾选Fast Switching ABR时触发
          - **/src/streaming/StreamProcessor.js:772 _prepareForDefaultQualitySwitch()** // 默认情况下触发



#### 请求视频块

##### 触发事件&函数调用

- **ScheduleController.js:165 _getNextFragment()**
  - **eventBus.trigger(Events.INIT_FRAGMENT_NEEDED...)**
    - **/src/streaming/StreamProcessor.js:385 _onInitFragmentNeeded()**
      - **/src/dash/DashHandler.js:128 getInitRequest()** //获取请求的内容
      - **/src/streaming/models/FragmentModels.js:202 executeRequest()**
  - **eventBus.trigger(Events.MEDIA_FRAGMENT_NEEDED...)**
    - **StreamProcessor.js:422 _onMediaFragmentNeeded()**
      - **StreamProcessor.js:535 _getFragmentRequest()** //获取请求的内容
      - **StreamProcessor.js:445 _mediaRequestGenerated()**
        - **FragmentModels.js:202 executeRequest()**

##### 请求视频块相关函数调用

- **FragmentModels.js:202 executeRequest()**
  - **FragmentModels.js:214 loadCurrentFragment()**
    - **eventBus.trigger(events.FRAGMENT_LOADING_STARTED...)**
    - **/src/streaming/FragmentLoader.js:87 load()**
      - **/src/streaming/net/URLLoader.js:51 load()**
        - **/src/streaming/net/SchemeLoaderFactory.js:59 getLoader()**
        - **/src/streaming/HTTPLoader.js:59 load()**

##### 请求内容生成相关函数调用

- **StreamProcessor.js:385 _onInitFragmentNeeded()**
  - **DashHandler.js:128 getInitRequest()**
    - **DashHandler.js:133 _generateInitRequest()**
- **StreamProcessor.js:422 _onMediaFragmentNeeded()**
  - **StreamProcessor.js:535 _getFragmentRequest()**
    - **DashHandler.js:236 getSegmentRequestForTime()**
      - **DashHandler.js:153 _getRequestForSegment()**
        - **DashHandler.js:99 _setRequestUrl()** // 设置URL
    - **DashHandler.js:272 getNextSegmentRequest()**
      - **let indexToRequest = lastSegment ? lastSegment.index + 1 : 0;** // 下一个视频块
      - **DashHandler.js:298 _getRequest()**
        - **DashHandler.js:153 _getRequestForSegment()**

#### 读取参数

bufferLevel

```
const DashMetrics = factory.getSingletonFactoryByName('DashMetrics');
let dashMetrics = DashMetrics(context).getInstance();
const mediaType = rulesContext.getMediaType();
let bufferLevel = dashMetrics.getCurrentBufferLevel(mediaType);
```

- /src/dash/DashMetrics.js:110 getCurrentBufferLevel(mediaType)
  - const metrics = metricsModel.getMetricsFor(*mediaType*, true);
    - /src/streaming/models/MetricsModel.js:92 getMetricsFor(type, readOnly)
  - const metric = getCurrent(metrics, MetricsConstants.BUFFER_LEVEL);
    - DashMetrics:239 getCurrent(metrics, metricName)
  - return Round10.round10(metric.level / 1000, -3);

- /src/streaming/controllers/StreamController.js:744 _onBufferLevelUpdated(e)
  - DashMetrics.js:142 addBufferLevel(mediaType, t, level)
    - /src/streaming/models/MetricsModel.js:224 addBufferLevel(mediaType, t, level)
      - MetricsModel.js:219 pushAndNotify()
        - MetricsModel.js:109 pushMetrics()
        - MetricsModel.js:77 metricAdded(mediaType, metricType, vo)
          - eventBus.trigger(Events.METRIC_ADDED...)
          - MetricsModel.js:67 metricChanged(mediaType)
            - eventBus.trigger(Events.METRIC_CHANGED...)
            - MetricsModel.js:63 metricsChanged()
              - eventBus.trigger(Events.METRICS_CHANGED...)

#### 收到视频块

### 监听事件

由于/src外的代码无法通过Factory读取事件类，所以无法监听事件(不确定)。但是在index.html和main.js可以监听，所以卡顿时间、视频总质量可以通过在main.js中监听BUFFER_EMPTY、BUFFER_LOADED等事件来计算



以事件FRAGMENT_LOADING_COMPLETED为例：

该事件在/src/streaming/models/FragmentModel.js:273 onLoadingCompleted()中定义

![image-20240530133415036](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20241203043526280.png)

所以在监听该事件的函数中，可以调用e.request、e.response等对象

注意**request: e.request**该行代码，request表示该事件后续可以调用e.request，e.request表示赋值，由于触发该事件的函数同样监听另一个事件，在那个事件中也定义了request，相当于参数传递

一步步找到最初的request，发现就是在请求视频块时发出的请求

属性定义在/src/streaming/vo/FragmentRequest.js

属性赋值在/src/dash/DashHandler.js:153 _getRequestForSegment()中，属性如下：
![image-20240530133217627](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20241203043530451.png)

可以看到其中并没有trequest、tresponse等属性

但是在main.js:1971 calculateHTTPMetrics()函数中，有req.trequest、req.tresponse等

属性定义在/src/streaming/vo/metrics/HTTPRequest.js

属性赋值在/src/streaming/net/HTTPLoader.js:116 addHttpRequestMetric()函数中

### 每次视频第一个块

也通过scheduleController的schedule函数，但是发header.m4s时不经过checkPlaybackQuality，但此时读取RepresentationInfo已经有码率了，然后通过_getNextFragment()的INIT_FRAGMENT_NEEDED发出
