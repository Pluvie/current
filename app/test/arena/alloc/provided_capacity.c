test(arena_alloc_provided_capacity) {

  given("an arena")
    struct arena arena = arena_init();
    verify(arena.begin == NULL);
  
  calling("arena_alloc()")
    u64 capacity = 128;
    arena_alloc(&arena, capacity);
  
  must("allocate the begin region with the provided capacity")
    verify(arena.begin != NULL);
    verify(arena.begin->capacity == capacity);

  success()
    arena_destroy(&arena);
}
