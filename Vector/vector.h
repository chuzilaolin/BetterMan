#ifndef VECTOR_H
#define VECTOR_H

// 数组默认容量设置为10
#define DEFAULT_CAPACITY 10 
// 数组长度低于 HIGHT_SIZE 时，每次按照原长度翻倍扩容
// 数组长度高于 HIGHT_SIZE 时，扩充原容量的1/2
#define HIGHT_SIZE 1000 

// 定义存储的数据类型
typedef char* Element;

// 定义Vector的数据结构
typedef struct vector_s {
    Element *data; // 用于存储数据的动态数组的指针
    int size; // 数组长度
    int capacity; // 容量
} Vector;

// 创建一个空的Vector
Vector* vector_create();

// 销毁释放Vector
void vector_destroy(Vector *v);

// 向动态数组的末尾新增一个元素
void vector_push_back(Vector *v, Element val);

// 向数组的前面插入一个元素
void vector_push_front(Vector *v, Element val);

// 将元素val添加到索引为idx的位置，idx后面的元素依次后移
void vector_insert(Vector *v, int idx, Element val);

// 给Vector的动态数组扩容
static void vector_rsize(Vector *v);

// 将数组的元素从指定下标位置依次向后挪动
static void move_data(Vector *v, int idx);




#endif
