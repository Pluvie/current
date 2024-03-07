test(vector_get_null_if_over_length) {

  given("a vector")
    struct vector vector = vector_init(i32);
    vector_create(&vector);

  when("the vector has some elements")
    i32 element = 3;
    vector_push(&vector, &element);
    vector_push(&vector, &element);
  
  calling("vector_get()")
    void* value = vector_get(&vector, 2);

  must("return NULL if the provided position is greater or equal than the length of "\
       "the vector")
    verify(vector.length == 2);
    verify(value == NULL);

  success()
    vector_destroy(&vector);
}
