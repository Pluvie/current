void* arena_create (
    Arena* arena,
    u64 capacity
)
/**
 * This function shall allocate the begin region of an arena, with the provided
 * *capacity*. */
{
  Region* region = arena_region_create(arena, capacity);
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
