void* arena_realloc (
    struct arena* arena,
    void* memory,
    int64 size
)
/**
 * Reallocates the *memory* in the arena to a new *size*. */
{
  struct region* memory_region = arena_region_search(arena, memory);
  if (memory_region == NULL)
    return NULL;

  int64 max_size = (memory_region->data + memory_region->size) - (byte*) memory;
  void* new_memory = arena_malloc(arena, size);
  memmove(new_memory, memory, max_size);
  return new_memory;
}
