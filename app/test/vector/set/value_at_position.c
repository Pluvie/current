test(vector_set_value_at_position) {

  given("a vector")
    struct vector vector = vector_init(i32);
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
    verify(vector.elements[0].value == &element);
    verify(vector.elements[1].value == &other_element);
    verify(result == true);

  success()
    vector_destroy(&vector);
}
