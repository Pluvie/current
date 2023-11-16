void test_vector_arena (
    void
)
{
  struct arena* scratch = arena_init(vector_estimated_bytesize(int, 100));
  vector(int) vector_int = vector_new_cap_arena(
    int, vector_estimated_capacity(100), scratch);

  for (int i = 0; i < 100; i ++)
    vector_push(vector_int, i);

  vector_each(vector_int, int, iter)
    assert(vector_int[iter.index] == iter.element);

  arena_destroy(scratch);
}
