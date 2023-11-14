arena* arena_init (
    int64 size
)
{
  arena* current = malloc(sizeof(arena));
  if (!current) return NULL;

  current->pos = 0;
  current->next = NULL;
  current->data = malloc(size * sizeof(byte));
  current->size = size;
  if (!current->data) {
    free(current);
    return NULL;
  }

  return current;
}
