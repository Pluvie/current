test(map_alloc_default_capacity) {

  given("a map")
    struct map map = map_init(i32, i32);
  
  when("no capacity is provided")
  
  calling("map_alloc()")
    map_alloc(&map);
  
  must("allocate the map with the default capacity")
    verify(map.capacity == MAP_DEFAULT_CAPACITY);

  success()
    map_free(&map);
}
