# WebRTC

WebRTC由3部分组成:

- 客户端:主要提供视频/文件等
- 信令服务器:交换客户端的信令
- STUN/TRUN服务器:为没有公网IP的客户端提供公网IP

## 信令服务器

信令服务器不是由WebRTC API来实现,可以自由选择搭建方式,例如Websocket

交换信令(SDP)流程:

- 客户端A创建一个RTCPeerConnection对象
- A使用RTCPeerConnection的createOffer()方法创建一个Offer
- A调用setLocalDescription()将Offer设置为本地的SDP
- A将Offer发给信令服务器,信令服务器将Offer发给其他所有客户端(此时仅有客户端B)
- B调用setRemoteDescription()将Offer设置为远程的SDP
- B调用createAnswer()创建一个Answer
- B调用setLocalDescription()将Answer设置为本地的SDP
- B将Answer发给信令服务器,信令服务器将Answer发给A
- A调用setRemoteDescription()将Answer设置为远程的SDP

## 客户端

客户端之间传输数据有两种方式,一种是track,只能用于传输音视频数据,另一种是datachannel,可以传输任意数据/文件.

## v1.0

### 简易客户端(使用datachannel)

客户端可以搭建在Windows主机或者Linux主机上

#### Windows

client.html

```c++
<!DOCTYPE html>
<html lang="zh">
<head>
    <meta charset="UTF-8">
    <title>WebRTC 文本通信</title>
</head>
<body onload="pageReady()">

<div>
    <button onclick="start(true)">开始通信</button>
</div>

<div>
    <label for="messageInput">输入消息:</label>
    <input type="text" id="messageInput"/>
    <button onclick="sendMessage()">发送消息</button>
    <button onclick="sendFile()">发送文件</button>
</div>

<div>
    <h3>接收到的消息:</h3>
    <div id="messages"></div>
</div>

<script src="webrtc.js"></script>
</body>
</html>

```

webrtc.js

```c++
let peerConnection;
let serverConnection;
let uuid;
let dataChannel;

async function pageReady() {
  uuid = createUUID();

  serverConnection = new WebSocket(`wss://udpcc-shh.dfshan.net:8443`);
  serverConnection.onmessage = gotMessageFromServer;
}

function start(isCaller) {
  peerConnection = new RTCPeerConnection();
  peerConnection.onicecandidate = gotIceCandidate;

  // 创建数据通道用于传输文本信息
  if (isCaller) {
    dataChannel = peerConnection.createDataChannel("chat");
    setupDataChannel();
    peerConnection.createOffer().then(createdDescription).catch(errorHandler);
  } else {
    peerConnection.ondatachannel = event => {
      dataChannel = event.channel;
      setupDataChannel();
    };
  }
}

function setupDataChannel() {
  dataChannel.onopen = () => console.log("Data channel opened");
  dataChannel.onmessage = event => {
    console.log("Received message: " + event.data);
    displayMessage("Received: " + event.data);
  };
}

// 处理 WebSocket 服务器发送的消息
function gotMessageFromServer(message) {
  if(!peerConnection) start(false);

  const signal = JSON.parse(message.data);

  // 忽略自己发送的消息
  if(signal.uuid == uuid) return;

  if(signal.sdp) {
    peerConnection.setRemoteDescription(new RTCSessionDescription(signal.sdp)).then(() => {
      if(signal.sdp.type === 'offer') {
        peerConnection.createAnswer().then(createdDescription).catch(errorHandler);
      }
    }).catch(errorHandler);
  } else if(signal.ice) {
    peerConnection.addIceCandidate(new RTCIceCandidate(signal.ice)).catch(errorHandler);
  }
}

function gotIceCandidate(event) {
  if(event.candidate != null) {
    serverConnection.send(JSON.stringify({'ice': event.candidate, 'uuid': uuid}));
  }
}

function createdDescription(description) {
  peerConnection.setLocalDescription(description).then(() => {
    serverConnection.send(JSON.stringify({'sdp': peerConnection.localDescription, 'uuid': uuid}));
  }).catch(errorHandler);
}

// 发送文本消息
function sendMessage() {
  const message = document.getElementById("messageInput").value;
  dataChannel.send(message);
  displayMessage("Sent: " + message);
  document.getElementById("messageInput").value = "";
}

