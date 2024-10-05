# python画图
python推荐使用matplotlib画图

[参考链接](https://blog.csdn.net/weixin_41558411/article/details/115582012?ops_request_misc=&request_id=&biz_id=102&utm_term=python%E7%94%BB%E5%9B%BE&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-0-115582012.142^v96^pc_search_result_base8&spm=1018.2226.3001.4187)

#### 常用API
###### 导入模块
```
import matplotlib as plt
```
###### 防止中文乱码
```
import seaborn as sns
sns.set_style({'font.sans-serif': ['simhei', 'Arial']})
```
#### 折线图
```
plt.plot(x,y)
```
###### 设置横纵坐标标签
```
plt.xlabel("xxx")
plt.ylabel("xxx")
```
提示：当标签为中文时，设置颜色等属性时，可能会出问题
###### 设置标题
```
plt.title("xxx")
```
###### 添加图例
```
plt.legend(['xxx','xxx','xxx'])
```
###### 绘制多个子图
```
plt.subplot(x,y,n)
```
x表示行数,y表示列数,n表示第几张图
```
import matplotlib.pyplot as plt
import seaborn as sns
matplotlib.rcParams['lines.linewidth'] = 4
matplotlib.rcParams['axes.titlesize'] = 'xx-large'
sns.set_style({'font.sans-serif': ['simhei', 'Arial']})

fig = plt.figure(figsize=(10, 10), dpi=100)
ax1 = plt.subplot(221)
#设置X轴、Y轴的刻度范围
#ax1.set_ylim(0, 1)
#ax1.set_xlim(0, 1)
#设置每个刻度对应的标签
#plt.xticks([1, 2, 3, 4], labels=["a", "b", "c", "d"])


plt.plot([1, 2, 3, 4], [4, 5, 7, 8], color="r", linestyle="--")
#在ax1中添加一条线
plt.plot([1, 2, 3, 4], [6, 7, 8, 9], color='#17becf', linestyle="-")
plt.title(label='first')  # 设置字体大小与格式

ax2 = plt.subplot(2, 2, 2)
plt.plot([1, 2, 3, 5], [4, 5, 7, 8], color="y", linestyle="-")
plt.title('tow')


ax3 = plt.subplot(223)
plt.plot([1, 2, 3, 4], [4, 5, 7, 8], marker='*', color="g", linestyle="-.")
plt.title('three', y=-0.15)  
ax4 = plt.subplot(224)
plt.plot([1, 2, 3, 4], [4, 5, 7, 8], color="b", linestyle=":")
plt.title('four', y=-0.15)  
fig.suptitle("四种样式的线条", y=0.05)  # 设置大标题及位置
plt.show()
```
结果:
![image](https://github.com/TheDarkArchmageShangYang/networkLearning/assets/149142839/d0ecfb9b-8a58-4620-970c-d2f3e519ee62)



#### 柱状图

修改柱状图的形状

###### 边框颜色

```py
plt.bar(x, values, width, edgecolor='black')
```

###### 内部填充颜色

无色为none

```py
plt.bar(x, values, width, edgecolor='red') 
```

###### 边框和内部颜色

```python
plt.bar(x, values, width, color='red') 
```

###### 内部填充线和颜色

```py
plt.bar(x, values, width, hatch='/') 
```

常见hatch图案样式:

- '/':斜线
- '\\\\':反斜线('\\\\'表示单斜杠,'\\\\\\\\'表示双斜杠)
- '|':竖线
- '-':水平线
- '+':横竖线
- 'x':斜线和反斜线

###### 颜色列表

![image-20241006044713471](assets/python%E7%94%BB%E5%9B%BE/image-20241006044713471.png)

###### 图层

zorder默认值为1,越高显示在越上层,越低显示在越下层

```py
plt.bar(x, values, width, zorder=2) 
```

