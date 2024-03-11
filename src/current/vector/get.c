void* vector_get (
    struct vector* vector,
    u64 position
)
{
  if (position >= vector->length)
    return NULL;

  if (vector->flags & Vector_Flag__Copy_Elements)
    return (byte*) vector->elements + (position * vector->element_size);
  else
    return ((void**) vector->elements)[position];
}
