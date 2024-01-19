void test_arena ()
{
  struct arena* test_arena = arena_init(ARENA_REGION_MIN_CAPACITY);
  arena_malloc(test_arena, 1024);
  byte* data = arena_malloc(test_arena, 1024 * 8);
  data = arena_realloc(test_arena, data, 1024 * 12);
  arena_destroy(test_arena);
}

void test_i32 ()
{
  struct map* test_map = map(i32, i32);
  i32 key = 3;
  i32 value = 7;
  map_set(test_map, &key, &value);
  map_pretty_print(test_map);
  map_get(test_map, &key);
  map_free(test_map);
}

void test_u64 ()
{
  struct map* test_map = map(u64, char*);
  u64 keys[] = { 0, 1, 2, 3, 4, 5 };
  char* values[] = { "a", "b", "c", "d", "e", "f" };
  for (u32 i = 0; i < countof(keys) - 1; i++)
    map_set(test_map, &(keys[i]), &(values[i]));
  map_pretty_print(test_map);
  map_del(test_map, &(keys[2]));
  map_del(test_map, &(keys[4]));
  fprintf(stderr, "\n\n");
  map_pretty_print(test_map);
  map_free(test_map);
}

int main (
    int argc,
    char** argv
)
{
  //fprintf(stderr, "ciao!\n");
  //test_i32();
  //test_u64();
  test_arena();
  return 0;
}
