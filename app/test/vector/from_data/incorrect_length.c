test(vector_from_data_incorrect_length) {

  given("a vector")
    Vector vector = vector_init(i32);
  
  when("fixed data is present, but with incorrect length")
    const byte data[31] = {
      1, 0, 0, 0,
      2, 0, 0, 0,
      3, 0, 0, 0,
      4, 0, 0, 0,
      5, 0, 0, 0,
      6, 0, 0, 0,
      7, 0, 0, 0,
      8, 0, 0
    };
    u64 data_length = sizeof(data);
  
  calling("vector_fromdata()")
    bool result = vector_from_data(&vector, (const byte*) data, data_length);
  
  must("initialize a read only vector with the correct length")
    verify(result == false);
    verify(vector.length == 0);
    verify(vector.capacity == 0);
    verify(vector.elements == NULL);

  success()
    vector_destroy(&vector);
}
