test(map_del_do_nothing) {

  given("a map")
    Map map = map_init(i32, i32);
    map_create(&map);

  when("a key is not present")
    i32 key = 3;
    u64 map_length = map.length;

  calling("map_del()");
    void* deleted_value = map_del(&map, &key);

  must("keep the map unchanged")
    verify(deleted_value == NULL);
    verify(map.length == map_length);

  success()
    map_destroy(&map);
}
