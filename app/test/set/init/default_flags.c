test(set_init_default_flags) {

  given("a set")
    struct set set = set_init(i32);
  
  when("no flags are provided")
  
  calling("set_init()")
  
  must("create the set with the default flags")
    verify(set.elements.flags == Map_Flag__None);

  success()
    set_destroy(&set);
}
