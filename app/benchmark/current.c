#include "../../src/current.h"
#include "../../src/current.c"

void insert(void);
void capacity(void);
void lookup(void);
void insert_rand(void);

static inline u32 pseudorand (
    u64 a
)
{
    a = (a ^ 61) ^ (a >> 16);
    a = a + (a << 3);
    a = a ^ (a >> 4);
    a = a * 0x27d4eb2d;
    a = a ^ (a >> 15);
    return a;
}

int main (
    int argc,
    char** argv
)
{
  //insert();
  //capacity();
  //lookup();
  insert_rand();
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

  fprintf(stderr, "done: %i - %li / %li / %li\n", result ? *result : 0, arena.total_capacity, arena.number_of_allocs, arena.number_of_regions);
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

  int key = 999;
  result = map_get(&map, &key);
  fprintf(stderr, "done: %i\n", result ? *result : 0);
}
