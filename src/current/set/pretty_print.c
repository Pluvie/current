void set_pretty_print (
    struct set* set
)
/**
 * This function shall pretty print the set, showing all elements in the set.
 *
 * For each entry, this function shall print the bytes of its key and value. */
{
  struct map* elements = &(set->elements);
  struct map_entry* entry = elements->entries;
  for (u64 i = 0; i < elements->capacity; i++, entry++)
    set_pretty_print_entry(elements->key_size, i, entry);
}
