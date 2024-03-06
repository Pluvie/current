test(arena_realloc_no_copy_overlap_old_region) {

  given("an arena")
    struct arena arena = arena_init();
    arena_create(&arena, 128);

  when("some allocated memory is present in the end region");
    arena_malloc(&arena, 92);
    byte* data = arena_malloc(&arena, 16);

  when("there not is enough space in the end region");
    struct region* original_region = arena.end;
    verify(arena.end->position == 108);
  
  calling("arena_realloc() on the previously allocated memory")
    data = arena_realloc(&arena, data, 32);
  
  must("reallocate the memory in the end region without causing memory overlap")
    verify(arena.end != original_region);
    verify(arena.end->position == 32);
    /* Verify also, by looking at Valgrind's output, that no `invalid write of size Y`
     * appear: otherwise, the realloc function is causing overlaps! */

  success()
    arena_destroy(&arena);
}
