void set_create (
    struct set* set
)
/**
 * This function shall allocate the provided set. */
{
  struct map* elements = &(set->elements);
  elements->capacity = set->capacity;
  map_create(elements);
  set->capacity = elements->capacity;
}
