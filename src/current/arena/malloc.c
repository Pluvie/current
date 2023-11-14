void* arena_malloc (
    arena* current,
    int64 size
)
{
  arena* last = current;

  do {
    if (current->pos + size <= current->size) {
      current->pos += size;
      return current->data + (current->pos - size);
    }

    last = current;
    current = current->next;
  } while(current != NULL);

  arena* next = arena_init(size);
  last->next = next;
  next->pos += size;
  return next->data;
}
