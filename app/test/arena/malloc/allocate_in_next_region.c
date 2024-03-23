test(arena_malloc_allocate_in_next_region) {

  given("an arena")
    Arena arena = arena_init();
    arena_create(&arena, 128);

  when("there is not enough space in the end region");
    verify(arena.end->position == 0);
    arena_malloc(&arena, 124);
  
  calling("arena_malloc()")
    arena_malloc(&arena, 32);
  
  must("allocate the provided amount in the next region")
    verify(arena.end != NULL);
    verify(arena.end != arena.begin);
    verify(arena.begin->position == 124);
    verify(arena.end->capacity == 32);
    verify(arena.end->position == 32);

  success()
    arena_destroy(&arena);
}
