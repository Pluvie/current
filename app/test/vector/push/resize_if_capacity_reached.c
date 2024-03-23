test(vector_push_resize_if_capacity_reached) {

  given("a vector")
    Vector vector = vector_init(i32);
    vector_create(&vector);

  when("the vector is reaching full capacity")
    i32 element = 3;
    vector_push(&vector, &element);
    vector_push(&vector, &element);
    vector_push(&vector, &element);
    vector_push(&vector, &element);
    vector_push(&vector, &element);
    vector_push(&vector, &element);
    vector_push(&vector, &element);
    verify(vector.length == 7);
    verify(vector.capacity == 8);
  
  calling("vector_push()")
    vector_push(&vector, &element);

  must("resize the vector by doubling the capacity")
    verify(vector.length == 8);
    verify(vector.capacity == 16);
    for (u32 i = 0; i < vector.length; i++)
      verify(vector_get(&vector, i) == &element);
    for (u32 i = vector.length; i < vector.capacity; i++)
      verify(vector_get(&vector, i) == NULL);

  success()
    vector_destroy(&vector);
}
