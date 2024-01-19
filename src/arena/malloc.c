void* arena_malloc (
    struct arena* arena,
    u64 amount
)
/**
 * This function shall allocate new *amount* of bytes in the arena. */
{
  if (arena == NULL)
    return malloc(amount);

  struct region* last_region = arena->end;
  if (last_region->position + amount <= last_region->capacity) {
    byte* data = last_region->data + last_region->position;
    last_region->position += amount;
    return data;
  }

  struct region* next = arena_region_next(arena, amount);
  if (next == NULL) 
    return NULL;

  return next->data;
}
