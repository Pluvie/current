test(map_init_correct_value_size) {

  given("a map")
    Map map = map_init(i32, i32);
  
  calling("map_init()")
  
  must("create the map with the correct value size")
    verify(map.value_size == sizeof(i32));

  success()
    map_destroy(&map);
}
