test(arena_alloc_allocate_begin_region) {

  given("an arena")
    struct arena arena = arena_init();
    verify(arena.begin == NULL);
  
  calling("arena_alloc()")
    arena_alloc(&arena, 32);
  
  must("allocate the begin region")
    verify(arena.begin != NULL);

  success()
    arena_destroy(&arena);
}
