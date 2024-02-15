/**
 * From: [https://github.com/tidwall/hashmap.c.git] */

#include "./tidwall/hashmap.h"
#include "./tidwall/hashmap.c"

void insert(void);
void capacity(void);

int main (
    int argc,
    char** argv
)
{
  //insert();
  capacity();
  return 0;
}

uint64_t int_hash(const void *item, uint64_t seed0, uint64_t seed1) {
  return hashmap_sip(item, sizeof(int), seed0, seed1);
}

int int_compare(const void *a, const void *b, void *udata) {
  return memcmp(a, b, sizeof(int));
}

void insert (
    void
)
{
  int* result = 0;
  struct hashmap *map = hashmap_new(
    sizeof(int), 0, 0, 0, 
    int_hash, int_compare, NULL, NULL);

  for (int i = 0; i < 300000; i++) {
    for (int j = 0; j < 1000; j++) {
      hashmap_set(map, &j);
    }
  }

  int key = 999;
  result = (int*) hashmap_get(map, &key);
  fprintf(stderr, "done: %i\n", *result);
}

void capacity (
    void
)
{
  int* result = 0;
  struct hashmap *map = hashmap_new(
    sizeof(int), 0, 0, 0, 
    int_hash, int_compare, NULL, NULL);

  for (int i = 0; i < 3000000; i++) {
    for (int j = 0; j < 100; j++) {
      hashmap_set(map, &i);
    }
  }

  int key = 0;
  result = (int*) hashmap_get(map, &key);
  fprintf(stderr, "done: %i\n", *result);
}
