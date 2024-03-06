test(map_set_copy_key) {

  given("a map")
    struct map map = map_init(i32, i32);
    map_create(&map);

  when("the `Map_Flag__Copy_Keys` is enabled")
    map_flag_enable(&map, Map_Flag__Copy_Keys);

  when("the provided key is not yet present in the map")

  calling("map_set()");
    i32 key = 3;
    i32 value = 7;
    map_set(&map, &key, &value);
  
  must("make a copy of the provided key")
    u64 hash = map_hash(&key, map.key_size);
    u64 capped_hash = map_capped_hash(hash, map.capacity);
    struct map_entry* entry = map.buckets[capped_hash];

    verify(entry->key != &key);
    verify(entry->value == &value);
    verify(*((i32*) entry->key) == key);
    verify(*((i32*) entry->value) == value);

  success()
    map_destroy(&map);
}
