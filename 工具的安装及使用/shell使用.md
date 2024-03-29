# shell使用
推荐使用zsh
终端复用工具推荐tmux
## zsh
#### 安装
```
sudo apt install zsh
```
#### 安装oh-my-zsh
```
sh -c "$(wget -O- https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"
```
.oh-my-zsh和.zshrc文件都在/home/fzchen下
#### 安装插件
/home/fzchen/.oh-my-zsh/custom/plugins
```
# zsh-suggestions:根据历史命令和当前输入，自动提示命令参数和选项
git clone https://github.com/zsh-users/zsh-autosuggestions ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-autosuggestions
# zsh-syntax-highlighting:根据语法高亮显示命令和文件路径等内容
git clone https://github.com/zsh-users/zsh-syntax-highlighting.git ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-syntax-highlighting
# autojump:根据使用频率，自动跳转到最常用的目录
git clone https://github.com/wting/autojump.git
# fzf:快速模糊搜索历史命令和文件路径
git clone --depth 1 https://github.com/junegunn/fzf.git ~/.fzf
```
## tmux
可以后台执行脚本(即使关闭终端)
#### 安装
```
$ sudo apt-get install tmux
```
#### 快捷键
在tmux中ctrl+b是快捷键前缀<br>
使用流程为:先按下ctrl+b，松开，再按其他键
###### 会话管理
s:列出所有会话
d:断开当前会话
###### 窗口管理
c:创建一个新窗口
w:列出所有窗口
%:水平分割窗口
":竖直分割窗口
n:选择下一个窗口
p:选择上一个窗口
0~9:选择0~9对应的窗口
&:关闭当前窗口
#### 会话(session)操作
###### 启动
```
tmux
```
新建session，自动生成一个会话名为0的会话
```
tmux new -s <会话名>
```
可以在建立时显式说明会话的名字
###### 离开会话
有时候需要离开终端，进行其他的任务。需要离开该任务，但是又想该任务继续在后台执行，可以在 tmux 的任何一个窗格中输入如下命令：
```
tmux detach
```
也可以使用快捷键
```
ctrl+b d
```
###### 进入会话
```
tmux attach -t <会话名>
```
也可以使用tmux a -t <会话名>
###### 关闭会话
```
tmux kill-session -t <会话名>
```
###### 支持鼠标滚动
1.通过tmux界面输入(对于其他tmux不起作用)
进入tmux界面，按ctrl+B后，再按冒号:，进入命令行
输入
```
set -g mouse on
```
2.通过配置文件
在用户目录的.tmux.conf下，添加
```
set -g mouse on
```
