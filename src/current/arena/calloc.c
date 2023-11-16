void* arena_calloc (
    struct arena* arena,
    int64 num,
    int64 size
)
/**
 * This function shall allocate *num* times *size* amount of bytes in the arena, and
 * shall set all those bytes to `0`. */
{
  void* memory = arena_malloc(arena, num * size);
  memset(memory, '\0', num * size);
  return memory;
}
