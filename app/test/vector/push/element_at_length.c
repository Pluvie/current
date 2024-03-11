test(vector_push_element_at_length) {

  given("a vector")
    struct vector vector = vector_init(i32);
    vector_create(&vector);
  
  calling("vector_push()")
    i32 element = 3;
    vector_push(&vector, &element);
    vector_push(&vector, &element);
    vector_push(&vector, &element);

  must("add the element at the position equal to the vector length")
    verify(vector.length == 3);
    verify(vector_get(&vector, 0) == &element);
    verify(vector_get(&vector, 1) == &element);
    verify(vector_get(&vector, 2) == &element);
    verify(vector_get(&vector, 3) == NULL);

  success()
    vector_destroy(&vector);
}
