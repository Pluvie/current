void test_scalar_int_arena (
    void
)
{
  arena* scratch = arena_init(
    map_estimated_bytesize(int, int, 100) +
    map_estimated_bytesize(int64, int64, 100));

  map(int, int) scalar_int = map_new_cap_arena(
    int, int, map_estimated_capacity(100), scratch);
  map_config(scalar_int, __map_prebuilt_int32_hash, __map_prebuilt_int32_compare);
  for (int i = 0; i < 100; i++)
    map_set(scalar_int, &i, i);
  for (int i = 0; i < 100; i++)
    assert(map_get(scalar_int, &i) == i);
  //map_print(scalar_int, int, __map_prebuilt_int64_print, int, __map_prebuilt_int64_print);

  map(int64, int64) scalar_int64 = map_new_cap_arena(
    int64, int64, map_estimated_capacity(100), scratch);
  map_config(scalar_int64, __map_prebuilt_int64_hash, __map_prebuilt_int64_compare);
  for (uint64 i = 1UL << 44; i < 100 + (1UL << 44); i++)
    map_set(scalar_int64, &i, i);
  for (uint64 i = 1UL << 44; i < 100 + (1UL << 44); i++)
    assert(map_get(scalar_int64, &i) == i);
  //map_print(scalar_int64, int64, __map_prebuilt_int64_print, int64, __map_prebuilt_int64_print);

  arena_destroy(scratch);
}
