test(map_create_provided_capacity_no_pow_2) {

  given("a map")
    Map map = map_init(i32, i32);
  
  when("the provided capacity is greater or equal than the minimum")
  when("the provided capacity is not a power of 2")
    map.capacity = 17;
  
  calling("map_create()")
    map_create(&map);
  
  must("allocate the map with the provided capacity raised to the next power of 2")
    verify(map.capacity == 32);

  success()
    map_destroy(&map);
}
