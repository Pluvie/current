test(arena_calloc_allocate_at_zero) {

  given("an arena")
    struct arena arena = arena_init();
    arena_create(&arena, 128);

  calling("arena_calloc()")
    byte* data = arena_calloc(&arena, 1, 32);
  
  must("allocate the provided amount and set the bytes at zero")
    for (u64 i = 0; i < 32; i++)
      verify(data[i] == 0);

  success()
    arena_destroy(&arena);
}
