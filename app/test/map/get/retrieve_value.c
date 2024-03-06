test(map_get_retrieve_value) {

  given("a map")
    struct map map = map_init(i32, i32);
    map_create(&map);

  when("a key is present")
    i32 key = 3;
    i32 value = 7;
    map_set(&map, &key, &value);

  calling("map_get()");
    void* retrieved_value = map_get(&map, &key);

  must("retrieve the correct value")
    verify(retrieved_value == &value);
    verify(*(i32*) retrieved_value == value);

  success()
    map_destroy(&map);
}
