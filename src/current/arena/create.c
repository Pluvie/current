void* arena_create (
    struct arena* arena,
    u64 capacity
)
/**
 * This function shall allocate the begin region of an arena, with the provided
 * *capacity*. */
{
  struct region* region = arena_region_create(arena, capacity);
  if (region == NULL)
    return NULL;

  byte* data = region->data;

  arena->begin = region;
  arena->end = region;
  arena->total_capacity = capacity;

  region->data = data;
  region->capacity = capacity;

  return data;
}
