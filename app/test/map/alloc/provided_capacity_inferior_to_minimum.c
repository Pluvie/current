test(map_alloc_provided_capacity_inferior_to_minimum) {

  given("a map")
    struct map map = map_init(i32, i32);
  
  when("the provided capacity is inferior to the minimum")
    map.capacity = 4;
  
  calling("map_alloc()")
    map_alloc(&map);
  
  must("allocate the map with the default capacity")
    verify(map.capacity == MAP_DEFAULT_CAPACITY);

  success()
    map_free(&map);
}
