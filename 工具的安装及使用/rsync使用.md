## rsync使用
#### 密码登陆
```
rsync -r -va /home/fzchen/proxygen/ fzchen@60.204.136.199:/home/fzchen/proxygen/
```

#### 密钥登陆
假设从服务器A向服务器B传输文件

服务器A
```
ssh-keygen(创建密钥)
```
服务器B
```
保存服务器A上创建出的id_rsa.pub为id_rsa1.pub
cat id_rsa1.pub >> authorized_keys
```
服务器A
```
rsync -r -va -e "ssh -p2220" /home/fzchen/proxygen/ fzchen@60.204.136.199:/home/fzchen/proxygen/
```
-p表示端口号，22时可以连带-e "ssh"省略
