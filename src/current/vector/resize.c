/**
 * This function will appropriately calculate the new vector capacity when it
 * has to be resized. */
void* __vector_resize (
  struct __vector_data* vector_data
)
{
  uint32 capacity = vector_data->capacity;
  uint32 block = vector_data->block;

  uint32 old_capacity = capacity;
  uint32 old_size = old_capacity * block;
  capacity <<= 1;

  vector_data->capacity = capacity;
  vector_data = realloc(vector_data, vector_datasize + (capacity * block));
  memset(((byte*) (vector_data + 1)) + old_size, '\0', old_size);
  return (vector_data + 1);
}
