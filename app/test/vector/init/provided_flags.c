test(vector_init_provided_flags) {

  given("a vector")
    struct vector vector = vector_init(i32);
  
  when("flags are provided")
    vector_flag_enable(&vector, Vector_Flag__Copy_Elements);
  
  calling("vector_init()")
  
  must("create the vector with the provided flags")
    verify(vector.flags & Vector_Flag__Copy_Elements);

  success()
    vector_destroy(&vector);
}
