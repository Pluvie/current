#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../src/current/prelude.h"
#include "../../src/current/arena.h"
#include "../../src/current/arena.c"
#include "./current-chained/map.c"

/**
 * Old Current implementation using separate chaining. */

void insert(void);
void capacity(void);
void lookup(void);
void insert_rand(void);

static inline i32 pseudorand (
    i32 n
)
{
  return 18000 * (n & 65535) + (n >> 16);
}

static inline void report (
    i32* result,
    struct arena* arena,
    struct map* map
)
{
  fprintf(stderr, "done: %i - arena: %li / %li / %li - map: %li\n",
    result ? *result : 0,
    arena->total_capacity, arena->number_of_allocs, arena->number_of_regions,
    map->capacity);
}

int main (
    int argc,
    char** argv
)
{
  if (argc < 2) {
    fprintf(stderr, "no benchmark\n");
    return 0;
  }

  if (strcmp(argv[1], "insert") == 0)
    insert();
  else if (strcmp(argv[1], "capacity") == 0)
    capacity();
  else if (strcmp(argv[1], "lookup") == 0)
    lookup();
  else if (strcmp(argv[1], "insert_rand") == 0)
    insert_rand();
  else
    fprintf(stderr, "invalid benchmark\n");

  return 0;
}

void insert (
    void
)
{
  i32* result = 0;
  struct arena arena = arena_init();
  arena_create(&arena, 0);
  struct map map = map_init(i32, i32);
  map.capacity = 1000;
  map.arena = &arena;
  map_flag_enable(&map, Map_Flag__Copy_Keys);
  map_flag_enable(&map, Map_Flag__Copy_Values);
  map_create(&map);

  for (i32 i = 0; i < 300000; i++) {
    for (i32 j = 0; j < 1000; j++) {
      map_set(&map, &j, &i);
    }
  }

  int key = 999;
  result = map_get(&map, &key);
  report(result, &arena, &map);
}

void capacity (
    void
)
{
  i32* result = 0;
  struct arena arena = arena_init();
  arena_create(&arena, 0);
  struct map map = map_init(i32, i32);
  map.capacity = 3000000;
  map.arena = &arena;
  map_flag_enable(&map, Map_Flag__Copy_Keys);
  map_flag_enable(&map, Map_Flag__Copy_Values);
  map_create(&map);

  for (i32 i = 0; i < 3000000; i++) {
    for (i32 j = 0; j < 100; j++) {
      map_set(&map, &i, &j);
    }
  }

  int key = 0;
  result = map_get(&map, &key);
  report(result, &arena, &map);
}

void lookup (
    void
)
{
  i32* result = 0;
  struct arena arena = arena_init();
  arena_create(&arena, 0);
  struct map map = map_init(i32, i32);
  map.capacity = 100;
  map.arena = &arena;
  map_flag_enable(&map, Map_Flag__Copy_Keys);
  map_flag_enable(&map, Map_Flag__Copy_Values);
  map_create(&map);

  for (i32 i = 0; i < 100; i++) {
    map_set(&map, &i, &i);
  }

  for (i32 i = 0; i < 3000000; i++) {
    for (i32 j = 0; j < 100; j++) {
      result = map_get(&map, &j);
    }
  }

  report(result, &arena, &map);
}

void insert_rand (
    void
)
{
  i32* result = 0;
  struct arena arena = arena_init();
  arena_create(&arena, 0);
  struct map map = map_init(i32, i32);
  map.capacity = 1000;
  map.arena = &arena;
  map_flag_enable(&map, Map_Flag__Copy_Keys);
  map_flag_enable(&map, Map_Flag__Copy_Values);
  map_create(&map);

  i32 k, v;
  for (i32 i = 0; i < 300000; i++) {
    for (i32 j = 0; j < 1000; j++) {
      k = pseudorand(i);
      v = pseudorand(j);
      map_set(&map, &k, &v);
    }
  }

  int key = 126000; // value should be: 17982000
  result = map_get(&map, &key);
  report(result, &arena, &map);
}
