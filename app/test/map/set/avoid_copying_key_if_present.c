test(map_set_avoid_copying_key_if_present) {

  given("a map")
    struct map map = map_init(i32, i32);
    map_alloc(&map);

  when("the `Map_Flag__Copy_Keys` is enabled")
    map_flag_enable(&map, Map_Flag__Copy_Keys);

  when("a key is already present in the map")
    i32 key = 3;
    i32 value = 7;
    map_set(&map, &key, &value);

    u64 capped_hash = map.hash(&key, map.key_size) % map.capacity;
    struct map_entry* entry = map.buckets[capped_hash];
    void* key_copy_addr = entry->key;
    verify(entry->key != &key);
    verify(*((i32*)entry->key) == key);

  calling("map_set() on the same key");
    value = 9;
    map_set(&map, &key, &value);
  
  must("avoid making another copy of the key")
    verify(entry->key == key_copy_addr);
    verify(entry->value == &value);
    verify(*((i32*) entry->key) == key);
    verify(*((i32*) entry->value) != 7);
    verify(*((i32*) entry->value) == value);

  success()
    map_free(&map);
}