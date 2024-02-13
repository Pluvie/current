test(map_set_rehash_avoid_double_copy) {

  given("a map(i32, i32)")
    struct map map_ptr = map(i32, i32);
    map_alloc(&map_ptr);

  when("the `Map_Flag__Copy_Keys` is enabled")
    map_flag_enable(&map_ptr, Map_Flag__Copy_Keys);

  when("the `Map_Flag__Copy_Values` is enabled")
    map_flag_enable(&map_ptr, Map_Flag__Copy_Values);

  when("a map rehash is triggered")
    i32 numbers[] = { 0, 1, 2, 3, 4, 5 };
    for (u32 i = 0; i < countof(numbers) - 1; i++)
      map_set(&map_ptr, &numbers[i], &numbers[i]);

    /* Saves all keys and values addresses before the rehash. */
    void* key_addresses[5] = { 0 };
    void* value_addresses[5] = { 0 };
    struct map_entry* entry = NULL;
    for (u32 i = 0; i < countof(numbers) - 1; i++) {
      entry = map_get_entry(&map_ptr, &numbers[i]);
      key_addresses[i] = entry->key;
      value_addresses[i] = entry->value;
    }

    /* Triggers the rehash. */
    verify(map_ptr.capacity == 8);
    map_set(&map_ptr, &numbers[5], &numbers[5]);

  must("avoid double copying the keys and values")
    /* Verify that the rehash occured and that it preserved the original keys and
     * values addresses. */
    verify(map_ptr.capacity == 16);
    for (u32 i = 0; i < countof(numbers) - 1; i++) {
      entry = map_get_entry(&map_ptr, &numbers[i]);
      verify(entry->key == key_addresses[i]);
      verify(entry->value == value_addresses[i]);
    }

  success()
    map_free(&map_ptr);
}
