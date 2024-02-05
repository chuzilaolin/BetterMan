#ifndef QUEUE_C
#define QUEUE_C

#include <stdio.h>                                                         
#include <stdlib.h>

// NULL检查                                                                
#define NULL_CHECK(arg, msg) {if(arg == NULL){fprintf(stderr, "error: %s is NULL\n", msg); exit(-1);}}

// 定义队列中的元素类型
typedef int E;

// 队列节点元素
typedef struct qNode_s {
    E data;
    struct qNode_s *next;
} qNode_t;

// 队列结构
typedef struct queue_s {
    qNode_t *front;
    qNode_t *rear;
    int size; // 元素个数
} queue_t;

// 创建空队列
queue_t* create_queue();
// 销毁队列并释放所有资源
int destroy_queue(queue_t *queue);
// ------------------ 基本操作 ------------------
// 入队
int enqueue(queue_t *queue, E element);
// 出队
E dequeue(queue_t *queue);
// 获取队首元素,但不出队
E peek(const queue_t *queue);
// 判断队列是否为空(-1出错,0不为空,1为空)
int isEmpty(const queue_t *queue);


#endif