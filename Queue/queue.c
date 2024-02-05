#include "queue.h"

// 创建空队列                                                              
queue_t* create_queue() {
    queue_t *queue = (queue_t*)calloc(1, sizeof(queue_t));
    NULL_CHECK(queue, "create_queue:queue");
    return queue;
}
// 销毁队列并释放所有资源
int destroy_queue(queue_t *queue) {
    NULL_CHECK(queue, "destroy_queue:queue");
    // 销毁结点
    qNode_t *cur = queue->front;
    while(cur) {
        qNode_t *temp = cur->next;
        free(cur);
        cur = temp;
    }
    
    // 销毁队列
    free(queue);
    return 0; 
}
// ------------------ 基本操作 ------------------
// 入队(从链表的尾插)
int enqueue(queue_t *queue, E element) {
    NULL_CHECK(queue, "enqueue:queue");

    // 创建新结点
    qNode_t *new_node = (qNode_t*)calloc(1, sizeof(qNode_t));
    NULL_CHECK(new_node, "enqueue:newNode");
    new_node->data = element;

    // 入队
    if(isEmpty(queue)) {
        queue->front = new_node;  
    }
    else {
        queue->rear->next = new_node;
    }

    // 更新尾指针
    queue->rear = new_node;

    // 更新size
    queue->size++;
    return 0;
}
// 出队(从链表的头取)
E dequeue(queue_t *queue) {
    NULL_CHECK(queue, "queue");

    // 判断是否已为空
    if(isEmpty(queue)) {
        fprintf(stderr, "error: dequeue:queue isEmpty\n");
        exit(-1);
    }

    // 出队
    qNode_t *cur = queue->front;
    E e = cur->data;
    queue->front = cur->next;

    // 释放内存
    free(cur);
    
    // 更新尾指针
    if(queue->front == NULL) {
        queue->rear = NULL; // 队列已空,则更新尾指针 
    }

    // 更新size
    queue->size--;

    return e;
}
// 获取队首元素,但不出队
E peek(const queue_t *queue) {
    NULL_CHECK(queue, "queue");
    // 判断是否已为空
    if(isEmpty(queue)) {
        fprintf(stderr, "error: dequeue:queue isEmpty\n");
        exit(-1);
    }
    return queue->front->data;
}
// 判断队列是否为空(0不为空,1为空)
int isEmpty(const queue_t *queue) {
    NULL_CHECK(queue, "queue");
    if (queue->size > 0) {
        return 0;
    }
    return 1;
}