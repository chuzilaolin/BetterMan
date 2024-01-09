#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

// 创建一个空的Vector
Vector* vector_create() {
    Vector *v = (Vector*)calloc(1, sizeof(Vector));
    if (v == NULL) {
        puts("error：创建一个空的Vector时分配内存失败");
        exit(-1);
    }
    // 给Vector的成员变量赋值
    v->data = c1alloc(DEFAULT_CAPACITY, sizeof(Element));
    if (v->data == NULL) {
        puts("error：创建一个空的Vector时分配内存失败");
        free(v); // 因为下面一行是直接退出程序，free(v)意义不大，但最好还是写上，养成习惯
        exit(-1);
    }
    v->capacity = DEFAULT_CAPACITY;
    return v;
}

// 销毁释放Vector
void vector_destroy(Vector *v) {
    if (v == NULL) { // Vector不能是NULL
        return;
    }
    free(v->data);
    free(v);
}

// 向动态数组的末尾新增一个元素
void vector_push_back(Vector *v, Element val) {
    if (v == NULL) { // Vector不能是NULL
        return;
    }
    if (v->size == v->capacity) { // 容量不足，扩容
        vector_rsize(v);
    }
    v->data[v->size] = val;
    v->size++;
}

// 向数组的前面插入一个元素
void vector_push_front(Vector *v, Element val) {
    if (v == NULL) { // Vector不能是NULL
        return;
    }
    if (v->size == v->capacity) { // 容量不足，扩容
        vector_rsize(v);
    }
    // 从下标0向后移动并在0下标位置赋值
    move_data(v, 0);
    v->data[0] = val;
    v->size++;
}

// 将元素val添加到索引为idx的位置，idx后面的元素依次后移
void vector_insert(Vector *v, int idx, Element val) {
    if (v == NULL || idx < 0 || idx > v->size) { // Vector不能是NULL，索引位置不能为负且不能越界
        return;
    }
    if (v->size == v->capacity) { // 容量不足，扩容
        vector_rsize(v);
    }
    move_data(v, idx);
    v->data[idx] = val;
    v->size++;
}

// 给Vector的动态数组扩容
static void vector_rsize(Vector *v) {
    int old_capacity = v->capacity;
    // tips：算术运算‘+’的优先级比位运算符‘>>’高，要用括号括起来
    int new_capacity = v->size < HIGHT_SIZE ? old_capacity << 1 : old_capacity + (old_capacity >> 1);
    // tips：用realloc扩容，不能用calloc和malloc，数据会丢失！
    // tips：扩容的是v->data，而不是v
    Element *temp = realloc(v->data, new_capacity * sizeof(Element));
    if (temp == NULL) {
        puts("error：给Vector的动态数组扩容失败");
        exit(-1);
    }
    // tips：v->data扩容部分附上初值
    memset(v->data + v->size, 0, (v->capacity - v->size) * sizeof(Element));
    v->data = temp;
    v->capacity = new_capacity;
}

// 将数组的元素从指定下标 idx 位置依次向后挪动1个位置
static void move_data(Vector *v, int idx) {
    for (int i = v->size - 1; i >= idx; i--) {
        v->data[i+1] = v->data[i];
    }
    v->data[idx] = 0;
}

