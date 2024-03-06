test(map_create_provided_capacity_no_pow_2_high_load) {

  given("a map")
    struct map map = map_init(i32, i32);
  
  when("the provided capacity is greater or equal than the minimum")
  when("the provided capacity is not a power of 2")
  when("the provided capacity is already over the load factor")
    map.capacity = 29;
  
  calling("map_create()")
    map_create(&map);
  
  must("allocate the map with double the provided capacity raised to the next "\
       "power of 2")
    verify(map.capacity == 64);

  success()
    map_free(&map);
}
