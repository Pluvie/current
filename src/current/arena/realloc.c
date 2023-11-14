void* arena_realloc (
    arena* current,
    void* memory,
    int64 size
)
{
  void* range[2] = { 0 };
  void* new_memory = NULL;
  int64 max_copy_size = 0;
  arena* last = current;

  do {
    range[0] = current->data;
    range[1] = current->data + current->size;

    if (memory >= range[0] && memory <= range[1]) {
      max_copy_size = range[1] - memory;
      if (size < max_copy_size) max_copy_size = size;
    }

    if (current->pos + size <= current->size) {
      new_memory = current->data + current->pos;
      current->pos += size;
      memmove(new_memory, memory, max_copy_size);
      return new_memory;
    }

    last = current;
    current = current->next;
  } while(current != NULL);

  arena* next = arena_init(size);
  last->next = next;
  next->pos += size;
  new_memory = next->data;
  memmove(new_memory, memory, max_copy_size);
  return new_memory;
}
