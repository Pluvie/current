test(vector_from_data_init_read_only) {

  given("a vector")
    Vector vector = vector_init(i32);
  
  when("fixed data is present")
    const byte data[32] = {
      1, 0, 0, 0,
      2, 0, 0, 0,
      3, 0, 0, 0,
      4, 0, 0, 0,
      5, 0, 0, 0,
      6, 0, 0, 0,
      7, 0, 0, 0,
      8, 0, 0, 0
    };
    u64 data_length = sizeof(data);
  
  calling("vector_fromdata()")
    bool result = vector_from_data(&vector, (const byte*) data, data_length);
  
  must("initialize a read only vector with the correct length")
    verify(result == true);
    verify(vector.length == 8);
    verify(vector.capacity == 8);
    verify(vector.flags & VECTOR_FLAG__READ_ONLY);
    verify(vector.elements == &data);
    i32* element;
    for vector_each_with_index(&vector, element, index)
      verify(*element == index + 1);

  success()
    vector_destroy(&vector);
}
