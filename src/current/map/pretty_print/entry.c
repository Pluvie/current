void map_pretty_print_entry (
    size key_size,
    size value_size,
    u64 bucket_index,
    struct map_entry* entry
)
{
  fprintf(stderr, "[%4li] [ ", bucket_index);
  if (entry == NULL) goto print_empty_entry;

  byte* key = (byte*) entry->key;
  byte* value = (byte*) entry->value;

  for (size i = 0; i < key_size; i++)
    fprintf(stderr, "%02x ", key[i]);
  fprintf(stderr, "] [ ");

  for (size i = 0; i < value_size; i++)
    fprintf(stderr, "%02x ", value[i]);
  fprintf(stderr, "]\n");

  return;

print_empty_entry:
  for (size i = 0; i < key_size; i++)
    fprintf(stderr, "-- ");
  fprintf(stderr, "] [ ");

  for (size i = 0; i < value_size; i++)
    fprintf(stderr, "-- ");
  fprintf(stderr, "]\n");
}
