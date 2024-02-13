/**
                          .___  ___.      ___      .______   
                          |   \/   |     /   \     |   _  \  
                          |  \  /  |    /  ^  \    |  |_)  | 
                          |  |\/|  |   /  /_\  \   |   ___/  
                          |  |  |  |  /  _____  \  |  |      
                          |__|  |__| /__/     \__\ | _|      
                                                                                      **/

/**
 * Defines the `map` macro to declare and create a new map with the given *key_type*
 * and *value_type*. */
#define map(key_type, value_type)     \
  { .key_size = sizeof(key_type),     \
    .value_size = sizeof(value_type), \
    .hash = map_generic_hash,         \
    .compare = map_generic_compare }

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
 * result in the same hash, they will be stored in the same index of the pairs array
 * using a linked list: this is why the pairs array is called "buckets". */
struct map {
  u64   length;
  u64   capacity;
  size  key_size;
  size  value_size;
  u64   (*hash)(void*, size);
  bool  (*compare)(void*, void*, size);
  u32   flags;
  struct arena* arena;
  struct map_entry** buckets;
};

/**
 * Defines the `map_entry` struct, which is a single pair { key, value } in the map.
 * All entries are grouped in buckets, where they share the same (capped) hash.
 * A bucket is just a linked list of entries. */
struct map_entry {
  void* key;
  void* value;
  u64   hash;
  struct map_entry* next;
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
#define map_flag_enable(map_ptr, flag) \
  (map_ptr)->flags |= (flag)

/**
 * Defines a macro to disable the provided flag in the map. */
#define map_flag_disable(map_ptr, flag) \
  (map_ptr)->flags &= ~(flag)

/**
 * All map function definitions. */
function( map_alloc,                void              )(  struct map*                                           );
function( map_del,                  void*             )(  struct map*, void*                                    );
function( map_entry_add,            void              )(  struct map*, void*, void*, u64, struct map_entry**    );
function( map_entry_key_set,        void              )(  struct map*, struct map_entry*, void*                 );
function( map_entry_value_set,      void              )(  struct map*, struct map_entry*, void*                 );
function( map_free,                 void              )(  struct map*                                           );
function( map_free_bucket,          void              )(  struct map*, struct map_entry*                        );
function( map_generic_compare,      bool              )(  void*, void*, size                                    );
function( map_generic_hash,         u64               )(  void*, size                                           );
function( map_get,                  void*             )(  struct map*, void*                                    );
function( map_get_entry,            struct map_entry* )(  struct map*, void*                                    );
function( map_has,                  bool              )(  struct map*, void*                                    );
function( map_pretty_print,         void              )(  struct map*                                           );
function( map_pretty_print_bucket,  void              )(  size, size, u64, struct map_entry*                    );
function( map_pretty_print_entry,   void              )(  size, size, u64, struct map_entry*                    );
function( map_rehash,               void              )(  struct map*                                           );
function( map_set,                  void*             )(  struct map*, void*, void*                             );
function( map_set_with_buckets,     void*             )(  struct map*, void*, void*, u64, struct map_entry**    );
