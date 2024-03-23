test(map_init_default_flags) {

  given("a map")
    Map map = map_init(i32, i32);
  
  when("no flags are provided")
  
  calling("map_init()")
  
  must("create the map with the default flags")
    verify(map.flags == MAP_FLAG__NONE);

  success()
    map_destroy(&map);
}
