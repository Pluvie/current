void arena_prealloc (
    struct arena* arena,
    int64 size
)
/**
 * This function shall reserve *size* amount of bytes in the arena.
 * If the amount is already available, nothing is done. Otherwise, the end region
 * will be enlarged to fit the amount. */
{
  if (arena == NULL)
    return;

  struct region* last_region = arena->end;
  int64 available_space = last_region->size - last_region->pos;
  if (available_space >= size)
    return;

  int64 missing_space = size - available_space;
  int64 new_size = last_region->size + missing_space;
  last_region->data = realloc(last_region->data, new_size);
  last_region->size = new_size;
}
