test(map_del_do_nothing) {

  given("a map(i32, i32)")
    struct map map_ptr = map(i32, i32);
    map_alloc(&map_ptr);

  when("a key is not present")
    i32 key = 3;
    u64 map_length = map_ptr.length;

  calling("map_del()");
    void* deleted_value = map_del(&map_ptr, &key);

  must("keep the map unchanged")
    verify(deleted_value == NULL);
    verify(map_ptr.length == map_length);

  success()
    map_free(&map_ptr);
}
