test(set_del_remove_element) {

  given("a set")
    Set set = set_init(i32);
    set_create(&set);

  when("an element is present")
    i32 element = 3;
    set_add(&set, &element);

  calling("set_del()");
    void* deleted_value = set_del(&set, &element);

  must("remove that element")
    verify(set_has(&set, &element) == false);
    verify(deleted_value == &element);
    verify(*(i32*) deleted_value == element);

  success()
    set_destroy(&set);
}
