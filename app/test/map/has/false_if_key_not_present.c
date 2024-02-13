test(map_has_false_if_key_not_present) {

  given("a map(i32, i32)")
    struct map map_ptr = map(i32, i32);
    map_alloc(&map_ptr);

  when("a key is not present")
    i32 key = 3;

  calling("map_has() on that key");
    bool result = map_has(&map_ptr, &key);

  must("return true")
    verify(result == false);

  success()
    map_free(&map_ptr);
}
