test(arena_realloc_copy_reallocated_memory) {

  given("an arena")
    Arena arena = arena_init();
    arena_create(&arena, 128);

  when("some allocated memory is present in the end region");
    arena_malloc(&arena, 32);
    byte* data = arena_malloc(&arena, 16);
    memset(data, '\7', 16);
  
  calling("arena_realloc() on the previously allocated memory")
    data = arena_realloc(&arena, data, 32);
  
  must("reallocate the memory with the provided amount and copy its content")
    for (u64 i = 0; i < 16; i++)
      verify(data[i] == '\7');

  success()
    arena_destroy(&arena);
}
