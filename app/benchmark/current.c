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
  i32 result = 0;
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
  result = *(i32*) map_get(&map, &key);
  fprintf(stderr, "done: %i\n", result);
}
