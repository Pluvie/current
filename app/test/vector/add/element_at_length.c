test(vector_add_element_at_length) {

  given("a vector")
    struct vector vector = vector_init(i32);
    vector_create(&vector);
  
  calling("vector_add()")
    i32 element = 3;
    vector_add(&vector, &element);
    vector_add(&vector, &element);
    vector_add(&vector, &element);

  must("add the element at the position equal to the vector length")
    verify(vector.length == 3);
    verify(vector.elements[0].value == &element);
    verify(vector.elements[1].value == &element);
    verify(vector.elements[2].value == &element);
    verify(vector.elements[3].value == NULL);

  success()
    vector_destroy(&vector);
}
