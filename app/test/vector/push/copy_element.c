test(vector_push_copy_element) {

  given("a vector")
    struct vector vector = vector_init(i32);
    vector_create(&vector);
  
  when("the copy elements flag is enabled")
    vector_flag_enable(&vector, Vector_Flag__Copy_Elements);

  calling("vector_push()")
    i32 element = 3;
    vector_push(&vector, &element);
    vector_push(&vector, &element);
    vector_push(&vector, &element);

  must("copy the element by value")
    verify(vector.length == 3);
    verify(vector_get(&vector, 0) != &element);
    verify(vector_get(&vector, 1) != &element);
    verify(vector_get(&vector, 2) != &element);
    verify(*(i32*) vector_get(&vector, 0) == element);
    verify(*(i32*) vector_get(&vector, 1) == element);
    verify(*(i32*) vector_get(&vector, 2) == element);
    verify(vector_get(&vector, 3) == NULL);

  success()
    vector_destroy(&vector);
}
