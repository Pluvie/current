void benchmark_insert (
    void
)
{
  printf("Insert\n");
  map(char*, int) benchmark = map_new(char*, int);
  map_set(benchmark, "test", 7);
  map_print(benchmark, char*, int, "%s", "%i");
  map_free(benchmark);
}
