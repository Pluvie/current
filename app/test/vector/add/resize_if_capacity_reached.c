test(vector_add_resize_if_capacity_reached) {

  given("a vector")
    struct vector vector = vector_init(i32);
    vector_create(&vector);

  when("the vector is reaching full capacity")
    i32 element = 3;
    vector_add(&vector, &element);
    vector_add(&vector, &element);
    vector_add(&vector, &element);
    vector_add(&vector, &element);
    vector_add(&vector, &element);
    vector_add(&vector, &element);
    vector_add(&vector, &element);
    verify(vector.length == 7);
    verify(vector.capacity == 8);
  
  calling("vector_add()")
    vector_add(&vector, &element);

  must("resize the vector by doubling the capacity")
    verify(vector.length == 8);
    verify(vector.capacity == 16);
    for (u32 i = 0; i < vector.length; i++)
      verify(vector.elements[i].value == &element);
    for (u32 i = vector.length; i < vector.capacity; i++)
      verify(vector.elements[i].value == NULL);

  success()
    vector_destroy(&vector);
}
