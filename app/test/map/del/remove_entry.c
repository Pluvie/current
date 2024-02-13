test(map_del_remove_entry) {

  given("a map(i32, i32)")
    struct map map_ptr = map(i32, i32);
    map_alloc(&map_ptr);

  when("a key is present")
    i32 key = 3;
    i32 value = 7;
    map_set(&map_ptr, &key, &value);

  calling("map_del()");
    void* deleted_value = map_del(&map_ptr, &key);

  must("remove the entry with that key")
    struct map_entry* entry = map_get_entry(&map_ptr, &key);
    verify(entry == NULL);
    verify(deleted_value == &value);
    verify(*(i32*) deleted_value == value);

  success()
    map_free(&map_ptr);
}
