struct __map_memsize __map_calc_memsize (
    uint16 key_size,
    uint16 value_size,
    uint64 initial_capacity
)
/**
 * This function shall calculate the memory footprint of a map with given *key_size*,
 * *value_size*, and *initial_capacity*. */
{
  uint64 capacity = next_pow2(initial_capacity);
  capacity = capacity < MAP_MIN_CAPACITY ? MAP_MIN_CAPACITY : capacity;

  /* Doubles the map capacity if the initial capacity was already under load. */
  if (((dec64) initial_capacity / (dec64) capacity) >= 0.7)
    capacity *= 2;

  uint64 footprint =
    sizeof(struct __map_fat_ptr) +          /* Map fat pointer data. */
    value_size +                            /* Zero value. */
    (capacity * value_size) +               /* Values. */
    (capacity * sizeof(struct __map_key));  /* Keys. */

  struct __map_memsize memsize = {
    .capacity = capacity,
    .footprint = footprint
  };

  return memsize;
}
