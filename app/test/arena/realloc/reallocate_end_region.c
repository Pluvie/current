test(arena_realloc_reallocate_end_region) {

  given("an arena")
    struct arena arena = arena_init();
    arena_alloc(&arena, 128);

  when("some allocated memory is present in the end region");
    arena_malloc(&arena, 92);
    byte* data = arena_malloc(&arena, 16);

  when("there not is enough space in the end region");
    struct region* original_region = arena.end;
    verify(arena.end->position == 108);
  
  calling("arena_realloc() on the previously allocated memory")
    data = arena_realloc(&arena, data, 32);
  
  must("reallocate the memory with the provided amount in the end region")
    verify(arena.end != original_region);
    verify(arena.end->data == data);
    verify(arena.end->capacity == 32);
    verify(arena.end->position == 32);

  success()
    arena_destroy(&arena);
}
