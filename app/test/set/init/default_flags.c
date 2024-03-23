test(set_init_default_flags) {

  given("a set")
    Set set = set_init(i32);
  
  when("no flags are provided")
  
  calling("set_init()")
  
  must("create the set with the default flags")
    verify(set.elements.flags == MAP_FLAG__NONE);

  success()
    set_destroy(&set);
}
