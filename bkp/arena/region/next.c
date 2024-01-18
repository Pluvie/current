struct region* arena_region_next (
    struct arena* arena,
    int64 size
)
/**
 * Allocates the next region, with *size* amount of data, in the arena. */
{
  size = size < ARENA_REGION_MIN_SIZE ? ARENA_REGION_MIN_SIZE : size;

  void* memory = malloc(sizeof(struct region) + size);
  if (memory == NULL)
    return NULL;

  struct region* region = (struct region*) memory;
  byte* data = (byte*) (region + 1);

  region->data = data;
  region->size = size;
  region->pos = size;
  region->next = NULL;

  arena->end->next = region;
  arena->end = region;

  return region;
}