// 显示消息
function displayMessage(message) {
  const messagesDiv = document.getElementById("messages");
  const newMessage = document.createElement("p");
  newMessage.textContent = message;
  messagesDiv.appendChild(newMessage);
}

function errorHandler(error) {
  console.log(error);
}

function createUUID() {
  function s4() {
    return Math.floor((1 + Math.random()) * 0x10000).toString(16).substring(1);
  }
  return `${s4() + s4()}-${s4()}-${s4()}-${s4()}-${s4() + s4() + s4()}`;
}

```

#### Linux

使用Node.js来搭建简易HTTP服务器

```javascript
const WebSocket = require('ws');
const wrtc = require('wrtc');

let peerConnection;
let dataChannel;
let uuid;
let serverConnection;

const peerConnectionConfig = {
  iceServers: []
};

// 创建唯一标识符（UUID）
function createUUID() {
  return `${Math.random().toString(16).slice(2)}-${Math.random().toString(16).slice(2)}`;
}

// 连接 WebSocket 服务器
function connectWebSocket() {
  uuid = createUUID();
  serverConnection = new WebSocket('wss://udpcc-shh.dfshan.net:8443');

  serverConnection.onopen = () => {
    console.log('已连接到 WebSocket 服务器');
  };

  serverConnection.onmessage = (message) => {
    handleServerMessage(message.data);
  };

  serverConnection.onclose = () => {
    console.log('WebSocket 连接已关闭');
  };
}

// 处理来自 WebSocket 服务器的消息
function handleServerMessage(data) {
  const signal = JSON.parse(data);

  // 忽略自己发送的消息
  if (signal.uuid === uuid) return;

  if (signal.sdp) {
    peerConnection.setRemoteDescription(new wrtc.RTCSessionDescription(signal.sdp)).then(() => {
      if (signal.sdp.type === 'offer') {
        peerConnection.createAnswer().then(createLocalDescription).catch(errorHandler);
      }
    }).catch(errorHandler);
  } else if (signal.ice) {
    peerConnection.addIceCandidate(new wrtc.RTCIceCandidate(signal.ice)).catch(errorHandler);
  }
}

// 初始化 WebRTC 连接
function startWebRTC(isCaller) {
  peerConnection = new wrtc.RTCPeerConnection(peerConnectionConfig);

  peerConnection.onicecandidate = (event) => {
    if (event.candidate) {
      serverConnection.send(JSON.stringify({ ice: event.candidate, uuid }));
    }
  };

  if (isCaller) {
    dataChannel = peerConnection.createDataChannel('chat');
    setupDataChannel();
    peerConnection.createOffer().then(createLocalDescription).catch(errorHandler);
  } else {
    peerConnection.ondatachannel = (event) => {
      dataChannel = event.channel;
      setupDataChannel();
    };
  }
}

// 设置数据通道
function setupDataChannel() {
  dataChannel.onopen = () => console.log('数据通道已打开');
  dataChannel.onmessage = (event) => {
    console.log('收到消息:', event.data);
  };
}

// 创建本地 SDP 并发送到服务器
function createLocalDescription(description) {
  peerConnection.setLocalDescription(description).then(() => {
    serverConnection.send(JSON.stringify({ sdp: peerConnection.localDescription, uuid }));
  }).catch(errorHandler);
}

// 发送文本消息
function sendMessage(message) {
  if (dataChannel && dataChannel.readyState === 'open') {
    dataChannel.send(message);
    console.log('发送消息:', message);
  } else {
    console.log('数据通道未就绪，无法发送消息');
  }
}

// 错误处理
function errorHandler(error) {
  console.error('发生错误:', error);
}

// 主函数
function main() {
  const isCaller = process.argv.includes('--caller');

  connectWebSocket();

  serverConnection.onopen = () => {
    startWebRTC(isCaller);

    if (isCaller) {
      // 示例：延迟 2 秒发送消息
      setTimeout(() => {
        sendMessage('Hello from caller!');
      }, 2000);
    }
  };
}

// 启动客户端
main();

```

安装依赖

```shell
sudo apt install npm
npm install ws
npm install wrtc

// 如果npm install wrtc报错
sudo npm i -g node-pre-gyp
// 如果还失败
sudo npm i -g node-pre-gyp --registry=https://registry.npmmirror.com --verbose
```



### 简易信令服务器

```py
import asyncio
import websockets
import ssl

