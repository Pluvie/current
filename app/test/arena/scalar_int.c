void test_scalar_int_arena (
    struct arena* arena
)
{
  map_new(scalar_int, int, int,
    .arena = arena,
    .hash = __map_prebuilt_int32_hash,
    .compare = __map_prebuilt_int32_compare);

  int iterations = 100;
  for (int i = 0; i < iterations; i++)
    map_set(scalar_int, &i, i);
  for (int i = 0; i < iterations; i++)
    assert(map_get(scalar_int, &i) == i);
  //map_print(scalar_int, int, __map_prebuilt_int32_print, int, __map_prebuilt_int32_print);

  //map(int64, int64) scalar_int64 = map_new_cap_arena(int64, int64, 100, arena);
  //map_config(scalar_int64, __map_prebuilt_int64_hash, __map_prebuilt_int64_compare);
  //for (uint64 i = 1UL << 44; i < 100 + (1UL << 44); i++)
  //  map_set(scalar_int64, &i, i);
  //for (uint64 i = 1UL << 44; i < 100 + (1UL << 44); i++)
  //  assert(map_get(scalar_int64, &i) == i);
  ////map_print(scalar_int64, int64, __map_prebuilt_int64_print, int64, __map_prebuilt_int64_print);
}
