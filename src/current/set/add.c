void* set_add (
    struct set* set,
    void* element
)
/**
 * This function shall add the provided *element* to the set. */
{
  map_set(&(set->elements), element, element);
  set->length = set->elements.length;
  return element;
}
