test(vector_pop_reduce_length) {

  given("a vector")
    struct vector vector = vector_init(i32);
    vector_create(&vector);

  when("the vector has some elements")
    i32 element = 3;
    vector_push(&vector, &element);
    vector_push(&vector, &element);
  
  calling("vector_pop()")
    vector_pop(&vector);

  must("delete the last element and reduce the length of the vector")
    verify(vector.length == 1);
    verify(vector.elements[0].value == &element);
    verify(vector.elements[1].value == NULL);

  success()
    vector_destroy(&vector);
}