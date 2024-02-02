void test_map()
{
  describe("Map");

  test("`map()` must create a new map with the correct key and value sizes") {
    struct map* test_map = map(i32, i32);
    assert(test_map->key_size == sizeof(i32));
    assert(test_map->value_size == sizeof(i32));
    map_free(test_map);
    success();
  }

  test("`map()` must create a new map with the default capacity") {
    struct map* test_map = map(i32, i32);
    assert(test_map->capacity == MAP_DEFAULT_CAPACITY);
    map_free(test_map);
    success();
  }

  test("`map_arena()` must create a new map allocated in the provided arena") {
    struct arena* arena = arena_init(1024);
    assert(arena->end->position == 0);
    struct map* test_map = map_arena(i32, i32, arena);
    assert(test_map->capacity == MAP_DEFAULT_CAPACITY);
    assert(arena->end->position > 0);
    map_free(test_map);
    success();
  }

  test("`map_set()` must set the provided key with the provided value") {
    struct map* test_map = map(i32, i32);
    i32 key = 3;
    i32 value = 7;
    map_set(test_map, &key, &value);
    u64 capped_hash = test_map->hash(&key, test_map->key_size) % test_map->capacity;
    struct map_entry* entry = test_map->buckets[capped_hash];
    /**
     * Suppose that `capped_hash` is `3`: the map will look like this:
     *
     * [   0] [ -- -- -- -- ] [ -- -- -- -- ]
     * [   1] [ -- -- -- -- ] [ -- -- -- -- ]
     * [   2] [ -- -- -- -- ] [ -- -- -- -- ]
     * [   3] [ 03 00 00 00 ] [ 07 00 00 00 ]     <- This is where `entry` points at.
     * [   4] [ -- -- -- -- ] [ -- -- -- -- ]
     * [   5] [ -- -- -- -- ] [ -- -- -- -- ]
     * [   6] [ -- -- -- -- ] [ -- -- -- -- ]
     * [   7] [ -- -- -- -- ] [ -- -- -- -- ]
     */
    assert(entry->value == &value);
    assert(*((i32*)entry->value) == value);
    map_free(test_map);
    success();
  }

  test("`map_set()` must set the provided key with the provided value, and overwrite "\
       "any previous value for the same key") {
    struct map* test_map = map(i32, i32);
    i32 key = 3;
    i32 value = 7;

    map_set(test_map, &key, &value);
    u64 capped_hash = test_map->hash(&key, test_map->key_size) % test_map->capacity;
    struct map_entry* entry = test_map->buckets[capped_hash];
    assert(entry->value == &value);
    assert(*((i32*)entry->value) == value);

    value = 9;
    map_set(test_map, &key, &value);
    assert(entry->value == &value);
    assert(*((i32*)entry->value) != 7);
    assert(*((i32*)entry->value) == value);

    map_free(test_map);
    success();
  }

  test("`map_get()` must retrieve the value of the provided key") {
    struct map* test_map = map(i32, i32);
    i32 key = 3;
    i32 value = 7;
    map_set(test_map, &key, &value);
    assert(*((i32*) map_get(test_map, &key)) == value);
    map_free(test_map);
    success();
  }

  test("`map_get()` must return a NULL pointer if the provided key is not present") {
    struct map* test_map = map(i32, i32);
    i32 key = 3;
    assert(map_get(test_map, &key) == NULL);
    map_free(test_map);
    success();
  }

  test("`map_del()` must delete the value of the provided key") {
    struct map* test_map = map(i32, i32);
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
    struct map* test_map = map(i32, i32);
    i32 key = 3;
    i32 value = 7;
    map_set(test_map, &key, &value);
    assert(map_has(test_map, &key) == true);
    map_free(test_map);
    success();
  }

  test("`map_has()` must return `false` if provided key is not present in the map") {
    struct map* test_map = map(i32, i32);
    i32 key = 3;
    assert(map_has(test_map, &key) == false);
    map_free(test_map);
    success();
  }
}
