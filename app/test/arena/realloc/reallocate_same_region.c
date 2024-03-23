test(arena_realloc_reallocate_same_region) {

  given("an arena")
    Arena arena = arena_init();
    arena_create(&arena, 128);

  when("some allocated memory is present in the end region");
    arena_malloc(&arena, 32);
    byte* data = arena_malloc(&arena, 16);

  when("there is enough space in the end region");
    verify(arena.end->position == 48);
  
  calling("arena_realloc() on the previously allocated memory")
    data = arena_realloc(&arena, data, 32);
  
  must("reallocate the memory with the provided amount in the same region")
    verify(arena.end->position == 80);

  success()
    arena_destroy(&arena);
}
