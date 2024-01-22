void test_arena()
{
  describe("Arena");

  test("on init, it must create a region with the provided amount of bytes "\
       "of capacity") {
    struct arena* arena = arena_init(ARENA_REGION_MIN_CAPACITY + 1);
    assert(arena != NULL);
    assert(arena->begin != NULL);
    assert(arena->begin != NULL);
    assert(arena->begin == arena->end);
    assert(arena->begin->position == 0);
    assert(arena->begin->capacity == ARENA_REGION_MIN_CAPACITY + 1);
    arena_destroy(arena);
    success();
  }

  test("on init, if the provided amount of bytes of capacity is inferior to the "\
       "minimum, it must create a region with the minimum amount of bytes of capacity") {
    struct arena* arena = arena_init(8);
    assert(arena != NULL);
    assert(arena->begin != NULL);
    assert(arena->begin != NULL);
    assert(arena->begin == arena->end);
    assert(arena->begin->position == 0);
    assert(arena->begin->capacity == ARENA_REGION_MIN_CAPACITY);
    arena_destroy(arena);
    success();
  }

  test("on malloc, it must allocate the provided amount of bytes") {
    struct arena* arena = arena_init(ARENA_REGION_MIN_CAPACITY);
    byte* data = arena_malloc(arena, 1024);
    assert(data != NULL);
    assert(arena->begin->capacity == ARENA_REGION_MIN_CAPACITY);
    assert(arena->begin->position == 1024);
    assert(arena->begin->data == data);
    arena_destroy(arena);
    success();
  }

  test("on malloc, if there is enough space in the region, it must allocate the "\
       "provided amount of bytes by just advancing the region position") {
    struct arena* arena = arena_init(ARENA_REGION_MIN_CAPACITY);
    byte* data = arena_malloc(arena, 1024);
    assert(data != NULL);
    assert(arena->begin->position == 1024);
    assert(arena->begin->data == data);

    data = arena_malloc(arena, 512);
    assert(data != NULL);
    assert(arena->begin->position == 1024 + 512);
    assert(arena->begin->data + 1024 == data);
    arena_destroy(arena);
    success();
  }

  test("on malloc, if there is not enough space in the region, it must allocate the "\
       "provided amount of bytes on a new region") {
    struct arena* arena = arena_init(ARENA_REGION_MIN_CAPACITY);
    byte* data = arena_malloc(arena, ARENA_REGION_MIN_CAPACITY);
    assert(data != NULL);
    assert(arena->begin == arena->end);
    assert(arena->begin->capacity == ARENA_REGION_MIN_CAPACITY);
    assert(arena->begin->position == ARENA_REGION_MIN_CAPACITY);
    assert(arena->begin->data == data);

    data = arena_malloc(arena, 1024);
    assert(data != NULL);
    assert(arena->end != arena->begin);
    assert(arena->end->capacity == ARENA_REGION_MIN_CAPACITY);
    assert(arena->end->position == 1024);
    assert(arena->end->data == data);
    arena_destroy(arena);
    success();
  }

  test("on calloc, it must allocate the provided amount of bytes, and set them "\
       "all to 0") {
    struct arena* arena = arena_init(ARENA_REGION_MIN_CAPACITY);
    byte* data = arena_calloc(arena, 2, 1024);
    assert(data != NULL);
    assert(arena->begin->capacity == ARENA_REGION_MIN_CAPACITY);
    assert(arena->begin->position == 2048);
    assert(arena->begin->data == data);
    for (u64 i = 0; i < 2048; i++)
      assert(data[i] == 0);
    arena_destroy(arena);
    success();
  }

  test("on realloc, it must reallocate the provided memory to the new amount of "\
       "bytes, copying the memory content") {
    struct arena* arena = arena_init(ARENA_REGION_MIN_CAPACITY);
    byte* data = arena_malloc(arena, 1024);
    assert(data != NULL);
    memset(data, 77, 1024);
    assert(arena->begin->capacity == ARENA_REGION_MIN_CAPACITY);
    assert(arena->begin->position == 1024);
    assert(arena->begin->data == data);

    data = arena_realloc(arena, data, 1024 * 2);
    assert(data != NULL);
    assert(arena->begin == arena->end);
    assert(arena->begin->position == 1024 + (1024 * 2));
    assert(arena->begin->data + 1024 == data);
    for (u64 i = 0; i < 1024; i++)
      assert(data[i] == 77);
    arena_destroy(arena);
    success();
  }

  test("on realloc, if there is not enough space in the region, it must reallocate "\
       "the provided memory to the new amount of bytes in a new region, and copy "\
       "the memory content") {
    struct arena* arena = arena_init(ARENA_REGION_MIN_CAPACITY);
    byte* data = arena_malloc(arena, 1024);
    assert(data != NULL);
    memset(data, 77, 1024);
    assert(arena->begin->capacity == ARENA_REGION_MIN_CAPACITY);
    assert(arena->begin->position == 1024);
    assert(arena->begin->data == data);

    byte* fill_data = arena_malloc(arena, ARENA_REGION_MIN_CAPACITY - 1024);
    assert(fill_data != NULL);
    assert(arena->begin->capacity == ARENA_REGION_MIN_CAPACITY);
    assert(arena->begin->position == ARENA_REGION_MIN_CAPACITY);
    assert(arena->begin->data + 1024 == fill_data);

    data = arena_realloc(arena, data, 1024 * 2);
    assert(data != NULL);
    assert(arena->end != arena->begin);
    assert(arena->end->capacity == ARENA_REGION_MIN_CAPACITY);
    assert(arena->end->position == 1024 * 2);
    assert(arena->end->data == data);
    for (u64 i = 0; i < 1024; i++)
      assert(data[i] == 77);
    arena_destroy(arena);
    success();
  }
}
