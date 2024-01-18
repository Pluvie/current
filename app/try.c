int main (
    int argc,
    char** argv
)
{
  fprintf(stderr, "ciao!\n");
  struct map* test_map = map(i32, i32);
  i32 key = 3;
  i32 value = 7;
  map_set(test_map, &key, &value);
  map_pretty_print(test_map);
  map_get(test_map, &key);
  map_free(test_map);
  return 0;
}
