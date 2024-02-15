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
  struct map map = map_init(i32, i32);
  map.capacity = 1024;
  map_flag_enable(&map, Map_Flag__Copy_Keys);
  map_flag_enable(&map, Map_Flag__Copy_Values);
  map_alloc(&map);

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
  arena_alloc(&arena, 8388608 * sizeof(i32) * 2);
  struct map map = map_init(i32, i32);
  map.capacity = 3000000;
  map.arena = &arena;
  map_flag_enable(&map, Map_Flag__Copy_Keys);
  map_flag_enable(&map, Map_Flag__Copy_Values);
  map_alloc(&map);

  for (i32 i = 0; i < 3000000; i++) {
    for (i32 j = 0; j < 100; j++) {
      map_set(&map, &i, &j);
    }
  }

  int key = 0;
  result = map_get(&map, &key);
  fprintf(stderr, "done: %i - %li / %li / %li\n", result ? *result : 0, arena.total_capacity, arena.number_of_allocs, arena.number_of_regions);
}
