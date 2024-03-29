test(map_create_provided_capacity) {

  given("a map")
    Map map = map_init(i32, i32);
  
  when("the provided capacity is greater or equal than the minimum")
  when("the provided capacity is a power of 2")
    map.capacity = 1 << 4;
  
  calling("map_create()")
    map_create(&map);
  
  must("allocate the map with the provided capacity")
    verify(map.capacity == 16);

  success()
    map_destroy(&map);
}
