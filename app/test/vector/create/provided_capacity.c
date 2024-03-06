test(vector_create_provided_capacity) {

  given("a vector")
    struct vector vector = vector_init(i32);
  
  when("it is provided a capacity greater than the minimum")
    vector.capacity = 1 << 4;
  
  calling("vector_create()")
    vector_create(&vector);
  
  must("allocate the vector with the provided capacity")
    verify(vector.capacity == 16);

  success()
    vector_destroy(&vector);
}
