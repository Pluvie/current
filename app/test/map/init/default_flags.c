test(map_default_flags) {

  given("a map")
    struct map map = map_init(i32, i32);
  
  when("no flags are provided")
  
  calling("map_init()")
  
  must("create the map with the default flags")
    verify(map.flags == Map_Flag__None);

  success()
    map_free(&map);
}
