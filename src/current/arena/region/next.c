struct region* arena_region_next (
    struct arena* arena,
    u64 amount
)
/**
 * Allocates the next region, with given *amount* of data, in the arena, and marks
 * its position to the *amount* -- which means that the region is full. */
{
  struct region* region = arena_region_create(arena, amount);
  if (region == NULL)
    return NULL;

  arena->end->next = region;
  arena->end = region;

  region->position = amount;

  return region;
}
