test(arena_realloc_reallocate_same_region) {

  given("an arena")
    struct arena arena = arena_init();
    arena_alloc(&arena, 128);

  when("some allocated memory is present in the end region");
    arena_malloc(&arena, 32);
    byte* data = arena_malloc(&arena, 16);
    memset(data, '\7', 16);

  when("there is enough space in the end region");
    verify(arena.end->position == 48);
  
  calling("arena_realloc() on the previously allocated memory")
    arena_malloc(&arena, 32);
  
  must("reallocate the memory with the provided amount in the same region")
    verify(arena.end->position == 80);

  success()
    arena_destroy(&arena);
}