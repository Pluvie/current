void arena_destroy (
    Arena* arena
)
{
  Region* current = arena->begin;
  Region* next = arena->begin;

  if (current == NULL)
    return;

  do {
    next = current->next;
    free(current);
    current = next;
  } while(current != NULL);
}
