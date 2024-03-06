test(vector_init_default_flags) {

  given("a vector")
    struct vector vector = vector_init(i32);
  
  when("no flags are provided")
  
  calling("vector_init()")
  
  must("create the vector with the default flags")
    verify(vector.flags == Map_Flag__None);

  success()
    vector_destroy(&vector);
}
