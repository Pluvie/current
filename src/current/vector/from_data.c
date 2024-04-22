bool vector_from_data (
    Vector* vector,
    void* data,
    u64 data_length
)
/**
 * This function shall create a read only vector using the provided *data* and its
 * length.
 *
 * The length must be an exact multiple of the vector *element_size*, otherwise
 * `false` shall be returned and the vector must be considered invalid.
 *
 * On success, the function shall return `true`. */
{
  u64 vector_length = data_length / vector->element_size;
  if (vector->element_size * vector_length != data_length)
    return false;

  vector->elements = data;
  vector->length = vector_length;
  vector->capacity = vector_length;
  vector->flags |= VECTOR_FLAG__READ_ONLY;
  vector->flags |= VECTOR_FLAG__COPY_ELEMENTS;

  return true;
}
