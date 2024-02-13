test(map_set_copy_key) {

  given("a map(i32, i32)")
    struct map map_ptr = map(i32, i32);
    map_alloc(&map_ptr);

  when("the `Map_Flag__Copy_Keys` is enabled")
    map_flag_enable(&map_ptr, Map_Flag__Copy_Keys);

  when("the provided key is not yet present in the map")

  calling("map_set()");
    i32 key = 3;
    i32 value = 7;
    map_set(&map_ptr, &key, &value);
  
  must("make a copy of the provided key")
    u64 capped_hash = map_ptr.hash(&key, map_ptr.key_size) % map_ptr.capacity;
    struct map_entry* entry = map_ptr.buckets[capped_hash];

    verify(entry->key != &key);
    verify(entry->value == &value);
    verify(*((i32*) entry->key) == key);
    verify(*((i32*) entry->value) == value);

  success()
    map_free(&map_ptr);
}
