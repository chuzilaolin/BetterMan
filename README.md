# 一些有趣的小工具小项目

### 一、命令行日历查看程序
**功能说明：** 
- 输入一个年份数字就可以查看这一年的全年日历；
- 如果查询年是本年，当天的日期会标红。

**运行截图：**
<img width="948" alt="image" src="https://github.com/chuzilaolin/FunBOX/assets/82101835/a2e6c90b-00a6-4320-aa21-4d7db6d3c25f">

### 二、用C语言实现动态数组Vector
**实现原理：**

定义一个结构体类型，在结构体中用指针指向一个在堆空间开辟的一块内存。
![image](https://github.com/chuzilaolin/FunBOX/assets/82101835/dc5e3430-5805-4d09-920f-c9a7ca6733fd)

### 三、用C语言实现哈希表HashMap
**功能说明：**
- 自定义初始容量和负载因子；
- 当键值对的个数与容量比值超过负载因子时，自动扩容；
- 借鉴Java8的HashMap部分扩容逻辑，定义了单独的桶结构体用于记录hash值，以及2倍扩容，减少了hash运算和移位的开销。

**实现原理：**
采用动态数组加链表的方式实现（之后撸完红黑树，增加动态数组+链表+红黑树的版本）。

![hashmap-array linkedlist drawio](https://github.com/chuzilaolin/FunBOX/assets/82101835/14fa9df7-9469-497b-8859-c73a6e8de5d8)
