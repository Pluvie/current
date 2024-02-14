test(arena_realloc_no_copy_overlap_same_region) {

  given("an arena")
    struct arena arena = arena_init();
    arena_alloc(&arena, 128);

  when("some allocated memory is present in the end region");
    arena_malloc(&arena, 32);
    byte* data = arena_malloc(&arena, 16);
    arena_malloc(&arena, 48);

  when("there is enough space in the end region");
    verify(arena.end->position == 96);
  
  calling("arena_realloc() on the previously allocated memory")
    data = arena_realloc(&arena, data, 32);
  
  must("reallocate the memory in the same region without causing memory overlap")
    verify(arena.end->position == 128);
    /* Verify also, by looking at Valgrind's output, that no `invalid write of size Y`
     * appear: otherwise, the realloc function is causing overlaps! */

  success()
    arena_destroy(&arena);
}
