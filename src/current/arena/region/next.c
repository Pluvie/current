struct region* arena_region_next (
    struct arena* arena,
    u64 amount
)
/**
 * Allocates the next region, with given *amount* of data, in the arena. */
{
  void* memory = malloc(sizeof(struct region) + amount);
  if (memory == NULL)
    return NULL;

  struct region* region = (struct region*) memory;
  byte* data = (byte*) (region + 1);

  region->data = data;
  region->capacity = amount;
  region->position = amount;
  region->next = NULL;

  arena->end->next = region;
  arena->end = region;

  arena->number_of_allocs++;
  arena->number_of_regions++;
  arena->total_capacity += region->capacity;

  return region;
}
