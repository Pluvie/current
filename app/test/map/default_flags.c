test(map_default_flags) {

  given("a map(i32, i32)")
    struct map map_ptr = map(i32, i32);
  
  when("no flags are provided")
  
  must("create the map with the default flags")
    verify(map_ptr.flags == Map_Flag__None);

  success()
    map_free(&map_ptr);
}