# 配置部分
WEBSOCKET_HOST = '0.0.0.0'  # 监听所有网络接口
WEBSOCKET_PORT = 8443       # WebSocket服务器端口

# SSL/TLS 配置
SSL_CERT_PATH = '/home/fzchen/cert/fullchain.pem'  # 替换为您的证书路径
SSL_KEY_PATH = '/home/fzchen/cert/privkey.pem'     # 替换为您的私钥路径

# 存储所有连接的客户端
connected_clients = set()

async def register(websocket):
    connected_clients.add(websocket)
    print(f"客户端已连接：{websocket.remote_address}")

async def unregister(websocket):
    connected_clients.remove(websocket)
    print(f"客户端已断开：{websocket.remote_address}")

async def websocket_handler(websocket, path):
    await register(websocket)
    try:
        async for message in websocket:
            print(f"收到来自客户端的消息：{message}")
            
            # 将收到的消息转发给所有其他客户端
            for client in connected_clients:
                if client != websocket:
                    await client.send(message)
    except websockets.exceptions.ConnectionClosed:
        pass
    finally:
        await unregister(websocket)

async def main():
    # 创建 SSL 上下文
    ssl_context = ssl.SSLContext(ssl.PROTOCOL_TLS_SERVER)
    ssl_context.load_cert_chain(certfile=SSL_CERT_PATH, keyfile=SSL_KEY_PATH)

    # 启动WebSocket服务器，启用 SSL
    server = await websockets.serve(websocket_handler, WEBSOCKET_HOST, WEBSOCKET_PORT, ssl=ssl_context)
    print(f"WebSocket信令服务器已启动, 监听 {WEBSOCKET_HOST}:{WEBSOCKET_PORT} (WSS)")

    # 保持服务器运行
    await server.wait_closed()

if __name__ == "__main__":
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        print("信令服务器已关闭。")

```



## v2.0

### 客户端(使用track)

video_provider.html

```javascript
<!DOCTYPE html>
<html lang="zh">
<head>
  <meta charset="UTF-8">
  <title>Video Provider</title>
