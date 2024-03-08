struct region* arena_region_create (
    struct arena* arena,
    u64 amount
)
/**
 * Allocates a new region, with given *amount* of data, in the arena. */
{
  void* memory = calloc(1, sizeof(struct region) + amount);
  if (memory == NULL)
    return NULL;

  struct region* region = (struct region*) memory;
  byte* data = (byte*) (region + 1);

  region->data = data;
  region->capacity = amount;
  region->next = NULL;

  arena->number_of_allocs++;
  arena->number_of_regions++;
  arena->total_capacity += region->capacity;

  return region;
}
