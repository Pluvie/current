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
  u64 key = 1UL << 44;
  char* value = "abc";
  map_set(test_map, &key, &value);
  map_pretty_print(test_map);
  map_get(test_map, &key);
  map_free(test_map);
}

int main (
    int argc,
    char** argv
)
{
  fprintf(stderr, "ciao!\n");
  test_i32();
  test_u64();
  return 0;
}
