#include "hash_map.h"

int main(void) {

    return 0;
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