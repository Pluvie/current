struct arena* arena_init (
    u64 capacity
)
/**
 * This function shall initialize an arena of given *capacity*. */
{
  capacity = capacity < ARENA_REGION_MIN_CAPACITY
    ? ARENA_REGION_MIN_CAPACITY
    : capacity;

  void* memory = calloc(1, sizeof(struct arena) + sizeof(struct region) + capacity);
  if (memory == NULL)
    return NULL;

  struct arena* arena = (struct arena*) memory;
  struct region* region = (struct region*) (arena + 1);
  byte* data = (byte*) (region + 1);

  arena->begin = region;
  arena->end = region;
  arena->total_size = capacity;
  region->data = data;
  region->capacity = capacity;

  return arena;
}
