test(vector_get_value_at_position) {

  given("a vector")
    Vector vector = vector_init(i32);
    vector_create(&vector);

  when("the vector has some elements")
    i32 element = 3;
    vector_push(&vector, &element);
    vector_push(&vector, &element);
  
  calling("vector_get()")
    void* value = vector_get(&vector, 1);

  must("return the element value at the provided position")
    verify(vector.length == 2);
    verify(value == &element);

  success()
    vector_destroy(&vector);
}
