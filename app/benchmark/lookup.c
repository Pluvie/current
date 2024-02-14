int main (
    int argc,
    char** argv
)
{
  u64 result = 0;
  struct map map = map_init(i32, i32);
  map_alloc(&map);

  for (u64 a = 0; a < 10; a++) {
    for (u64 i = 0; i < 100000; i++) {
      for (u64 j = 0; j < 100; j++) {
        map_set(&map, &j, &i);
        result = *(i32*) map_get(&map, &j);
      }
    }
  }

  fprintf(stderr, "done: %li\n", result);
  return 0;
}
