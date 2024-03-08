test(set_has_true_if_element_present) {

  given("a set")
    struct set set = set_init(i32);
    set_create(&set);

  when("a element is present")
    i32 element = 3;
    set_add(&set, &element);

  calling("set_has() on that element");
    bool result = set_has(&set, &element);

  must("return true")
    verify(result == true);

  success()
    set_destroy(&set);
}
