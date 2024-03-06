bool vector_get_for_each (
    struct vector* vector,
    u64 position,
    void** value_location
)
{
  struct vector_element* element = vector_element_get(vector, position);

  if (element == NULL)
    return false;

  *value_location = element->value;

  return true;
}
