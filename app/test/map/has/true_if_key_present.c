test(map_has_true_if_key_present) {

  given("a map(i32, i32)")
    struct map map_ptr = map(i32, i32);
    map_alloc(&map_ptr);

  when("a key is present")
    i32 key = 3;
    i32 value = 7;
    map_set(&map_ptr, &key, &value);

  calling("map_has() on that key");
    bool result = map_has(&map_ptr, &key);

  must("return true")
    verify(result == true);

  success()
    map_free(&map_ptr);
}
