void* __vector_resize (
  struct __vector_fp* vector_fp
)
/**
 * This function will appropriately calculate the new vector capacity when it
 * has to be resized. */
{
  struct arena* arena = vector_fp->arena;
  uint64 capacity = vector_fp->capacity;
  uint64 block = vector_fp->block;

  uint64 old_capacity = capacity;
  uint64 old_size = old_capacity * block;
  capacity <<= 1;

  vector_fp->capacity = capacity;
  vector_fp = (arena == NULL)
    ? realloc(vector_fp, vector_fp_size + (capacity * block))
    : arena_realloc(arena, vector_fp, vector_fp_size + (capacity * block));

  memset(((byte*) (vector_fp + 1)) + old_size, '\0', old_size);
  return (vector_fp + 1);
}
