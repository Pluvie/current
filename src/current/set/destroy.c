void set_destroy (
    Set* set
)
/**
 * This function shall free the memory used by the set and all its entries. */
{
  map_destroy(&(set->elements));
}
