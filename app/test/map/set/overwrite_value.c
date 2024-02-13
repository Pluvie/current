test(map_set_overwrite_value) {

  given("a map")
    struct map map = map_init(i32, i32);
    map_alloc(&map);

  when("a key is already present in the map")
    i32 key = 3;
    i32 value = 7;
    map_set(&map, &key, &value);

    u64 capped_hash = map.hash(&key, map.key_size) % map.capacity;
    struct map_entry* entry = map.buckets[capped_hash];
    verify(entry->value == &value);
    verify(*((i32*)entry->value) == value);

  calling("map_set() on the same key with another value");
    value = 9;
    map_set(&map, &key, &value);
  
  must("overwrite the previous value")
    verify(entry->key == &key);
    verify(entry->value == &value);
    verify(*((i32*) entry->key) == key);
    verify(*((i32*) entry->value) != 7);
    verify(*((i32*) entry->value) == value);

  success()
    map_free(&map);
}
