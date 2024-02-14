void arena_destroy (
    struct arena* arena
)
{
  struct region* current = arena->begin;
  struct region* next = arena->begin;

  if (current == NULL)
    return;

  do {
    next = current->next;
    free(current);
    current = next;
  } while(current != NULL);
}
