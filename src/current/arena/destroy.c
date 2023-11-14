void arena_destroy (
    arena* current
)
{
  arena* next = current;
  arena* last = current;

  do {
    next = last->next;
    free(last->data);
    free(last);
    last = next;
  } while(next != NULL);
}
