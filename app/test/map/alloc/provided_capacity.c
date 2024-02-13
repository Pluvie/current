test(map_alloc_provided_capacity) {

  given("a map(i32, i32)")
    struct map map_ptr = map(i32, i32);
  
  when("the provided capacity is greater or equal than the minimum")
  when("the provided capacity is a power of 2")
    map_ptr.capacity = 1 << 4;
  
  calling("map_alloc()")
    map_alloc(&map_ptr);
  
  must("allocate the map with the provided capacity")
    verify(map_ptr.capacity == 16);

  success()
    map_free(&map_ptr);
}
