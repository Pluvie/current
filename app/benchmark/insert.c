int main (
    int argc,
    char** argv
)
{
  u64 result = 0;
  struct map map = map_init(i32, i32);
  map.capacity = 300000;
  map_flag_enable(&map, Map_Flag__Copy_Keys);
  map_flag_enable(&map, Map_Flag__Copy_Values);
  map_alloc(&map);

  for (u64 i = 0; i < 300000; i++) {
    for (u64 j = 0; j < 1000; j++) {
      map_set(&map, &i, &j);
    }
    result = i;
  }

  fprintf(stderr, "done: %li\n", result);
  return 0;
}
