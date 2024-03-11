void vector_pretty_print (
    struct vector* vector
)
/**
 * This function shall pretty print the vector, showing all its elements.
 *
 * For each element, this function shall print the bytes of its value. */
{
  byte* element;
  size element_size = vector->element_size;
  fprintf(stderr, "\n");

  for (u64 i = 0; i < vector->capacity; i++) {
    fprintf(stderr, "[%4li] [ ", i);

    if (vector->flags & Vector_Flag__Copy_Elements) {
      element = (byte*) vector->elements + (i * element_size);
      for (size i = 0; i < element_size; i++)
        fprintf(stderr, "%02x ", element[i]);
      fprintf(stderr, "]\n");

    } else {
      element = ((void**) vector->elements)[i];
      fprintf(stderr, "%p ]\n", element);
      //element = ((void**) vector->elements)[i];
      //if (element != NULL) {
      //  for (size i = 0; i < element_size; i++)
      //    fprintf(stderr, "%02x ", ((byte*) element)[i]);
      //  fprintf(stderr, "]\n");
      //} else {
      //  for (size i = 0; i < element_size; i++)
      //    fprintf(stderr, "-- ");
      //  fprintf(stderr, "]\n");
      //}
    }
  }
}
