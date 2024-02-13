test(map_set_reuse_value_copy_if_key_present) {

  given("a map")
    struct map map = map_init(i32, i32);
    map_alloc(&map);

  when("the `Map_Flag__Copy_Values` is enabled")
    map_flag_enable(&map, Map_Flag__Copy_Values);

  when("a key is already present in the map")
    i32 key = 3;
    i32 value = 7;
    map_set(&map, &key, &value);

    u64 capped_hash = map.hash(&key, map.key_size) % map.capacity;
    struct map_entry* entry = map.buckets[capped_hash];
    void* value_copy_addr = entry->value;
    verify(entry->key == &key);
    verify(entry->value != &value);
    verify(*((i32*) entry->key) == key);
    verify(*((i32*) entry->value) == value);

  calling("map_set() on the same key");
    value = 9;
    map_set(&map, &key, &value);
  
  must("avoid making another copy of the value and instead reuse the already "\
       "allocated memory")
    verify(entry->key == &key);
    verify(entry->value == value_copy_addr);
    verify(*((i32*) entry->key) == key);
    verify(*((i32*) entry->value) != 7);
    verify(*((i32*) entry->value) == value);

  success()
    map_free(&map);
}
