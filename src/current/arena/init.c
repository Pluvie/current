struct arena* arena_init (
    int64 size
)
/**
 * This function shall initialize an arena of given *size*. */
{
  void* memory = malloc(sizeof(struct arena) + sizeof(struct region) + size);
  if (memory == NULL)
    return NULL;

  struct arena* arena = (struct arena*) memory;
  struct region* region = (struct region*) (arena + 1);
  byte* data = (byte*) (region + 1);

  arena->begin = region;
  arena->end = region;
  region->data = data;
  region->size = size;
  region->pos = 0;
  region->next = NULL;

  return arena;
}
