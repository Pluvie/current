test(map_get_return_null) {

  given("a map(i32, i32)")
    struct map map_ptr = map(i32, i32);
    map_alloc(&map_ptr);

  when("a key is not present")
    i32 key = 3;

  calling("map_get()");
    void* retrieved_value = map_get(&map_ptr, &key);

  must("return NULL")
    verify(retrieved_value == NULL);

  success()
    map_free(&map_ptr);
}
