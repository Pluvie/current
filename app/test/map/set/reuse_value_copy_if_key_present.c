test(map_set_reuse_value_copy_if_key_present) {

  given("a map")
    Map map = map_init(i32, i32);
    map_create(&map);

  when("the `MAP_FLAG__COPY_VALUES` is enabled")
    map_flag_enable(&map, MAP_FLAG__COPY_VALUES);

  when("a key is already present in the map")
    i32 key = 3;
    i32 value = 7;
    map_set(&map, &key, &value);

    u64 hash = map_hash(&key, map.key_size);
    u64 capped_hash = map_capped_hash(hash, map.capacity);
    MapEntry* entry = map.entries + capped_hash;
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
    map_destroy(&map);
}
