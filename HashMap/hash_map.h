#ifndef HASH_MAP_H
#define HASH_MAP_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
// 默认桶的个数(动态数组默认大小)
#define DEFAULT_CAPACITY 8
// 默认负载因子
#define DEFAULT_LOAD_FACTOR 0.75

typedef char* K;    
typedef char* V;    

// 定义hashmap的链表结点
typedef struct map_node {
    K key;  // 键
    V value;    // 值
    struct map_node *next; // 下一个结点
} MapNode;

// 定义hashmap的桶结点
typedef struct {
    MapNode *head; // 桶中链表的第一个节点
    uint32_t hash; // 桶中键值对hash值
} Bucket;

// 定义hashmap结构体
typedef struct {
    Bucket **buckets;  // 存键值对的桶（动态的Bucket指针数组）
    int size;   // map中键值对个数
    int capacity; // map的容量
    double load_factor; // map的负载因子
    uint32_t hash_seed; // hash函数的种子
} HashMap;

// 创建HashMap（容量和负载因子填NULL则使用默认值）
HashMap* create_hashmap(const void* capacity_p, const void* load_factor_p);
// 销毁HashMap
void destroy_hashmap(HashMap *map);
// ---------------- 基本操作 ----------------
// 存入键值对
V put(HashMap *map, K key, V val);
// 查询键值对
V get(const HashMap *map, K key);
// 删除键值对
bool map_remove(HashMap *map);
// 判断是否为空
bool is_empty(const HashMap *map);


// murmur_hash2 哈希函数
static uint32_t hash(const void* key, int len, uint32_t seed);

#endif