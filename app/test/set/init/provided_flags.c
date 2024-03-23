test(set_init_provided_flags) {

  given("a set")
    Set set = set_init(i32);
  
  when("flags are provided")
    set_flag_enable(&set, SET_FLAG__COPY_ELEMENTS);
  
  calling("set_init()")
  
  must("create the set with the provided flags")
    verify(set.elements.flags & MAP_FLAG__COPY_KEYS);
    verify(set.elements.flags & MAP_FLAG__COPY_VALUES);

  success()
    set_destroy(&set);
}
