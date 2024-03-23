void set_pretty_print (
    Set* set
)
/**
 * This function shall pretty print the set, showing all elements in the set.
 *
 * For each entry, this function shall print the bytes of its key and value. */
{
  Map* elements = &(set->elements);
  MapEntry* entry = elements->entries;
  for (u64 i = 0; i < elements->capacity; i++, entry++)
    set_pretty_print_entry(elements->key_size, i, entry);
}
