void arena_destroy (
    struct arena* arena
)
{
  struct region* current = arena->begin;
  struct region* next = arena->begin;

  do {
    next = current->next;
    if (current != arena->begin)
      free(current);
    current = next;
  } while(current != NULL);

  free(arena);
}
