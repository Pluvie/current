struct region* arena_region_next (
    struct arena* arena,
    u64 capacity
)
/**
 * Allocates the next region, with given *capacity* of data, in the arena. */
{
  capacity = capacity < ARENA_REGION_MIN_CAPACITY
    ? ARENA_REGION_MIN_CAPACITY
    : capacity;

  void* memory = malloc(sizeof(struct region) + capacity);
  if (memory == NULL)
    return NULL;

  struct region* region = (struct region*) memory;
  byte* data = (byte*) (region + 1);

  region->data = data;
  region->capacity = capacity;
  region->position = capacity;
  region->next = NULL;

  arena->end->next = region;
  arena->end = region;

  return region;
}
