test(map_init_correct_key_size) {

  given("a map")
    struct map map = map_init(i32, i32);
  
  calling("map_init()")

  must("create the map with the correct key size")
    verify(map.key_size == sizeof(i32));

  success()
    map_destroy(&map);
}
