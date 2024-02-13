test(map_alloc_provided_capacity_inferior_to_minimum) {

  given("a map(i32, i32)")
    struct map map_ptr = map(i32, i32);
  
  when("the provided capacity is inferior to the minimum")
    map_ptr.capacity = 4;
  
  calling("map_alloc()")
    map_alloc(&map_ptr);
  
  must("allocate the map with the default capacity")
    verify(map_ptr.capacity == MAP_DEFAULT_CAPACITY);

  success()
    map_free(&map_ptr);
}
