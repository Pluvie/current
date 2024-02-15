/**
 * From: [https://github.com/Mashpoe/c-hashmap] */

#include "./mashpoe/map.h"
#include "./mashpoe/map.c"

void insert(void);

int main (
    int argc,
    char** argv
)
{
  insert();
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
