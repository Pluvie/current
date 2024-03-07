void vector_pop (
    struct vector* vector
)
{
  if (vector->length == 0)
    return;

  vector->length--;
  u64 position = vector->length;
  struct vector_element* element = vector->elements + position;

  if (vector->flags & Vector_Flag__Copy_Elements)
    free(element->value);

  element->value = NULL;
}
