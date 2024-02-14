void* arena_malloc (
    struct arena* arena,
    u64 amount
)
/**
 * This function shall allocate new *amount* of bytes in the arena. */
{
  if (arena == NULL)
    return malloc(amount);

  if (arena->begin == NULL)
    return NULL;

  struct region* last_region = arena->end;
  /* If there is enough space in the last region, allocate the provided *amount* there.
   * Otherwise, create a new region, with *amount* bytes of capacity. */
  if (last_region->position + amount <= last_region->capacity)
    goto allocate_on_last_region;
  else
    goto create_next_region;

allocate_on_last_region:
  byte* data = last_region->data + last_region->position;
  last_region->position += amount;
  arena->number_of_allocs++;
  return data;

create_next_region:
  struct region* next = arena_region_next(arena, amount);
  if (next == NULL) 
    return NULL;

  return next->data;
}
