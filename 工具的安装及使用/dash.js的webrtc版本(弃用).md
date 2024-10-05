## GitHub地址

https://github.com/PJ-AWT-SS22-WebRTC-Broadcast-in-dash-js/webrtc-in-dash.js

## 问题

1.请求dash.all.debug.js时404

原因：未编译dash.js

解决方案：

```
npm install
npm run prepack
```

2.npm run prepack报错error:0308010C:digital envelope routines::unsupported

原因：node.js版本过高

解决方案：

1.降低node.js版本(17不行，16有人行，建议12/14)

2.在package.json中添加export SET NODE_OPTIONS=--openssl-legacy-provider(实测可行)

原本scripts部分

```
"scripts": {
    ......
    "prepack": "npm run build"
}
```

修改后

```
"scripts": {
    ......
    "prepack": "export SET NODE_OPTIONS=--openssl-legacy-provider && npm run build"
    // 似乎有版本更新了参数的位置，也可以尝试把参数放在命令后面
    // 如“start”：“react-scripts --openssl-legacy-provider start” ===> “start”：“react-scripts start --openssl-legacy-provider”
}
```

