test(map_provided_flags) {

  given("a map(i32, i32)")
    struct map map_ptr = map(i32, i32);
  
  when("flags are provided")
    map_flag_enable(&map_ptr, Map_Flag__Copy_Keys);
    map_flag_enable(&map_ptr, Map_Flag__Copy_Values);
  
  must("create the map with the provided flags")
    verify(map_ptr.flags & Map_Flag__Copy_Keys);
    verify(map_ptr.flags & Map_Flag__Copy_Values);

  success()
    map_free(&map_ptr);
}
