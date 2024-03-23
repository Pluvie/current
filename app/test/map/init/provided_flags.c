test(map_init_provided_flags) {

  given("a map")
    Map map = map_init(i32, i32);
  
  when("flags are provided")
    map_flag_enable(&map, MAP_FLAG__COPY_KEYS);
    map_flag_enable(&map, MAP_FLAG__COPY_VALUES);
  
  calling("map_init()")
  
  must("create the map with the provided flags")
    verify(map.flags & MAP_FLAG__COPY_KEYS);
    verify(map.flags & MAP_FLAG__COPY_VALUES);

  success()
    map_destroy(&map);
}
