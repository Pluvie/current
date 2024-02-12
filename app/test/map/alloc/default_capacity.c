test(map_alloc_default_capacity) {

  given("a map(i32, i32)")
    struct map map_ptr = map(i32, i32);
  
  when("no capacity is provided")
  
  calling("map_alloc()")
    map_alloc(&map_ptr);
  
  must("allocate the map with the default capacity")
    verify(map_ptr.capacity == MAP_DEFAULT_CAPACITY);

  success()
    map_free(&map_ptr);
}
