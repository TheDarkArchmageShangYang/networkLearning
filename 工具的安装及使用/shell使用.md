# shell使用
推荐使用zsh
终端复用工具推荐tmux
## zsh
#### 安装
```
sudo apt install zsh
sh -c "$(wget -O- https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"
```
.oh-my-zsh和.zshrc文件都在/home/fzchen下

vscode切换默认终端

![image](https://github.com/TheDarkArchmageShangYang/networkLearning/assets/149142839/71faa6f6-2aa6-459b-b5fc-171c9c8233fa)
#### 安装插件
所有插件都应该下载到/home/fzchen/.oh-my-zsh/custom/plugins
```
# zsh-suggestions:根据历史命令和当前输入，自动提示命令参数和选项
git clone https://github.com/zsh-users/zsh-autosuggestions ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-autosuggestions

# zsh-syntax-highlighting:根据语法高亮显示命令和文件路径等内容
git clone https://github.com/zsh-users/zsh-syntax-highlighting.git ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-syntax-highlighting

# autojump:根据使用频率，自动跳转到最常用的目录
git clone https://github.com/wting/autojump.git
cd autojump
./install.py

# fzf:快速模糊搜索历史命令和文件路径
git clone --depth 1 https://github.com/junegunn/fzf.git ~/.fzf
```
修改.zshrc文件
```
# extract和z是oh-my-zsh自带的
plugins=(git 
         zsh-autosuggestions 
         zsh-syntax-highlighting
         autojump
         extract
         z)

source $ZSH/oh-my-zsh.sh
```
使.zshrc文件生效
```
source .zshrc
```
#### 使用
###### 修改主题
下载主题，在.zshrc中设置ZSH_THEME=""
###### 自动补全命令
只要输入过某命令，后续会按照输入来匹配最符合的历史指令，按右箭头补全
###### 快捷跳转
z插件会记录在命令行跳转过的每个路径及跳转次数,不需要输入完整的路径就可以跳转
```
#跳转/home/fzchen/worknew/tengine-install/sbin
z wo
```
###### 快捷跳转
输入d可以显示访问过的路径，再输入数字可以直接跳转

![image](https://github.com/TheDarkArchmageShangYang/networkLearning/assets/149142839/b4fa15e6-5375-4aed-a4cc-974ce27dd126)

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
