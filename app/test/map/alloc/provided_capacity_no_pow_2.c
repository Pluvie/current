test(map_alloc_provided_capacity_no_pow_2) {

  given("a map(i32, i32)")
    struct map map_ptr = map(i32, i32);
  
  when("the provided capacity is greater or equal than the minimum")
  when("the provided capacity is not a power of 2")
    map_ptr.capacity = 29;
  
  calling("map_alloc()")
    map_alloc(&map_ptr);
  
  must("allocate the map with the provided capacity raised to the next power of 2")
    verify(map_ptr.capacity == 32);

  success()
    map_free(&map_ptr);
}
