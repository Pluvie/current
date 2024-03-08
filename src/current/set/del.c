void* set_del (
    struct set* set,
    void* element
)
/**
 * This function shall remove the provided *element* from the set. */
{
  void* deleted_element = map_del(&(set->elements), element);
  set->length = set->elements.length;
  return deleted_element;
}
