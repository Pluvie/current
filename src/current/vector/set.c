bool vector_set (
    struct vector* vector,
    u64 position,
    void* value
)
{
  struct vector_element* element = vector_element_get(vector, position);

  if (element == NULL)
    return false;

  vector_element_set(vector, element, value);
  return true;
}
