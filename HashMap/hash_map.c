#include "hash_map.h"

int main(void) {
    // 创建hashmap
    int capacity = 10;
    double load_factor = 0.70;
    HashMap *map = create_hashmap(&capacity, &load_factor);


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
    // 1. 销毁链表结点

    // 2. 销毁桶

    // 3. 销毁map

}
// ---------------- 基本操作 ----------------
// 存入键值对
V put(HashMap *map, K key, V val) {

    return map->buckets[0]->head->value;
}
// 查询键值对
V get(const HashMap *map, K key) {

    return map->buckets[0]->head->value;
}
// 删除键值对
bool map_remove(HashMap *map) {
    
    return false;
}
// 判断是否为空
bool is_empty(const HashMap *map) {

    return false;
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