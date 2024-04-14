# C/C++练手项目集
> C++不是世界上最好的语言（【狗头保命🐶】），但是我很喜欢它。

**项目介绍**：这个项目记录了我用c++实现的一些小玩意儿。编程虽然是我的爱好，但是我开悟得晚，技术能力也才刚刚起步，所以不敢说这个项目对各位“码友”有什么太大的帮助，只是一起交流学习罢了🀀🀂🀁🀃🀅。

### 一、目录（难度不分先后）
- [x] [命令行日历小程序 (c)](https://github.com/chuzilaolin/FunBOX/tree/main/Commandlinecalendar)
- [x] [动态数组Vector (c)](https://github.com/chuzilaolin/FunBOX/tree/main/Vector)
- [x] [哈希表HashMap (c)](https://github.com/chuzilaolin/FunBOX/tree/main/HashMap)
- [ ] 基于链表的队列Queue
- [ ] 基于循环数组的队列Queue
- [ ] 基于链表的栈Stack
- [ ] 基于动态数组的栈Stack
- [ ] 表达式求值小程序
- [ ] 双向链表
- [ ] 二叉搜索树
- [ ] 红黑树
- [ ] B树
- [ ] B+树
- [ ] 跳表
- [x] [封装线程池 (c++)](https://github.com/chuzilaolin/FreeTime/tree/main/cpp/ThreadPool)
- [x] [封装string类（c++）](https://blog.csdn.net/weixin_44398687/article/details/136725095)
- [x] [C++ Primer上的简单词频统计（c++）](https://blog.csdn.net/weixin_44398687/article/details/136793289)  

### 二、项目说明

#### 1. 命令行日历小程序

**功能说明：** 

- 输入一个年份数字就可以查看这一年的全年日历；
- 如果查询年是本年，当天的日期会标红。

**运行截图：**
<img width="948" alt="image" src="https://github.com/chuzilaolin/FunBOX/assets/82101835/a2e6c90b-00a6-4320-aa21-4d7db6d3c25f">

#### 2. 动态数组Vector
**实现原理：**

定义一个结构体类型，在结构体中用指针指向一个在堆空间开辟的一块内存。
![image](https://github.com/chuzilaolin/FunBOX/assets/82101835/dc5e3430-5805-4d09-920f-c9a7ca6733fd)

#### 3. 哈希表HashMap
**功能说明：**
- 自定义初始容量和负载因子；
- 当键值对的个数与容量比值超过负载因子时，自动扩容；
- 借鉴Java8的HashMap部分扩容逻辑，定义了单独的桶结构体用于记录hash值，以及2倍扩容，减少了hash运算和移位的开销。

**实现原理：**
采用动态数组加链表的方式实现（之后撸完红黑树，增加动态数组+链表+红黑树的版本）。

![hashmap-array linkedlist drawio](https://github.com/chuzilaolin/FunBOX/assets/82101835/14fa9df7-9469-497b-8859-c73a6e8de5d8)

#### 4. 基于链表的队列Queue
**功能说明：**
- 创建队列
- 销毁队列
- 入队
- 出队
- 查看队头 
- 判空

**实现原理：**
基于单向链表实现，从尾部插入，从头部取出。

#### 5. 基于循环数组的队列Queue



#### 6. 基于链表的栈Stack



#### 7. 基于动态数组的栈Stack

**功能说明：**

**实现原理：**
基于动态数组实现栈；比起用链表方式，随机访问效率高且不需要额外空间存储指针，但重分配内存那一刻可能涉及巨大的内存开销，拖慢整体栈的效率。

#### 8. 表达式求值小程序
**功能说明：**

- 在命令行输入一串运算表达式，计算得到结果；

#### 9. 双向链表

**功能说明：**


#### 10. 二叉搜索树

**功能说明：**
