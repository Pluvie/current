test(arena_create_allocate_begin_region) {

  given("an arena")
    Arena arena = arena_init();
    verify(arena.begin == NULL);
  
  calling("arena_create()")
    arena_create(&arena, 32);
  
  must("allocate the begin region")
    verify(arena.begin != NULL);

  success()
    arena_destroy(&arena);
}
