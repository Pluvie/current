void set_create (
    Set* set
)
/**
 * This function shall allocate the provided set. */
{
  Map* elements = &(set->elements);
  elements->capacity = set->capacity;
  map_create(elements);
  set->capacity = elements->capacity;
}
