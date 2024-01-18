void* arena_malloc (
    struct arena* arena,
    int64 size
)
/**
 * This function shall allocate new *size* amount of bytes in the arena. */
{
  if (arena == NULL)
    return malloc(size);

  struct region* last_region = arena->end;
  if (last_region->pos + size <= last_region->size) {
    byte* data = last_region->data + last_region->pos;
    last_region->pos += size;
    return data;
  }

  struct region* next = arena_region_next(arena, size);
  if (next == NULL) 
    return NULL;

  return next->data;
}
