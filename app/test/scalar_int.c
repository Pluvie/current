void test_scalar_int (
    void
)
{
  map_new(scalar_int, int, int,
    .hash = __map_prebuilt_int32_hash,
    .compare = __map_prebuilt_int32_compare);
  for (int i = 0; i < 6; i++)
    map_set(scalar_int, &i, i);
  //for (int i = 0; i < 100; i++)
  //  assert(map_get(scalar_int, &i) == i);
  map_print(scalar_int, int, __map_prebuilt_int32_print, int, __map_prebuilt_int32_print);
  map_free(scalar_int);

  //map_new(scalar_int64, int64, int64,
  //  .hash = __map_prebuilt_int64_hash,
  //  .compare = __map_prebuilt_int64_compare);
  //for (uint64 i = 1UL << 44; i < 100 + (1UL << 44); i++)
  //  map_set(scalar_int64, &i, i);
  //for (uint64 i = 1UL << 44; i < 100 + (1UL << 44); i++)
  //  assert(map_get(scalar_int64, &i) == i);
  ////map_print(scalar_int64, int64, __map_prebuilt_int64_print, int64, __map_prebuilt_int64_print);
  //map_free(scalar_int64);
}
