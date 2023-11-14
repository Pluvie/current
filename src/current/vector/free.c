void __vector_free (
  struct __vector_fp* vector_fp
)
/**
 * Frees all memory used by the vector and its metadata. */
{
  if (vector_fp->allocator != NULL)
    return;

  free(vector_fp);
}
