#include <stdio.h>
#include "hash_map.h"

int main(void) {
    // 创建hashmap
    int capacity = 1;
    double load_factor = 0.70;
    HashMap *map = create_hashmap(&capacity, &load_factor);
    // 表判空
    printf("%s\n", is_empty(map) ? "表为空" : "表不空");
    // 存值
    put(map, "name", "tom");
    put(map, "age", "20");
    put(map, "gender", "male");
    put(map, "gender1", "male");
    put(map, "gender2", "male");
    // 取值
    printf("%s, %s\n", get(map, "name"), get(map, "gender1"));
    // 表判空
    printf("%s\n", is_empty(map) ? "表为空" : "表不空");
    // 判断表中是否包含key
    printf("%s\n", contains(map, "age") ? "存在" : "不存在");
    // 删值
    map_remove(map, "name");
    map_remove(map, "age");
    map_remove(map, "gender");
    // 判断表中是否包含key
    printf("%s\n", contains(map, "age") ? "存在" : "不存在");
    // 表判空
    printf("%s\n", is_empty(map) ? "表为空" : "表不空");



    // 销毁
    destroy_hashmap(map);
    return 0;
}
