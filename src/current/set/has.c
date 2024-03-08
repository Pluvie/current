bool set_has (
    struct set* set,
    void* element
)
/**
 * This function shall determine whether the provided *element* is in the set. */
{
  return map_has(&(set->elements), element);
}
