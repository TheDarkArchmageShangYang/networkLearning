# 自签名证书
[参考链接](https://blog.csdn.net/bluishglc/article/details/123617558?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522170184906816777224455514%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=170184906816777224455514&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduend~default-2-123617558-null-null.142^v96^pc_search_result_base2&utm_term=openssl%E8%AF%81%E4%B9%A6&spm=1018.2226.3001.4187)
生成CA私钥(ca.key)和CA自签名证书(ca.crt)

```
openssl req -x509 -newkey rsa:2048 -nodes -keyout ca.key -out ca.crt -days 3650  -subj "/C=CN/ST=shanghai/L=shanghai/O=example/OU=it/CN=domain1/CN=domain2"
```
生成Server端私钥(server.key)和证书签名请求(server.csr)
```
openssl req -new -newkey rsa:2048 -nodes -keyout server.key -out server.csr -subj "/C=CN/ST=shanghai/L=shanghai/O=example/OU=it/CN=domain1/CN=domain2"
```
使用CA证书(ca.crt)与密钥(ca.key)签署服务器的证书签名请求(server.csr)，生成私有CA签名的服务器证书(server.crt)
```
openssl x509 -req -in server.csr -CA ca.crt -CAkey ca.key -CAcreateserial -out server.crt -days 3650
```

## 使用certbot申请证书

1.安装snapd

正常情况ubuntu18以上默认安装，但有些未被安装，并且apt install会报错

在/etc/apt/preferences.d中可能有nosnap.pref,可以改个名字将其无效掉

```
sudo apt update
sudo apt install snapd
```

2.安装certbot

```
sudo snap install --classic certbot
```

3.准备certbot命令

```
sudo ln -s /snap/bin/certbot /usr/bin/certbot
```

4.运行certbot

```
sudo certbot certonly --standalone
```

