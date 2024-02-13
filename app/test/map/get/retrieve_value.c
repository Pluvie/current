test(map_get_retrieve_value) {

  given("a map(i32, i32)")
    struct map map_ptr = map(i32, i32);
    map_alloc(&map_ptr);

  when("a key is present")
    i32 key = 3;
    i32 value = 7;
    map_set(&map_ptr, &key, &value);

  calling("map_get()");
    void* retrieved_value = map_get(&map_ptr, &key);

  must("retrieve the correct value")
    verify(retrieved_value == &value);
    verify(*(i32*) retrieved_value == value);

  success()
    map_free(&map_ptr);
}
