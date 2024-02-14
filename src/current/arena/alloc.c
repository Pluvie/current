void* arena_alloc (
    struct arena* arena,
    u64 capacity
)
/**
 * This function shall allocate the begin region of an arena, with the provided
 * *capacity*. */
{
  void* memory = calloc(1, sizeof(struct region) + capacity);
  if (memory == NULL)
    return NULL;

  struct region* region = (struct region*) (memory);
  byte* data = (byte*) (region + 1);

  arena->begin = region;
  arena->end = region;
  arena->total_capacity = capacity;

  region->data = data;
  region->capacity = capacity;

  return data;
}
