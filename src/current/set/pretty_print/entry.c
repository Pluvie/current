void set_pretty_print_entry (
    size element_size,
    u64 entry_index,
    MapEntry* entry
)
/**
 * Pretty prints an element of the set. */
{
  fprintf(stderr, "[%4li] [ ", entry_index);
  if (entry->key == NULL) goto print_empty_entry;

  byte* key = (byte*) entry->key;

  for (size i = 0; i < element_size; i++)
    fprintf(stderr, "%02x ", key[i]);
  fprintf(stderr, "]\n");

  return;

print_empty_entry:
  for (size i = 0; i < element_size; i++)
    fprintf(stderr, "-- ");
  fprintf(stderr, "]\n");
}
