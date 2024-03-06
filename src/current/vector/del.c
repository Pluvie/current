void vector_del (
    struct vector* vector,
    u64 position
)
{
  struct vector_element* element = vector_element_get(vector, position);

  if (element == NULL)
    return;

  element->used = false;

  if (vector->flags & Vector_Flag__Copy_Elements)
    free(element->value);
}