</head>
<body  onload="pageReady()">
    <h1>Video Provider</h1>
    <div id="button">
        <button id="playPauseButton">播放</button>
        <h2>视频播放信息</h2>
        <p id="bitrate">平均码率: 0kbps</p>
        <p id="rebufferTime">卡顿时间: 0ms</p>
    </div>
    <video id="localVideo" controls playsinline>
        <source src="../video/output.mp4" type="video/mp4"/>
    </video>
  

  <script>
    let stream;
    const localVideo = document.getElementById("localVideo");
    const playPauseButton = document.getElementById("playPauseButton");

    playPauseButton.addEventListener("click", () => {
        localVideo.play();
        playPauseButton.textContent = "暂停";
        localVideo.oncanplay = maybeCreateStream;
        if (localVideo.readyState >= 3) {
            maybeCreateStream();
        }
        startWebrtc();
    });

    function maybeCreateStream() {
        if (stream) {
            return;
        }
        if (localVideo.captureStream) {
            stream = localVideo.captureStream();
            console.log('Captured stream from leftVideo with captureStream', stream);
        } else if (localVideo.mozCaptureStream) {
            stream = localVideo.mozCaptureStream();
            console.log('Captured stream from leftVideo with mozCaptureStream()', stream);
        } else {
            console.log('captureStream() not supported');
        }
    }

    let peerConnection;
    let serverConnection;
    let uuid = "video_send"; 

    const offerOptions = {
        offerToReceiveAudio: 1,
        offerToReceiveVideo: 1
    };

    async function pageReady() {
        serverConnection = new WebSocket(`wss://udpcc-shh.dfshan.net:8443`);
        serverConnection.onopen = () => {
            console.log('WebSocket 连接已建立');
        }
        serverConnection.onmessage = gotMessageFromServer;
        serverConnection.onerror = (error) => {
            console.error('WebSocket 连接错误:', error);
        };
        
        serverConnection.onclose = () => {
            console.log('WebSocket 连接已关闭');
        };
    }

    function updateRebufferTime(rebufferTime) {
        const rebuffer = document.getElementById('rebufferTime');
        rebuffer.textContent = `总卡顿时间: ${rebufferTime.toFixed(2)} 秒`;
    }

    function gotMessageFromServer(message) {
        if (!peerConnection) startWebrtc();

        const signal = JSON.parse(message.data);
        console.log(signal);

        if (signal.uuid === uuid) return;

        if (signal.sdp) {
            // console.log(signal.sdp);
            peerConnection.setRemoteDescription(new RTCSessionDescription(signal.sdp))
            .then(() => {
                if (signal.sdp.type === 'offer') {
                    peerConnection.createAnswer().then(createdDescription).catch(errorHandler);
                }
            }).catch(errorHandler);
        } else if (signal.ice) {
            // console.log(signal.ice);
            // if (!signal.ice.candidate) {
            //     return;
            // }
            peerConnection.addIceCandidate(new RTCIceCandidate(signal.ice)).catch(errorHandler);
        }
    };

    function startWebrtc() {
        console.log("start webrtc");
        peerConnection = new RTCPeerConnection();

        peerConnection.onicecandidate = (event) => {
            if (event.candidate) {
                console.log(event.candidate);
                sendWebSocketMessage(JSON.stringify({'ice': event.candidate, 'uuid': uuid}));
            }
        };

        console.log(stream);
        stream.getTracks().forEach((track) => peerConnection.addTrack(track, stream));
        //   localVideo.srcObject = stream;
        peerConnection.createOffer(offerOptions).then(createdDescription).catch(errorHandler);
    }
    
    function createdDescription(description) {
        console.log(description);
        peerConnection.setLocalDescription(description)
        .then(() => {
            sendWebSocketMessage(JSON.stringify({'sdp': peerConnection.localDescription, 'uuid': uuid}));
        })
        .catch((error) => {
            console.error('创建LocalSDP失败:', error);
        });
    }

    function sendWebSocketMessage(message) {
        if (serverConnection.readyState === WebSocket.OPEN) {
            serverConnection.send(message);
        } else {
            console.error('WebSocket 未连接，无法发送消息');
        }
    }

    function errorHandler(error) {
        console.error('发生错误:', error);
    }
  </script>
</body>
</html>

```

video_receiver.html

```javascript
<!DOCTYPE html>
<html lang="zh">
<head>
    <meta charset="UTF-8">
    <title>Video Receiver</title>
