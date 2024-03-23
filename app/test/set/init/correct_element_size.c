test(set_init_correct_element_size) {

  given("a set")
    Set set = set_init(i32);
  
  calling("set_init()")

  must("create the set with the correct element size")
    verify(set.elements.key_size == sizeof(i32));

  success()
    set_destroy(&set);
}
