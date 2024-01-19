/**
 * Defines the map configuration options. */
struct __map_config {
  uint64  initial_capacity;
  uint16  key_size;
  uint16  value_size;
  uint64  (*hash)(void*);
  bool    (*compare)(void*, void*);
  bool    copy_keys;
  uint16  key_copy_size;
  void    (*key_copy_func)(void*, void*, uint64);
  uint16  (*key_copy_size_func)(void*);
  bool    copy_values;
  uint16  value_copy_size;
  void    (*value_copy_func)(void*, void*, uint64);
  uint16  (*value_copy_size_func)(void*);
  struct arena* arena;
};

/**
 * Main map data, held just before the map pointer.
 * It contains all the metadata needed for the map to operate.
 *
 * This will be referenced by the macro #map_fat_ptr, which will move the map pointer
 * behind by `sizeof(struct __map_fat_ptr) + sizeof(T)` bytes, where `T` is the map
 * value type.
 *
 * This technique is called "Fat Pointer", [see more here](
 * https://libcello.org/learn/a-fat-pointer-library). */
struct __map_fat_ptr {
  uint64  length;
  uint64  capacity;
  byte*   keys;
  uint64* hashes;
  enum __map_key_status* statuses;
  struct __map_config config;
};

/**
 * Defines the memory size of a map, giving the resulting *capacity* and the total
 * memory *footprint* in bytes of the map. */
struct __map_memsize {
  uint64  capacity;
  uint64  footprint;
};
