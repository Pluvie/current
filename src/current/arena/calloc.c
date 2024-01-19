void* arena_calloc (
    struct arena* arena,
    u64 quantity,
    u64 amount
)
/**
 * This function shall allocate *quantity* times *amount* of bytes in the arena, and
 * shall set all those bytes to `0`. */
{
  if (arena == NULL)
    return calloc(quantity, amount);

  void* memory = arena_malloc(arena, quantity * amount);
  memset(memory, '\0', quantity * amount);
  return memory;
}
