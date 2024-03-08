void set_destroy (
    struct set* set
)
/**
 * This function shall free the memory used by the set and all its entries. */
{
  map_destroy(&(set->elements));
}
