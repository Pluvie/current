/**
 * From: [https://github.com/Mashpoe/c-hashmap] */

#include "./mashpoe/map.h"
#include "./mashpoe/map.c"

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

void insert (
    void
)
{
  uintptr_t result = 0;
  hashmap* map = hashmap_create();

  for (int i = 0; i < 300000; i++) {
    for (int j = 0; j < 1000; j++) {
      hashmap_set(map, (char*) &j, sizeof(j), i);
    }
  }

  int key = 999;
  hashmap_get(map, (char*) &key, sizeof(key), &result);
  fprintf(stderr, "done: %i\n", (int) result);
}

void capacity (
    void
)
{
  uintptr_t result = 0;
  hashmap* map = hashmap_create();

  for (int i = 0; i < 3000000; i++) {
    for (int j = 0; j < 100; j++) {
      hashmap_set(map, (char*) &i, sizeof(i), j);
    }
  }

  int key = 0;
  hashmap_get(map, (char*) &key, sizeof(key), &result);
  fprintf(stderr, "done: %i\n", (int) result);
}
