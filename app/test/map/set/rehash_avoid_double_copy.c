test(map_set_rehash_avoid_double_copy) {

  given("a map")
    Map map = map_init(i32, i32);
    map_create(&map);

  when("the `MAP_FLAG__COPY_KEYS` is enabled")
    map_flag_enable(&map, MAP_FLAG__COPY_KEYS);

  when("the `MAP_FLAG__COPY_VALUES` is enabled")
    map_flag_enable(&map, MAP_FLAG__COPY_VALUES);

  when("a map rehash is triggered")
    i32 numbers[] = { 0, 1, 2, 3, 4, 5 };
    for (u32 i = 0; i < countof(numbers) - 1; i++)
      map_set(&map, &numbers[i], &numbers[i]);

    /* Saves all keys and values addresses before the rehash. */
    void* key_addresses[5] = { 0 };
    void* value_addresses[5] = { 0 };
    MapEntry* entry = NULL;
    for (u32 i = 0; i < countof(numbers) - 1; i++) {
      entry = map_entry_get(&map, &numbers[i]);
      key_addresses[i] = entry->key;
      value_addresses[i] = entry->value;
    }

    /* Triggers the rehash. */
    verify(map.capacity == 8);
    map_set(&map, &numbers[5], &numbers[5]);

  must("avoid double copying the keys and values")
    /* Verify that the rehash occured and that it preserved the original keys and
     * values addresses. */
    verify(map.capacity == 16);
    for (u32 i = 0; i < countof(numbers) - 1; i++) {
      entry = map_entry_get(&map, &numbers[i]);
      verify(entry->key == key_addresses[i]);
      verify(entry->value == value_addresses[i]);
    }

  success()
    map_destroy(&map);
}
