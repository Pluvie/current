/**
                          .___  ___.      ___      .______   
                          |   \/   |     /   \     |   _  \  
                          |  \  /  |    /  ^  \    |  |_)  | 
                          |  |\/|  |   /  /_\  \   |   ___/  
                          |  |  |  |  /  _____  \  |  |      
                          |__|  |__| /__/     \__\ | _|      
                                                                                      **/


/**
 * # Map
 *
 * A map is an unordered array of pairs { key, value } that can be retrieved in constant
 * time.
 *
 * This is achieved by using a hash function on the key, and using the resulting number
 * as the index where to store the pair in the pairs array. If two different keys would
 * result in the same hash, then a collision will happen. This collision shall be
 * addressed by scanning the entries array until a free entry is found.
 * This technique is called "open addressing". */


enum map_flags;
typedef enum map_flags {
  MAP_FLAG__NONE          = 0,
  MAP_FLAG__FIXED_LOOKUP  = 1 << 0,
  MAP_FLAG__COPY_KEYS     = 1 << 1,
  MAP_FLAG__COPY_VALUES   = 1 << 2,
} MapFlags;


struct map_entry;
typedef struct map_entry {
  void* key;
  void* value;
  u64 hash;
} MapEntry;


struct map;
typedef struct map {
  u64 length;
  u64 capacity;
  size key_size;
  size value_size;
  u64 probe_limit;
  Arena* arena;
  MapFlags flags;
  MapEntry* entries;
} Map;


/**
 * Defines the defaul initial capacity of a map, if not specified by the programmer. */
#define MAP_DEFAULT_CAPACITY      8

/**
 * Defines the maximum load factor of a map, after which a rehash is triggered. */
#define MAP_MAXIMUM_LOAD_FACTOR   0.7

/**
 * Defines the `map_init` macro to initialize a new map with the given *key_type* and
 * *value_type*. */
#define map_init(key_type, value_type)  \
  { .key_size = sizeof(key_type),       \
    .value_size = sizeof(value_type) }

/**
 * Defines a macro to enable the provided flag in the map. */
#define map_flag_enable(map, flag) \
  (map)->flags |= (flag)

/**
 * Defines a macro to disable the provided flag in the map. */
#define map_flag_disable(map, flag) \
  (map)->flags &= ~(flag)

/**
 * Defines a macro to iterate all the entries in the map. */
#define map_each(map, key, value) \
  (u64 i = 0; i < (map)->capacity + (map)->probe_limit; i++) \
    if (key = (map)->entries[i].key, value = (map)->entries[i].value, key != NULL)


/**
 * All map function definitions. */

u64           map_capped_hash         ( i64, u64 );
bool          map_compare             ( void*, void*, size );
void          map_create              ( Map* );
void*         map_del                 ( Map*, void* );
void          map_destroy             ( Map* );
void*         map_entry_add           ( Map*, MapEntry*, MapEntry* );
void          map_entry_destroy       ( Map*, MapEntry* );
MapEntry*     map_entry_get           ( Map*, void* );
void*         map_entry_set           ( Map*, MapEntry* );
void*         map_get                 ( Map*, void* );
bool          map_has                 ( Map*, void* );
u64           map_hash                ( void*, size );
void          map_pretty_print        ( Map* );
void          map_pretty_print_entry  ( size, size, u64, MapEntry* );
void          map_rehash              ( Map* );
void*         map_set                 ( Map*, void*, void* );
