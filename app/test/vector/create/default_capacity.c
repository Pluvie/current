test(vector_create_default_capacity) {

  given("a vector")
    struct vector vector = vector_init(i32);
  
  when("no capacity is provided")
  
  calling("vector_create()")
    vector_create(&vector);
    vector_pretty_print(&vector);
  
  must("allocate the vector with the default capacity")
    verify(vector.capacity == MAP_DEFAULT_CAPACITY);

  success()
    vector_destroy(&vector);
}
