test(vector_del_set_unused) {

  given("a vector")
    struct vector vector = vector_init(i32);
    vector_create(&vector);

  when("the vector has some elements")
    i32 element = 3;
    vector_add(&vector, &element);
    vector_add(&vector, &element);
  
  calling("vector_del()")
    vector_pretty_print(&vector);
    vector_del(&vector, 1);

  must("delete the element at the provided position and set it unused")
    verify(vector.length == 1);
    verify(vector.elements[0].used == true);
    verify(vector.elements[1].used == false);

  success()
    vector_destroy(&vector);
}