</head>
<body  onload="pageReady()">
    <h1>Video Receiver</h1>
    <div id="video">
        <video id="remoteVideo" autoplay controls playsinline></video>
    </div>
    <div id="info">
        <p id="bitrate">平均码率: 0kbps</p>
        <p id="rebufferTime">卡顿时间: 0ms</p>
    </div>

  <script>
    const remoteVideo = document.getElementById("remoteVideo");

    let peerConnection;
    let serverConnection;
    let uuid = "video_recv";

    const peerConnectionConfig = {
        iceServers: [],
        iceTransportPolicy: 'all'
    };

    async function pageReady() {
        setWebSocket();
        remoteVideo.addEventListener('play', () => {
            setupMetric();
        });
        // setupMetric();
    }

    function setWebSocket() {
        serverConnection = new WebSocket(`wss://udpcc-shh.dfshan.net:8443`);
        serverConnection.onopen = () => {
            console.log('WebSocket 连接已建立');
        }
        serverConnection.onmessage = gotMessageFromServer;
        serverConnection.onerror = (error) => {
            console.error('WebSocket 连接错误:', error);
        };
        
        serverConnection.onclose = () => {
            console.log('WebSocket 连接已关闭');
        };
    }

    // function setupMetric() {
    //     let totalPlayTime = 0;
    //     let rebufferTime = 0;
    //     let frameCount = 0;
    //     let idealFrameInterval = 33;
    //     let lastFrameTime = 0;

    //     const calculateMetrics = () => {
    //         frameCount++;
    //         let now = performance.now();
    //         totalPlayTime = remoteVideo.currentTime * 1000;
    //         if (totalPlayTime > 40 * frameCount) {
    //             rebufferTime = totalPlayTime - 40 * frameCount;
    //         }
    //         remoteVideo.requestVideoFrameCallback(calculateMetrics);
    //     };

    //     remoteVideo.requestVideoFrameCallback(calculateMetrics);

    //     setInterval(() => {
    //         const stallRate = (rebufferTime / totalPlayTime) * 100;
    //         updateRebufferTime(rebufferTime / 1000);
    //         console.log(`总播放时间: ${totalPlayTime / 1000} 秒, ${remoteVideo.currentTime}`);
    //         console.log(`累计卡顿时间: ${rebufferTime / 1000} 秒`);
    //         console.log(`卡顿率: ${stallRate.toFixed(2)}%`);
    //         console.log(`累计播放帧数: ${frameCount}`);
    //     }, 1000);
    // }
    function setupMetric() {
        const interval = 1000; 
        let videoStats = {};

        const intervalId = setInterval(async () => {
            try {
                const stats = await peerConnection.getStats();

                stats.forEach(report => {
                    // console.log(report);
                    if (report.type === 'inbound-rtp' && report.kind === 'video') {
                        videoStats.framesPerSecond = report.framesPerSecond;
                        videoStats.framesReceived = report.framesReceived;
                        updateRebufferTime((1 - videoStats.framesReceived * 40 / 1000 / remoteVideo.currentTime) * 100);
                    }
                    if (remoteVideo.currentTime > 193.68) {
                        console.log("计时结束");
                        clearInterval(intervalId);
                    }
                });

                console.log(videoStats.framesPerSecond, videoStats.framesReceived, remoteVideo.currentTime);

            } catch (error) {
                console.error("Error fetching stats:", error);
            }
        }, interval);
    }



    function updateBitrate(bitrate) {
        const aveBitrate = document.getElementById('bitrate');
        aveBitrate.textContent = `平均码率: ${bitrate} kbps`;
    }

    function updateRebufferTime(rebufferTime) {
        const rebuffer = document.getElementById('rebufferTime');
        rebuffer.textContent = `卡顿率: ${rebufferTime.toFixed(2)}%`;
    }

    function gotMessageFromServer(message) {
        if (!peerConnection) startWebrtc();

        const signal = JSON.parse(message.data);
        // console.log(signal);

        if (signal.uuid == uuid) return;

        if (signal.sdp) {
            // console.log(data);
            peerConnection.setRemoteDescription(new RTCSessionDescription(signal.sdp))
            .then(() => {
                if (signal.sdp.type === 'offer') {
                    peerConnection.createAnswer().then(createdDescription).catch(errorHandler);
                }
            }).catch(errorHandler);
        } else if (signal.ice) {
            // console.log(data.ice);
            // if (!signal.ice.candidate) {
            //     return;
            // }
            peerConnection.addIceCandidate(new RTCIceCandidate(signal.ice)).catch(errorHandler);
        }
    };

    function startWebrtc() {
        peerConnection = new RTCPeerConnection(peerConnectionConfig);

        peerConnection.onicecandidate = (event) => {
            if (event.candidate) {
                // console.log('生成的 ICE 候选者:', event.candidate);
                sendWebSocketMessage(JSON.stringify({'ice': event.candidate, 'uuid': uuid}));
            } else {
                console.log('ICE 候选者生成完毕');
            }
        };

        peerConnection.ontrack = (event) => {
            remoteVideo.srcObject = event.streams[0];
            console.log("收到远程视频流");
            updateBitrate(1200);
        };

        // peerConnection.createOffer().then(createdDescription).catch(errorHandler);
    }

    function createdDescription(description) {
        peerConnection.setLocalDescription(description)
        .then(() => {
            sendWebSocketMessage(JSON.stringify({'sdp': peerConnection.localDescription, 'uuid': uuid}));
        })
        .catch((error) => {
            console.error('创建LocalSDP失败:', error);
        });
    }

    function sendWebSocketMessage(message) {
        if (serverConnection.readyState === WebSocket.OPEN) {
            serverConnection.send(message);
        } else {
            console.error('WebSocket 未连接，无法发送消息');
        }
    }

    function errorHandler(error) {
        console.error('发生错误:', error);
    }
  </script>
</body>
</html>

```



## 统计信息

### 卡顿率



## 注意事项

1.firefox默认选项会把ip地址转换为xxxx.local,导致其他客户端无法解析

可以在`about:config`中关闭``media.peerconnection.ice.obfuscate_host_addresses`选项
