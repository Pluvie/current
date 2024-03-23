void* vector_get (
    Vector* vector,
    u64 position
)
{
  if (position >= vector->length)
    return NULL;

  if (vector->flags & VECTOR_FLAG__COPY_ELEMENTS)
    return (byte*) vector->elements + (position * vector->element_size);
  else
    return ((void**) vector->elements)[position];
}
