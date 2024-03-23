test(vector_init_provided_flags) {

  given("a vector")
    Vector vector = vector_init(i32);
  
  when("flags are provided")
    vector_flag_enable(&vector, VECTOR_FLAG__COPY_ELEMENTS);
  
  calling("vector_init()")
  
  must("create the vector with the provided flags")
    verify(vector.flags & VECTOR_FLAG__COPY_ELEMENTS);

  success()
    vector_destroy(&vector);
}
