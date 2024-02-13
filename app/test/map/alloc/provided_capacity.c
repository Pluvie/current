test(map_alloc_provided_capacity) {

  given("a map")
    struct map map = map_init(i32, i32);
  
  when("the provided capacity is greater or equal than the minimum")
  when("the provided capacity is a power of 2")
    map.capacity = 1 << 4;
  
  calling("map_alloc()")
    map_alloc(&map);
  
  must("allocate the map with the provided capacity")
    verify(map.capacity == 16);

  success()
    map_free(&map);
}
