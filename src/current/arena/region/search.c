struct region* arena_region_search (
    struct arena* arena,
    void* memptr
)
/**
 * This function shall search the given *memptr* in all the regions of the arena,
 * by looking at its address.
 *
 * If the pointer is found, the function returns the region containing such pointer.
 * If not, the function shall return `NULL`. */
{
  struct region* current = arena->begin;
  void* range[2] = { 0 };

  do {
    range[0] = current->data;
    range[1] = current->data + current->capacity;

    if (memptr >= range[0] && memptr <= range[1])
      return current;

    current = current->next;
  } while (current != NULL);

  return NULL;
}
