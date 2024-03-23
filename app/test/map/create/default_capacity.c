test(map_create_default_capacity) {

  given("a map")
    Map map = map_init(i32, i32);
  
  when("no capacity is provided")
  
  calling("map_create()")
    map_create(&map);
  
  must("allocate the map with the default capacity")
    verify(map.capacity == MAP_DEFAULT_CAPACITY);

  success()
    map_destroy(&map);
}
