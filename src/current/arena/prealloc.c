void* arena_prealloc (
    Arena* arena,
    u64 amount
)
/**
 * This function shall reserve *amount* of bytes in the arena.
 * If the amount is already available, nothing is done. Otherwise, a new region with
 * the requested amount shall be created. */
{
  if (arena == NULL)
    return NULL;

  Region* last_region = arena->end;
  i64 available_space = last_region->capacity - last_region->position;
  if (available_space >= amount)
    return last_region->data + last_region->position;

allocate_new_region:
  Region* region = arena_region_create(arena, amount);
  if (region == NULL)
    return NULL;

  arena->end->next = region;
  arena->end = region;

  return region->data;
}
