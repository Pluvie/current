struct region* arena_region_next (
    struct arena* arena,
    u64 amount
)
/**
 * Allocates the next region, with given *capacity* of data, in the arena. */
{
  u64 capacity = amount < ARENA_REGION_MIN_CAPACITY
    ? ARENA_REGION_MIN_CAPACITY
    : amount;

  void* memory = malloc(sizeof(struct region) + capacity);
  if (memory == NULL)
    return NULL;

  struct region* region = (struct region*) memory;
  byte* data = (byte*) (region + 1);

  region->data = data;
  region->capacity = capacity;
  region->position = amount;
  region->next = NULL;

  arena->end->next = region;
  arena->end = region;

  arena->number_of_allocs++;
  arena->number_of_regions++;
  arena->total_size += region->capacity;

  return region;
}
