test(map_has_true_if_key_present) {

  given("a map")
    struct map map = map_init(i32, i32);
    map_create(&map);

  when("a key is present")
    i32 key = 3;
    i32 value = 7;
    map_set(&map, &key, &value);

  calling("map_has() on that key");
    bool result = map_has(&map, &key);

  must("return true")
    verify(result == true);

  success()
    map_destroy(&map);
}
