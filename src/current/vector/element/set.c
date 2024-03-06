void vector_element_set (
    struct vector* vector,
    struct vector_element* element,
    void* value
)
{
  if (element->used)
    goto do_not_copy;

  if (vector->flags & Vector_Flag__Copy_Elements)
    goto do_copy;

do_not_copy:
  element->value = value;
  return;

do_copy:
  size element_size = vector->element_size;
  void* value_copy = arena_calloc(vector->arena, 1, element_size);
  memcpy(value_copy, value, element_size);
  element->value = value_copy;
  return;
}
