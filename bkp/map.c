void test_map()
{
  describe("Map");
//
//  test("`map()` must create a new map with the correct key and value sizes") {
//    struct map* test_map = map(i32, i32, NULL);
//    assert(test_map->key_size == sizeof(i32));
//    assert(test_map->value_size == sizeof(i32));
//    map_free(test_map);
//    success();
//  }
//
//  test("`map()` must create a new map with the default capacity if no capacity "\
//       "is provided") {
//    struct map* test_map = map(i32, i32, NULL);
//    assert(test_map->capacity == MAP_DEFAULT_CAPACITY);
//    map_free(test_map);
//    success();
//  }
//
//  test("`map()` must create a new map with the default capacity if the provided "\
//       "capacity is inferior to the minimum") {
//    struct map_parameters test_map_params = { .capacity = 4 };
//    struct map* test_map = map(i32, i32, &test_map_params);
//    assert(test_map->capacity != test_map_params.capacity);
//    assert(test_map->capacity == MAP_DEFAULT_CAPACITY);
//    map_free(test_map);
//    success();
//  }
//
//  test("`map()` must create a new map with the provided capacity") {
//    struct map_parameters test_map_params = { .capacity = 16 };
//    struct map* test_map = map(i32, i32, &test_map_params);
//    assert(test_map->capacity == test_map_params.capacity);
//    assert(test_map->capacity != MAP_DEFAULT_CAPACITY);
//    map_free(test_map);
//    success();
//  }
//
//  test("`map()` must create a new map with no flags if none are provided") {
//    struct map* test_map = map(i32, i32, NULL);
//    assert(test_map->flags == Map_Flag__None);
//    assert((test_map->flags & Map_Flag__Copy_Keys) == false);
//    assert((test_map->flags & Map_Flag__Copy_Values) == false);
//    map_free(test_map);
//    success();
//  }
//
//  test("`map()` must create a new map with the provided flags") {
//    struct map_parameters test_map_params = { .flags = Map_Flag__Copy_Keys };
//    struct map* test_map = map(i32, i32, &test_map_params);
//    assert(test_map->flags != Map_Flag__None);
//    assert(test_map->flags & Map_Flag__Copy_Keys);
//    map_free(test_map);
//    success();
//  }

  test("`map()` must create a new arena allocated map if an arena is provided") {
    struct arena* arena = arena_new();
    assert(arena->end->position == 0);

    struct map_parameters test_map_params = { .arena = arena };
    struct map* test_map = map(i32, i32, &test_map_params);

    assert(test_map->capacity == MAP_DEFAULT_CAPACITY);
    assert(arena->end->position > 0);
    map_free(test_map);
    arena_destroy(arena);
    success();
  }

//  test("`map_set()` must set the provided key with the provided value") {
//    struct map* test_map = map(i32, i32, NULL);
//    i32 key = 3;
//    i32 value = 7;
//    map_set(test_map, &key, &value);
//
//    u64 capped_hash = test_map->hash(&key, test_map->key_size) % test_map->capacity;
//    struct map_entry* entry = test_map->buckets[capped_hash];
//
//    assert(entry->key == &key);
//    assert(entry->value == &value);
//    assert(*((i32*) entry->key) == key);
//    assert(*((i32*) entry->value) == value);
//    map_free(test_map);
//    success();
//  }

//  test("`map_set()` must set the provided key with the provided value, and make a "
//       "copy of the key if the `Map_Flag__Copy_Keys` flag is enabled and the key was "\
//       "not yet present in the map") {
//    struct map_parameters test_map_params = { .flags = Map_Flag__Copy_Keys };
//    struct map* test_map = map(i32, i32, &test_map_params);
//    i32 key = 3;
//    i32 value = 7;
//    map_set(test_map, &key, &value);
//
//    u64 capped_hash = test_map->hash(&key, test_map->key_size) % test_map->capacity;
//    struct map_entry* entry = test_map->buckets[capped_hash];
//
//    assert(entry->key != &key);
//    assert(entry->value == &value);
//    assert(*((i32*) entry->key) == key);
//    assert(*((i32*) entry->value) == value);
//    map_free(test_map);
//    success();
//  }
//
//  test("`map_set()` must set the provided key with the provided value, and make a "
//       "copy of the value if the `Map_Flag__Copy_Values` flag is enabled and the key "\
//       "was not yet present in the map") {
//    struct map_parameters test_map_params = { .flags = Map_Flag__Copy_Values };
//    struct map* test_map = map(i32, i32, &test_map_params);
//    i32 key = 3;
//    i32 value = 7;
//    map_set(test_map, &key, &value);
//
//    u64 capped_hash = test_map->hash(&key, test_map->key_size) % test_map->capacity;
//    struct map_entry* entry = test_map->buckets[capped_hash];
//
//    assert(entry->key == &key);
//    assert(entry->value != &value);
//    assert(*((i32*) entry->key) == key);
//    assert(*((i32*) entry->value) == value);
//    map_free(test_map);
//    success();
//  }

//  test("`map_set()` must set the provided key with the provided value, and overwrite "\
//       "any previous value for the same key") {
//    struct map* test_map = map(i32, i32, NULL);
//    i32 key = 3;
//    i32 value = 7;
//    map_set(test_map, &key, &value);
//
//    u64 capped_hash = test_map->hash(&key, test_map->key_size) % test_map->capacity;
//    struct map_entry* entry = test_map->buckets[capped_hash];
//
//    assert(entry->value == &value);
//    assert(*((i32*)entry->value) == value);
//
//    value = 9;
//    map_set(test_map, &key, &value);
//    assert(entry->key == &key);
//    assert(entry->value == &value);
//    assert(*((i32*) entry->key) == key);
//    assert(*((i32*) entry->value) != 7);
//    assert(*((i32*) entry->value) == value);
//
//    map_free(test_map);
//    success();
//  }

//  test("`map_set()` must avoid making a copy of the key, even if the "\
//       "`Map_Flag__Copy_Keys` flag is enabled, if the key was already present") {
//    struct map_parameters test_map_params = { .flags = Map_Flag__Copy_Keys };
//    struct map* test_map = map(i32, i32, &test_map_params);
//    i32 key = 3;
//    i32 value = 7;
//    map_set(test_map, &key, &value);
//
//    u64 capped_hash = test_map->hash(&key, test_map->key_size) % test_map->capacity;
//    struct map_entry* entry = test_map->buckets[capped_hash];
//
//    void* key_copy_addr = entry->key;
//    assert(entry->key != &key);
//    assert(entry->value == &value);
//    assert(*((i32*) entry->key) == key);
//    assert(*((i32*) entry->value) == value);
//
//    value = 9;
//    map_set(test_map, &key, &value);
//    assert(entry->key == key_copy_addr);
//    assert(entry->value == &value);
//    assert(*((i32*) entry->key) == key);
//    assert(*((i32*) entry->value) != 7);
//    assert(*((i32*) entry->value) == value);
//
//    map_free(test_map);
//    success();
//  }

//  test("`map_set()` must make a copy of the value, if the `Map_Flag__Copy_Value` "\
//       "flag is enabled, even if the key was already present") {
//    struct map_parameters test_map_params = { .flags = Map_Flag__Copy_Values };
//    struct map* test_map = map(i32, i32, &test_map_params);
//    i32 key = 3;
//    i32 value = 7;
//    map_set(test_map, &key, &value);
//
//    u64 capped_hash = test_map->hash(&key, test_map->key_size) % test_map->capacity;
//    struct map_entry* entry = test_map->buckets[capped_hash];
//
//    void* value_copy_addr = entry->value;
//    assert(entry->key == &key);
//    assert(entry->value != &value);
//    assert(*((i32*) entry->key) == key);
//    assert(*((i32*) entry->value) == value);
//
//    value = 9;
//    map_set(test_map, &key, &value);
//    assert(entry->key == &key);
//    assert(entry->value != value_copy_addr);
//    assert(*((i32*) entry->key) == key);
//    assert(*((i32*) entry->value) != 7);
//    assert(*((i32*) entry->value) == value);
//
//    map_free(test_map);
//    success();
//  }

//  test("`map_set()` must trigger a rehash if, by adding a new entry, causes the load "\
//       "factor of the map to surpass the threshold") {
//    struct map* test_map = map(i32, i32, NULL);
//    i32 numbers[] = { 0, 1, 2, 3, 4, 5 };
//
//    for (u32 i = 0; i < 5; i++)
//      map_set(test_map, &numbers[i], &numbers[i]);
//    for (u32 i = 0; i < 5; i++)
//      assert(*((i32*) map_get(test_map, &numbers[i])) == numbers[i]);
//    assert(test_map->capacity == 8);
//
//    map_set(test_map, &numbers[5], &numbers[5]);
//    assert(test_map->capacity == 16);
//    for (u32 i = 0; i < countof(numbers); i++)
//      assert(*((i32*) map_get(test_map, &numbers[i])) == numbers[i]);
//
//    map_free(test_map);
//    success();
//  }

//  test("`map_rehash()` must avoid making a copy of each entry key, even if the "\
//       "`Map_Flag__Copy_Key` flag is enabled") {
//    struct map_parameters test_map_params = { .flags = Map_Flag__Copy_Keys };
//    struct map* test_map = map(i32, i32, &test_map_params);
//    i32 numbers[] = { 0, 1, 2, 3, 4, 5 };
//    void* key_addresses[5] = { 0 };
//
//    for (u32 i = 0; i < 5; i++)
//      map_set(test_map, &numbers[i], &numbers[i]);
//    for (u32 i = 0; i < 5; i++) {
//      key_addresses[i] = map_get_entry(test_map, &numbers[i])->key;
//      assert(key_addresses[i] != &numbers[i]);
//      assert(*((i32*) map_get(test_map, &numbers[i])) == numbers[i]);
//    }
//    assert(test_map->capacity == 8);
//
//    map_set(test_map, &numbers[5], &numbers[5]);
//    assert(test_map->capacity == 16);
//    for (u32 i = 0; i < countof(numbers); i++) {
//      if (i < 5)
//        assert(map_get_entry(test_map, &numbers[i])->key == key_addresses[i]);
//      assert(*((i32*) map_get(test_map, &numbers[i])) == numbers[i]);
//    }
//
//    map_free(test_map);
//    success();
//  }
//
//  test("`map_rehash()` must avoid making a copy of each entry value, even if the "\
//       "`Map_Flag__Copy_Values` flag is enabled") {
//    struct map_parameters test_map_params = { .flags = Map_Flag__Copy_Values };
//    struct map* test_map = map(i32, i32, &test_map_params);
//    i32 numbers[] = { 0, 1, 2, 3, 4, 5 };
//    void* value_addresses[5] = { 0 };
//
//    for (u32 i = 0; i < 5; i++)
//      map_set(test_map, &numbers[i], &numbers[i]);
//    for (u32 i = 0; i < 5; i++) {
//      value_addresses[i] = map_get(test_map, &numbers[i]);
//      assert(value_addresses[i] != &numbers[i]);
//      assert(*((i32*) map_get(test_map, &numbers[i])) == numbers[i]);
//    }
//    assert(test_map->capacity == 8);
//
//    map_set(test_map, &numbers[5], &numbers[5]);
//    assert(test_map->capacity == 16);
//    for (u32 i = 0; i < countof(numbers); i++) {
//      if (i < 5)
//        assert(map_get(test_map, &numbers[i]) == value_addresses[i]);
//      assert(*((i32*) map_get(test_map, &numbers[i])) == numbers[i]);
//    }
//
//    map_free(test_map);
//    success();
//  }

//  test("`map_get()` must retrieve the value of the provided key") {
//    struct map* test_map = map(i32, i32, NULL);
//    i32 key = 3;
//    i32 value = 7;
//    map_set(test_map, &key, &value);
//    assert(*((i32*) map_get(test_map, &key)) == value);
//    map_free(test_map);
//    success();
//  }

//  test("`map_get()` must return a NULL pointer if the provided key is not present") {
//    struct map* test_map = map(i32, i32, NULL);
//    i32 key = 3;
//    assert(map_get(test_map, &key) == NULL);
//    map_free(test_map);
//    success();
//  }
//
//  test("`map_del()` must delete the value of the provided key") {
//    struct map* test_map = map(i32, i32, NULL);
//    i32 key = 3;
//    i32 value = 7;
//    map_set(test_map, &key, &value);
//    assert(*((i32*) map_get(test_map, &key)) == value);
//    map_del(test_map, &key);
//    assert(map_get(test_map, &key) == NULL);
//    map_free(test_map);
//    success();
//  }

//  test("`map_has()` must return `true` if provided key is present in the map") {
//    struct map* test_map = map(i32, i32, NULL);
//    i32 key = 3;
//    i32 value = 7;
//    map_set(test_map, &key, &value);
//    assert(map_has(test_map, &key) == true);
//    map_free(test_map);
//    success();
//  }
//
//  test("`map_has()` must return `false` if provided key is not present in the map") {
//    struct map* test_map = map(i32, i32, NULL);
//    i32 key = 3;
//    assert(map_has(test_map, &key) == false);
//    map_free(test_map);
//    success();
//  }
}
