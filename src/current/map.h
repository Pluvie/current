/**
                          .___  ___.      ___      .______   
                          |   \/   |     /   \     |   _  \  
                          |  \  /  |    /  ^  \    |  |_)  | 
                          |  |\/|  |   /  /_\  \   |   ___/  
                          |  |  |  |  /  _____  \  |  |      
                          |__|  |__| /__/     \__\ | _|      
                                                                                      **/

/**
 * Defines the possible key statuses of the map. */
enum __map_key_status {
  __Map__Key_Status__Not_Used = 0,
  __Map__Key_Status__Used     = 1,
  __Map__Key_Status__Deleted  = 2,
};

/**
 * Defines the result output of the function #__map_find. */
enum __map_find_output {
  __Map_Find_Default  = 0,
  __Map_Find_Offset   = 1,
};

/**
 * Defines the operation mode of the function #__map_use. */
enum __map_use_opmode {
  __Map_Use_Default   = 0,
  __Map_Use_Rehashing = 1,
};

/**
 * Defines a map key, which holds the address where the actual key content is in memory,
 * the key hash integer value and other key metadata. */
struct __map_key {
  void*   address;
  uint64  hash;
  enum __map_key_status status;
};

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
  struct __map_key*   keys;
  struct __map_config config;
};

/**
 * Defines the memory size of a map, giving the resulting *capacity* and the total
 * memory *footprint* in bytes of the map. */
struct __map_memsize {
  uint64  capacity;
  uint64  footprint;
};

/**
 * Minimum map capacity. */
#define MAP_MIN_CAPACITY 8

/**
 * Defines the `map` type. */
#define map(key_type, value_type)                                                       \
  value_type*

/**
 * Map functions and macros. */
#include "map/functions.h"
#include "map/macros.h"
