void* arena_prealloc (
    struct arena* arena,
    int64 size
)
/**
 * This function shall reserve *size* amount of bytes in the arena.
 * If the amount is already available, nothing is done. Otherwise, a new region with
 * the requested amount shall be created. */
{
  if (arena == NULL)
    return NULL;

  struct region* last_region = arena->end;
  int64 available_space = last_region->size - last_region->pos;
  if (available_space >= size)
    return last_region->data + last_region->pos;

  struct region* region = arena_region_next(arena, size);
  if (region == NULL)
    return NULL;

  return region->data;
}
