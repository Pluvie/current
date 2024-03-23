Region* arena_region_next (
    Arena* arena,
    u64 amount
)
/**
 * Allocates the next region, with given *amount* of data, in the arena, and marks
 * its position to the *amount* -- which means that the region is full. */
{
  Region* region = arena_region_create(arena, amount);
  if (region == NULL)
    return NULL;

  arena->end->next = region;
  arena->end = region;

  region->position = amount;

  return region;
}
