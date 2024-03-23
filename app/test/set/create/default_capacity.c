test(set_create_default_capacity) {

  given("a set")
    Set set = set_init(i32);
  
  when("no capacity is provided")
  
  calling("set_create()")
    set_create(&set);
  
  must("allocate the set with the default capacity")
    verify(set.capacity == MAP_DEFAULT_CAPACITY);

  success()
    set_destroy(&set);
}
