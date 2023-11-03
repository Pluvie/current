void test_scalar_int (
    void
)
{
  map(int, int) scalar_int = map_new(int, int);
  for (int i = 0; i < 100; i++)
    map_set(scalar_int, &i, i);
  for (int i = 0; i < 100; i++)
    assert(map_get(scalar_int, &i) == i);
  //map_print(scalar, int, __map_identity_print, int, __map_identity_print);
  map_free(scalar_int);

  map(int64, int64) scalar_int64 = map_new(int64, int64);
  for (uint64 i = 1UL << 44; i < 100 + (1UL << 44); i++)
    map_set(scalar_int64, &i, i);
  for (uint64 i = 1UL << 44; i < 100 + (1UL << 44); i++)
    assert(map_get(scalar_int64, &i) == i);
  //map_print(scalar, int, __map_identity_print, int, __map_identity_print);
  map_free(scalar_int64);
}
