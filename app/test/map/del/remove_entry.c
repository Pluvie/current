test(map_del_remove_entry) {

  given("a map")
    Map map = map_init(i32, i32);
    map_create(&map);

  when("a key is present")
    i32 key = 3;
    i32 value = 7;
    map_set(&map, &key, &value);

  calling("map_del()");
    void* deleted_value = map_del(&map, &key);

  must("remove the entry with that key")
    MapEntry* entry = map_entry_get(&map, &key);
    verify(entry == NULL);
    verify(deleted_value == &value);
    verify(*(i32*) deleted_value == value);

  success()
    map_destroy(&map);
}
