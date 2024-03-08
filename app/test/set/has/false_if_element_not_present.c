test(set_has_false_if_element_not_present) {

  given("a set")
    struct set set = set_init(i32);
    set_create(&set);

  when("a element is not present")
    i32 element = 3;

  calling("set_has() on that element");
    bool result = set_has(&set, &element);

  must("return true")
    verify(result == false);

  success()
    set_destroy(&set);
}
