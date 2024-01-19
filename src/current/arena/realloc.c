void* arena_realloc (
    struct arena* arena,
    void* memory,
    u64 amount
)
/**
 * Reallocates the *memory* in the arena to a new *amount*. */
{
  if (arena == NULL)
    return realloc(memory, amount);

  struct region* memory_region = arena_region_search(arena, memory);
  if (memory_region == NULL)
    return NULL;

  i64 realloc_amount = 0;
  u64 previous_position = memory_region->position;
  void* new_memory = arena_malloc(arena, amount);

  if ((byte*) new_memory >= memory_region->data &&
      (byte*) new_memory < (memory_region->data + memory_region->capacity))
    realloc_amount = (memory_region->data + previous_position) - (byte*) memory;
  else
    realloc_amount = (memory_region->data + memory_region->capacity) - (byte*) memory;

  memmove(new_memory, memory, realloc_amount);
  return new_memory;
}
