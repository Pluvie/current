void vector_add (
    struct vector* vector,
    void* element
)
{
  u64 position = vector->length;

  vector->length++;
  if (vector->length >= vector->capacity)
    vector_resize(vector);

  vector_element_set(vector, vector->elements + position, element);
}
