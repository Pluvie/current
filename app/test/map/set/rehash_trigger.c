test(map_set_rehash_trigger) {

  given("a map")
    struct map map = map_init(i32, i32);
    map_alloc(&map);

  when("the map load factor is near the threshold")
    i32 numbers[] = { 0, 1, 2, 3, 4, 5 };
    for (u32 i = 0; i < countof(numbers) - 1; i++) {
      map_set(&map, &numbers[i], &numbers[i]);
      verify(map_get(&map, &numbers[i]) == &numbers[i]);
    }
    verify(map.capacity == 8);

  calling("map_set()");
    map_set(&map, &numbers[5], &numbers[5]);
  
  must("trigger a map rehash")
    verify(map.capacity == 16);
    for (u32 i = 0; i < countof(numbers); i++) {
      verify(map_get(&map, &numbers[i]) == &numbers[i]);
      verify(*((i32*) map_get(&map, &numbers[i])) == numbers[i]);
    }

  success()
    map_free(&map);
}
