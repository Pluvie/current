test(map_get_return_null) {

  given("a map")
    Map map = map_init(i32, i32);
    map_create(&map);

  when("a key is not present")
    i32 key = 3;

  calling("map_get()");
    void* retrieved_value = map_get(&map, &key);

  must("return NULL")
    verify(retrieved_value == NULL);

  success()
    map_destroy(&map);
}
