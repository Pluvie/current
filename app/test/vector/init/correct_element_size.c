test(vector_init_correct_element_size) {

  given("a vector")
    Vector vector = vector_init(i32);
  
  calling("vector_init()")

  must("create the vector with the correct element size")
    verify(vector.element_size == sizeof(i32));

  success()
    vector_destroy(&vector);
}
