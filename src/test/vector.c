void test_vector (
    void
)
{
  vector(int) vector_int = vector_new(int);
  for (int i = 0; i < 100; i ++)
    vector_push(vector_int, i);

  vector_each(vector_int, int, iter)
    assert(vector_int[iter.index] == iter.element);

  vector_free(vector_int);
}
