void vector_push (
    Vector* vector,
    void* element
)
{
  u64 position = vector->length;
  if (position + 1 >= vector->capacity)
    vector_resize(vector);

  vector->length++;
  vector_set(vector, position, element);
}
