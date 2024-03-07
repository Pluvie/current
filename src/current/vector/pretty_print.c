void vector_pretty_print (
    struct vector* vector
)
/**
 * This function shall pretty print the vector, showing all its elements.
 *
 * For each element, this function shall print the bytes of its value. */
{
  struct vector_element* element;
  size element_size = vector->element_size;
  byte* element_value;

  for (u64 i = 0; i < vector->capacity; i++) {
    element = vector->elements + i;
    element_value = (byte*) element->value;
    fprintf(stderr, "[%4li] [", i);

    if (element_value != NULL) {
      fprintf(stderr, "■] [ ");
      for (size i = 0; i < element_size; i++)
        fprintf(stderr, "%02x ", element_value[i]);
      fprintf(stderr, "]\n");
    } else {
      fprintf(stderr, " ] [ ");
      for (size i = 0; i < element_size; i++)
        fprintf(stderr, "-- ");
      fprintf(stderr, "]\n");
    }
  }
}
