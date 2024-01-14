#include "hash_map.h"

int main(void) {
    // 创建hashmap
    int capacity = 3;
    double load_factor = 0.70;
    HashMap *map = create_hashmap(&capacity, &load_factor);
    // 表判空
    printf("%s\n", is_empty(map) ? "表为空" : "表不空");
    // 存值
    put(map, "name", "tom");
    put(map, "age", "20");
    put(map, "gender", "male");
    put(map, "gender", "male1");
    // 取值
    printf("%s\n", get(map, "name"));
    printf("%s\n", get(map, "gender1"));
    // 表判空
    printf("%s\n", is_empty(map) ? "表为空" : "表不空");
    // 判断表中是否包含key
    printf("%s\n", contains(map, "age") ? "存在" : "不存在");
    // 删值
    map_remove(map, "age");
    // 判断表中是否包含key
    printf("%s\n", contains(map, "age") ? "存在" : "不存在");







    // 销毁
    destroy_hashmap(map);
    return 0;
}

// 创建HashMap（容量和负载因子填NULL则使用默认值）
HashMap* create_hashmap(const void* capacity_p, const void* load_factor_p) {
    // 1. 创建hashmap
    HashMap *map = calloc (1, sizeof(HashMap));
    if (map == NULL) {
        puts("error：create_hashmap()内分配内存失败");
        return NULL;
    }
    //2. 初始化Bucket动态数组
    int capacity = capacity_p == NULL ? DEFAULT_CAPACITY : *(int*)capacity_p;
    Bucket **buckets = calloc(capacity, sizeof(Bucket));
    if (map == NULL) {
        puts("error：create_hashmap()内分配内存失败");
        free(map);
        return NULL;
    }
    map->buckets = buckets;
    // 3. 初始化hashmap的其他属性
    map->capacity = capacity;
    double load_factor = load_factor_p == NULL ? DEFAULT_LOAD_FACTOR : *(double*)load_factor_p;
    map->load_factor = load_factor;
    map->hash_seed = time(NULL);
    return map;
}
// 销毁HashMap
void destroy_hashmap(HashMap *map) {
    if (map == NULL) {
        puts("error：destroy_hashmap()的参数map为NULL");
        exit(-1);
    }
    // 1. 销毁链表结点
    for (int i = 0; i < map->capacity; i++) {
        Bucket *cur_bucket = map->buckets[i];
        if (cur_bucket != NULL) {
            MapNode *cur = cur_bucket->head;
            while(cur != NULL) {
                MapNode *temp = cur->next;
                free(cur);
                cur = temp;
            }
            // 2. 销毁桶
            free(cur_bucket);
        }
    }
    // 3. 销毁map
    free(map);
}
// ---------------- 基本操作 ----------------
// 存入键值对
V put(HashMap *map, K key, V val) {
    if (map == NULL) {
        puts("error：put()的参数map为NULL");
        exit(-1);
    }
    // 1. 计算key的hash值以及桶的位置idx
    uint32_t hash_code = hash(key, strlen(key), map->hash_seed);
    int idx = hash_code % map->capacity;
    // 2. 判断idx位置的桶是否存在
    if (map->buckets[idx] != NULL) {
        // 2-1. idx位置的桶已存在，则判断idx桶中是否存在key值
        MapNode *cur = map->buckets[idx]->head;
        while (cur != NULL) {
            if (strcmp(cur->key, key) == 0) {
                // 2-1-1. 若idx桶中已存在key值则更新value值，并返回旧value值
                V old_val = cur->value;
                cur->value = val;
                return old_val;
            }
            cur = cur->next;
        }
    }
    // 3. 判断是否需要扩容
    if (is_need_resize(map)) {
        // 3-1. 若需扩容，则扩容，并重新计算key的hash值和桶位置idx
        resize(map);
        hash_code = hash(key, strlen(key), map->hash_seed);
        idx = hash_code % map->capacity;
    }
    // 4. 重新判断idx位置的桶是否存在（在‘2.’虽然判断了一次，但有可能新的idx位置桶还未创建过
    if (map->buckets[idx] == NULL) {
        // 4-1. idx位置的桶不存在，则在idx位置创建桶，并在桶中存入hash值
        Bucket *bucket = calloc(1, sizeof(Bucket));
        if (bucket == NULL) {
            puts("error：put()内分配内存失败");
            exit(-1);
        }
        bucket->hash_code = hash_code;
        map->buckets[idx] = bucket;
    }
    // 5. 在桶中插入这键值对（用头插 O(1)）
    MapNode *new_node = calloc(1, sizeof(MapNode));
    if (new_node == NULL) {
        puts("error：put()内分配内存失败");
        exit(-1);
    }
    new_node->key = key;
    new_node->value = val;
    new_node->next = map->buckets[idx]->head;
    map->buckets[idx]->head = new_node;
    // 6. 更新size 
    map->size++;
    return NULL;
}
// 查询键值对
V get(const HashMap *map, K key) {
    if (map == NULL) {
        puts("error：get()的参数map为NULL");
        exit(-1);
    }
    // 1. 计算key的hash值应存放的桶的位置idx
    int idx = hash(key, strlen(key), map->hash_seed) % map->capacity;
    // 2. 在idx位置的桶中搜索对应key值
    if (map->buckets[idx] != NULL) { // 先判断桶是否为空
        MapNode *cur = map->buckets[idx]->head;
        while(cur != NULL) {
            if (strcmp(cur->key, key) == 0) {
                return cur->value;
            }
            cur = cur->next;
        }
    }
    return NULL;
}
// 删除键值对
bool map_remove(HashMap *map, K key) {
    if (map == NULL) {
        puts("error：map_remove()的参数map为NULL");
        exit(-1);
    }
     // 1. 计算key的hash值应存放的桶的位置idx
    int idx = hash(key, strlen(key), map->hash_seed) % map->capacity;
    // 2. 在idx位置的桶中搜索对应key值
    if (map->buckets[idx] != NULL) { // 先判断桶是否为空
        MapNode *pre = NULL;
        MapNode *cur = map->buckets[idx]->head;
        while(cur != NULL) {
            if (strcmp(cur->key, key) == 0) {
                // 3. 删除结点
                if (pre == NULL) { // 删除的是第一个结点
                    map->buckets[idx]->head = cur->next;
                }else {
                    pre->next = cur->next;
                }
                // 4. 释放内存
                free(cur);
                return true;
            }
            pre = cur;
            cur = cur->next;
        }
    }
    return false;
}
// 键key在表中是否有对应的值
bool contains(const HashMap *map, K key) {
    if (map == NULL) {
        puts("error：contains()的参数map为NULL");
        exit(-1);
    }
    return get(map, key) != NULL;
}
// 判断表是否为空
bool is_empty(const HashMap *map) {
    if (map == NULL) {
        puts("error：is_empty()的参数map为NULL");
        exit(-1);
    }
    return map->size == 0;
}

// ---------------- 其他操作 ----------------
// 是否需要扩容
static bool is_need_resize(const HashMap *map) {
    double load_factor = map->size*1.0 / map->capacity;
    return load_factor > map->load_factor;
}
// TODO：扩容
static void resize(HashMap *map) {

}

// murmur_hash2 哈希函数
static uint32_t hash(const void* key, int len, uint32_t seed) {
    const uint32_t m = 0x5bd1e995;
    const int r = 24;
    uint32_t h = seed ^ len;
    const unsigned char* data = (const unsigned char*)key;

    while (len >= 4) {
        uint32_t k = *(uint32_t*)data;
        k *= m;
        k ^= k >> r;
        k *= m;
        h *= m;
        h ^= k;
        data += 4;
        len -= 4;
    }

    switch (len) {
    case 3: h ^= data[2] << 16;
    case 2: h ^= data[1] << 8;
    case 1: h ^= data[0];
        h *= m;
    };

    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;

    return h;
}