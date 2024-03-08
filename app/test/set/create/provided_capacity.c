test(set_create_provided_capacity) {

  given("a set")
    struct set set = set_init(i32);
  
  when("the provided capacity is greater or equal than the minimum")
  when("the provided capacity is a power of 2")
    set.capacity = 1 << 4;
  
  calling("set_create()")
    set_create(&set);
  
  must("allocate the set with the provided capacity")
    verify(set.capacity == 16);

  success()
    set_destroy(&set);
}
