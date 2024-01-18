void map_pretty_print_bucket (
    size key_size,
    size value_size,
    u64 bucket_index,
    struct map_entry* bucket
)
/**
 * Pretty prints a bucket of the map. */
{
  map_pretty_print_entry(key_size, value_size, bucket_index, bucket);
  if (bucket != NULL && bucket->next != NULL)
    map_pretty_print_bucket(key_size, value_size, bucket_index, bucket->next);
}
