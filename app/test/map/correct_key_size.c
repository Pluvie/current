test(map_correct_key_size) {

  given("a map(i32, i32)")
    struct map map_ptr = map(i32, i32);
  
  must("create the map with the correct key size")
    verify(map_ptr.key_size == sizeof(i32));

  success()
    map_free(&map_ptr);
}
