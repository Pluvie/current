test(vector_create_provided_capacity_inferior_to_minimum) {

  given("a vector")
    struct vector vector = vector_init(i32);
  
  when("the provided capacity is inferior to the minimum")
    vector.capacity = 4;
  
  calling("vector_create()")
    vector_create(&vector);
  
  must("allocate the vector with the default capacity")
    verify(vector.capacity == VECTOR_DEFAULT_CAPACITY);

  success()
    vector_destroy(&vector);
}
