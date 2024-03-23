test(arena_init_on_stack) {

  given("an arena")
  
  calling("arena_init()")
    Arena arena = arena_init();
  
  must("initialize an empty arena on the stack")
    verify(arena.begin == NULL);
    verify(arena.end == NULL);
    verify(arena.total_capacity == 0);
    verify(arena.number_of_allocs == 0);
    verify(arena.number_of_regions == 0);

  success()
    arena_destroy(&arena);
}
