test(set_add_new_element_if_not_present) {

  given("a set")
    struct set set = set_init(i32);
    set_create(&set);

  when("a element is not present")
    verify(set.length == 0);

  calling("set_add()");
    i32 element = 3;
    set_add(&set, &element);
  
  must("add that element anew")
    verify(set_has(&set, &element) == true);
    verify(set.length == 1);

  success()
    set_destroy(&set);
}
