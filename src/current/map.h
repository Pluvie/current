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
 * and *value_type*. The map initial capacity is set as default. */
#define map(key_type, value_type) \
  map_new(sizeof(key_type), sizeof(value_type), MAP_DEFAULT_CAPACITY)

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
  Map_Flag__None                = 0,
  Map_Flag__Integer_Key         = 1 << 0,
  Map_Flag__Do_Not_Copy_Values  = 1 << 1,
};

/**
 * All map function definitions. */
function( map_add_entry,            void          )(  struct map*, void*, void*, u64, struct map_entry**    );
function( map_del,                  void*         )(  struct map*, void*                                    );
function( map_free,                 void          )(  struct map*                                           );
function( map_free_bucket,          void          )(  struct map_entry*                                     );
function( map_generic_compare,      bool          )(  void*, void*, size                                    );
function( map_generic_hash,         u64           )(  void*, size                                           );
function( map_get,                  void*         )(  struct map*, void*                                    );
function( map_new,                  struct map*   )(  size, size, size                                      );
function( map_pretty_print,         void          )(  struct map*                                           );
function( map_pretty_print_bucket,  void          )(  size, size, u64, struct map_entry*                    );
function( map_pretty_print_entry,   void          )(  size, size, u64, struct map_entry*                    );
function( map_rehash,               void          )(  struct map*                                           );
function( map_set,                  void*         )(  struct map*, void*, void*                             );
function( map_set_on_buckets,       void*         )(  struct map*, void*, void*, u64, struct map_entry**    );
