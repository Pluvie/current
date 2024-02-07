void test_map()
{
  describe("Map");

  test("`map()` must create a new map with the correct key and value sizes") {
    struct map* test_map = map(i32, i32, NULL);
    assert(test_map->key_size == sizeof(i32));
    assert(test_map->value_size == sizeof(i32));
    map_free(test_map);
    success();
  }

  test("`map()` must create a new map with the default capacity if no capacity "\
       "is provided") {
    struct map* test_map = map(i32, i32, NULL);
    assert(test_map->capacity == MAP_DEFAULT_CAPACITY);
    map_free(test_map);
    success();
  }

  test("`map()` must create a new map with the default capacity if the provided "\
       "capacity is inferior to the minimum") {
    struct map_parameters test_map_params = { .capacity = 4 };
    struct map* test_map = map(i32, i32, &test_map_params);
    assert(test_map->capacity != test_map_params.capacity);
    assert(test_map->capacity == MAP_DEFAULT_CAPACITY);
    map_free(test_map);
    success();
  }

  test("`map()` must create a new map with the provided capacity") {
    struct map_parameters test_map_params = { .capacity = 16 };
    struct map* test_map = map(i32, i32, &test_map_params);
    assert(test_map->capacity == test_map_params.capacity);
    assert(test_map->capacity != MAP_DEFAULT_CAPACITY);
    map_free(test_map);
    success();
  }

  test("`map()` must create a new map with no flags if none are provided") {
    struct map* test_map = map(i32, i32, NULL);
    assert(test_map->flags == Map_Flag__None);
    assert((test_map->flags & Map_Flag__Copy_Keys) == false);
    assert((test_map->flags & Map_Flag__Copy_Values) == false);
    map_free(test_map);
    success();
  }

  test("`map()` must create a new map with the provided flags") {
    struct map_parameters test_map_params = { .flags = Map_Flag__Copy_Keys };
    struct map* test_map = map(i32, i32, &test_map_params);
    assert(test_map->flags != Map_Flag__None);
    assert(test_map->flags & Map_Flag__Copy_Keys);
    map_free(test_map);
    success();
  }

  test("`map()` must create a new arena allocated map if an arena is provided") {
    struct arena* arena = arena_init(1024);
    assert(arena->end->position == 0);

    struct map_parameters test_map_params = { .arena = arena };
    struct map* test_map = map(i32, i32, &test_map_params);

    assert(test_map->capacity == MAP_DEFAULT_CAPACITY);
    assert(arena->end->position > 0);
    map_free(test_map);
    arena_destroy(arena);
    success();
  }

  test("`map_set()` must set the provided key with the provided value") {
    struct map* test_map = map(i32, i32, NULL);
    i32 key = 3;
    i32 value = 7;
    map_set(test_map, &key, &value);

    u64 capped_hash = test_map->hash(&key, test_map->key_size) % test_map->capacity;
    struct map_entry* entry = test_map->buckets[capped_hash];

    assert(entry->key == &key);
    assert(entry->value == &value);
    assert(*((i32*) entry->key) == key);
    assert(*((i32*) entry->value) == value);
    map_free(test_map);
    success();
  }

  test("`map_set()` must set the provided key with the provided value, and make a "
       "copy of the key if the `Map_Flag__Copy_Keys` flag is enabled") {
    struct map_parameters test_map_params = { .flags = Map_Flag__Copy_Keys };
    struct map* test_map = map(i32, i32, &test_map_params);
    i32 key = 3;
    i32 value = 7;
    map_set(test_map, &key, &value);

    u64 capped_hash = test_map->hash(&key, test_map->key_size) % test_map->capacity;
    struct map_entry* entry = test_map->buckets[capped_hash];

    assert(entry->key != &key);
    assert(entry->value == &value);
    assert(*((i32*) entry->key) == key);
    assert(*((i32*) entry->value) == value);
    map_free(test_map);
    success();
  }

  test("`map_set()` must set the provided key with the provided value, and overwrite "\
       "any previous value for the same key") {
    struct map* test_map = map(i32, i32, NULL);
    i32 key = 3;
    i32 value = 7;
    map_set(test_map, &key, &value);

    u64 capped_hash = test_map->hash(&key, test_map->key_size) % test_map->capacity;
    struct map_entry* entry = test_map->buckets[capped_hash];

    assert(entry->value == &value);
    assert(*((i32*)entry->value) == value);

    value = 9;
    map_set(test_map, &key, &value);
    assert(entry->key == &key);
    assert(entry->value == &value);
    assert(*((i32*) entry->key) == key);
    assert(*((i32*) entry->value) != 7);
    assert(*((i32*) entry->value) == value);

    map_free(test_map);
    success();
  }

  test("`map_get()` must retrieve the value of the provided key") {
    struct map* test_map = map(i32, i32, NULL);
    i32 key = 3;
    i32 value = 7;
    map_set(test_map, &key, &value);
    assert(*((i32*) map_get(test_map, &key)) == value);
    map_free(test_map);
    success();
  }

  test("`map_get()` must return a NULL pointer if the provided key is not present") {
    struct map* test_map = map(i32, i32, NULL);
    i32 key = 3;
    assert(map_get(test_map, &key) == NULL);
    map_free(test_map);
    success();
  }

  test("`map_del()` must delete the value of the provided key") {
    struct map* test_map = map(i32, i32, NULL);
    i32 key = 3;
    i32 value = 7;
    map_set(test_map, &key, &value);
    assert(*((i32*) map_get(test_map, &key)) == value);
    map_del(test_map, &key);
    assert(map_get(test_map, &key) == NULL);
    map_free(test_map);
    success();
  }

  test("`map_has()` must return `true` if provided key is present in the map") {
    struct map* test_map = map(i32, i32, NULL);
    i32 key = 3;
    i32 value = 7;
    map_set(test_map, &key, &value);
    assert(map_has(test_map, &key) == true);
    map_free(test_map);
    success();
  }

  test("`map_has()` must return `false` if provided key is not present in the map") {
    struct map* test_map = map(i32, i32, NULL);
    i32 key = 3;
    assert(map_has(test_map, &key) == false);
    map_free(test_map);
    success();
  }
}
