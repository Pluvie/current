test(map_provided_flags) {

  given("a map")
    struct map map = map_init(i32, i32);
  
  when("flags are provided")
    map_flag_enable(&map, Map_Flag__Copy_Keys);
    map_flag_enable(&map, Map_Flag__Copy_Values);
  
  calling("map_init()")
  
  must("create the map with the provided flags")
    verify(map.flags & Map_Flag__Copy_Keys);
    verify(map.flags & Map_Flag__Copy_Values);

  success()
    map_free(&map);
}
