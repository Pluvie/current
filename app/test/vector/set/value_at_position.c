test(vector_set_value_at_position) {

  given("a vector")
    Vector vector = vector_init(i32);
    vector_create(&vector);

  when("the vector has some elements")
    i32 element = 3;
    vector_push(&vector, &element);
    vector_push(&vector, &element);
  
  calling("vector_set()")
    i32 other_element = 7;
    bool result = vector_set(&vector, 1, &other_element);

  must("set the value at the provided position")
    verify(vector.length == 2);
    verify(vector_get(&vector, 0) == &element);
    verify(vector_get(&vector, 1) == &other_element);
    verify(result == true);

  success()
    vector_destroy(&vector);
}
