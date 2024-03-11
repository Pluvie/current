test(vector_set_overwrite_copy) {

  given("a vector")
    struct vector vector = vector_init(i32);
    vector_create(&vector);

  when("the copy elements flag is enabled")
    vector_flag_enable(&vector, Vector_Flag__Copy_Elements);
  when("the vector has some elements")
    i32 element = 3;
    vector_push(&vector, &element);
    vector_push(&vector, &element);
    verify(vector_get(&vector, 1) != &element);
  
  calling("vector_set()")
    element = 7;
    bool result = vector_set(&vector, 1, &element);

  must("overwrite the copy of the element")
    verify(vector.length == 2);
    verify(result == true);
    verify(*(i32*) vector_get(&vector, 0) == 3);
    verify(*(i32*) vector_get(&vector, 1) == 7);

  success()
    vector_destroy(&vector);
}
