/**
                          .___  ___.      ___      .______   
                          |   \/   |     /   \     |   _  \  
                          |  \  /  |    /  ^  \    |  |_)  | 
                          |  |\/|  |   /  /_\  \   |   ___/  
                          |  |  |  |  /  _____  \  |  |      
                          |__|  |__| /__/     \__\ | _|      
                                                                                      **/

/**
 * Defines the `map_init` macro to initialize a new map with the given *key_type* and
 * *value_type*. */
#define map_init(key_type, value_type)  \
  { .key_size = sizeof(key_type),       \
    .value_size = sizeof(value_type) }

/**
 * Defines the defaul initial capacity of a map, if not specified by the programmer. */
#define MAP_DEFAULT_CAPACITY      8

/**
 * Defines the maximum load factor of a map, after which a rehash is triggered. */
#define MAP_MAXIMUM_LOAD_FACTOR   0.7

/**
 * Defines the `map` struct.
 * A map is an unordered array of pairs { key, value } that can be retrieved in constant
 * time.
 *
 * This is achieved by using a hash function on the key, and using the resulting number
 * as the index where to store the pair in the pairs array. If two different keys should
 * result in the same hash, they will be addressed by scanning the entries array until
 * a free entry is found. This technique is called "open addressing". */
struct map {
  u64   length;
  u64   capacity;
  size  key_size;
  size  value_size;
  u32   flags;
  u64   probe_limit;
  struct arena* arena;
  struct map_entry* entries;
};

/**
 * Defines the `map_entry` struct, which is a single pair { key, value } in the map.
 * All entries are stored sequentially one after the other. Collision will be handled
 * using open addressing with linear probing. */
struct map_entry {
  void* key;
  void* value;
  u64   hash;
//  u64   distance;
};

/**
 * Defines all the flags used to tweak and configure the map behaviour. */
enum map_flags {
  Map_Flag__None        = 0,
  Map_Flag__Copy_Keys   = 1 << 0,
  Map_Flag__Copy_Values = 1 << 1,
};

/**
 * Defines a macro to enable the provided flag in the map. */
#define map_flag_enable(map, flag) \
  (map)->flags |= (flag)

/**
 * Defines a macro to disable the provided flag in the map. */
#define map_flag_disable(map, flag) \
  (map)->flags &= ~(flag)

/**
 * All map function definitions. */
function( map_capped_hash,          u64               )(  i64, u64                                );
function( map_compare,              bool              )(  void*, void*, size                      );
function( map_create,               void              )(  struct map*                             );
function( map_del,                  void*             )(  struct map*, void*                      );
function( map_destroy,              void              )(  struct map*                             );
function( map_destroy_entry,        void              )(  struct map*, struct map_entry*          );
function( map_get,                  void*             )(  struct map*, void*                      );
function( map_get_entry,            struct map_entry* )(  struct map*, void*                      );
function( map_has,                  bool              )(  struct map*, void*                      );
function( map_hash,                 u64               )(  void*, size                             );
function( map_pretty_print,         void              )(  struct map*                             );
function( map_pretty_print_entry,   void              )(  size, size, u64, struct map_entry*      );
function( map_rehash,               void              )(  struct map*                             );
function( map_set,                  void*             )(  struct map*, void*, void*               );
function( map_set_entry,            void*             )(  struct map*, struct map_entry*          );
