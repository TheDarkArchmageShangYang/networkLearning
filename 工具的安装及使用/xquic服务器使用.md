[参考连接](https://github.com/alibaba/tengine/tree/master/modules/ngx_http_xquic_module)
#### 常见问题
问题1

![image](https://github.com/TheDarkArchmageShangYang/networkLearning/assets/149142839/17b9b03e-9450-4382-a7e8-0bb73acdfa56)
```
vim /etc/ld.so.conf
sudo ldconfig
在ld.so.conf中添加以下内容
/home/fzchen/worknew/xquic-1.6.0/build
```
sudo权限无法编辑ld.so.conf，root用户可以
问题2

![image](https://github.com/TheDarkArchmageShangYang/networkLearning/assets/149142839/b6a6443c-fe40-47cc-b932-7cf997fc726b)
```
sudo chown root tengine
sudo chmod u+s tengine
```
