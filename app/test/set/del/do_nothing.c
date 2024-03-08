test(set_del_do_nothing) {

  given("a set")
    struct set set = set_init(i32);
    set_create(&set);

  when("an element is not present")
    i32 element = 3;
    u64 set_length = set.length;

  calling("set_del()");
    void* deleted_value = set_del(&set, &element);

  must("keep the set unchanged")
    verify(deleted_value == NULL);
    verify(set.length == set_length);

  success()
    set_destroy(&set);
}
