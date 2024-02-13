void arena_alloc (
    struct arena* arena
)
/**
 * This function shall allocate an arena of given *capacity*. */
{
  size capacity = arena->capacity;
  if (capacity < ARENA_REGION_MIN_CAPACITY)
    capacity = ARENA_REGION_MIN_CAPACITY;

  arena->capacity = capacity;

  void* memory = calloc(1, sizeof(struct region) + capacity);
  if (memory == NULL)
    return NULL;

  struct region* region = (struct region*) (memory);
  byte* data = (byte*) (region + 1);

  arena->begin = region;
  arena->end = region;
  arena->total_size = capacity;
  region->data = data;
  region->capacity = capacity;

  return arena;
}
