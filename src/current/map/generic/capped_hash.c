inline u64 map_capped_hash (
    i64 hash,
    u64 capacity
)
/**
 * This inlined function will calculate the capped hash given the map *capacity*.
 *
 * Since the capacity is a power of 2, we can optimize this function by doing just
 * a bitmask with the capacity in order to avoid the expensive modulo operation. */
{
  return (hash & (capacity - 1));
}
