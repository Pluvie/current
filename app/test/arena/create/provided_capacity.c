test(arena_create_provided_capacity) {

  given("an arena")
    Arena arena = arena_init();
    verify(arena.begin == NULL);
  
  calling("arena_create()")
    u64 capacity = 128;
    arena_create(&arena, capacity);
  
  must("allocate the begin region with the provided capacity")
    verify(arena.begin != NULL);
    verify(arena.begin->capacity == capacity);

  success()
    arena_destroy(&arena);
}
