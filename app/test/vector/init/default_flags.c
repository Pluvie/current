test(vector_init_default_flags) {

  given("a vector")
    Vector vector = vector_init(i32);
  
  when("no flags are provided")
  
  calling("vector_init()")
  
  must("create the vector with the default flags")
    verify(vector.flags == VECTOR_FLAG__NONE);

  success()
    vector_destroy(&vector);
}
