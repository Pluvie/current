test(map_correct_value_size) {

  given("a map(i32, i32)")
    struct map map_ptr = map(i32, i32);
  
  must("create the map with the correct value size")
    verify(map_ptr.value_size == sizeof(i32));

  success()
    map_free(&map_ptr);
}
