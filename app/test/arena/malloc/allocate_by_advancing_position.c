test(arena_malloc_allocate_by_advancing_position) {

  given("an arena")
    struct arena arena = arena_init();
    arena_alloc(&arena, 128);

  when("there is enough space in the end region");
    verify(arena.end->position == 0);
    arena_malloc(&arena, 32);
  
  calling("arena_malloc()")
    arena_malloc(&arena, 32);
  
  must("allocate the provided amount by just advancing the region position")
    verify(arena.end != NULL);
    verify(arena.end->capacity == 128);
    verify(arena.end->position == 32 + 32);

  success()
    arena_destroy(&arena);
}
