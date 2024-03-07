#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../src/current/preamble.h"
#include "../../src/current/arena.h"
#include "../../src/current/arena.c"
#include "./current-chained/map.c"

/**
 * Old Current implementation using separate chaining. */

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
  fprintf(stderr, "done: %i\n", result ? *result : 0);
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
  fprintf(stderr, "done: %i - %li / %li / %li\n", result ? *result : 0, arena.total_capacity, arena.number_of_allocs, arena.number_of_regions);
}
