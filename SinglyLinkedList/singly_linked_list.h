#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef int Element;

// 定义单向链表的结点
typedef struct node_s {
    Element data;
    struct node_s *next;
} Node;

// 定义单向链表
typedef struct {
    size_t size; // 元素个数
    Node *head;  // 指向头节点
    Node *tail;  // 指向尾节点
} SinglyLinkedList;

// 创建一个单向链表
SinglyLinkedList* create__list();
// 销毁一个单向链表
void destroy_list(SinglyLinkedList *list);

// -------------- 增加数据操作 ---------------
// 从头部插入结点
bool add_before_head(SinglyLinkedList *list, Element val);
// 从尾部插入结点
bool add_behind_tail(SinglyLinkedList *list, Element val);
// 从指定索引位置插入结点
bool add_by_index(SinglyLinkedList *list, int idx, Element val);

// -------------- 查询数据操作 ---------------
// 根据下标查询数据（类似数组，第一个结点下标为0）
Node* get_by_idx(const SinglyLinkedList *list, int idx);
// 根据数据值查找数据
Node* get_by_data(const SinglyLinkedList *list, int idx);

// -------------- 删除数据操作 ---------------
// 从头部删除一个结点
bool delete_from_head(SinglyLinkedList *list);
// 从尾部删除一个结点
bool delete_from_tail(SinglyLinkedList *list);
// 删除某个值的结点（只删除匹配到的第一个）
bool delete_by_data(SinglyLinkedList *list, Element val);

// -------------- 其他操作 ---------------
// 打印链表
void print_list(const SinglyLinkedList *list);

#endif