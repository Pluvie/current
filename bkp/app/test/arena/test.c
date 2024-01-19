void test_arena_memory (
    void
)
{
  describe("[Arena] (memory)");

  struct arena* scratch = arena_init(ARENA_REGION_MIN_SIZE);

  byte* it = arena_malloc(scratch, 1);
  *it = 7;
  for(int i = 0; i < 10; i++) {
    byte* i = arena_malloc(scratch, 1000);
    i[99] = 7;
  }
  it = arena_malloc(scratch, 5000);
  it = arena_malloc(scratch, 40);
  it = arena_malloc(scratch, 40);
  it = arena_malloc(scratch, 100);

  arena_destroy(scratch);
  success();
}
