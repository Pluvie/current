test(map_has_false_if_key_not_present) {

  given("a map")
    struct map map = map_init(i32, i32);
    map_create(&map);

  when("a key is not present")
    i32 key = 3;

  calling("map_has() on that key");
    bool result = map_has(&map, &key);

  must("return true")
    verify(result == false);

  success()
    map_free(&map);
}
