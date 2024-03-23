test(set_add_invariant_if_element_present) {

  given("a set")
    Set set = set_init(i32);
    set_create(&set);

  when("a element is present")
    i32 element = 3;
    set_add(&set, &element);
    verify(set.length == 1);

  calling("set_add()");
    set_add(&set, &element);
  
  must("keep the set")
    verify(set_has(&set, &element) == true);
    verify(set.length == 1);

  success()
    set_destroy(&set);
}
