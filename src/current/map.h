/**
                          .___  ___.      ___      .______   
                          |   \/   |     /   \     |   _  \  
                          |  \  /  |    /  ^  \    |  |_)  | 
                          |  |\/|  |   /  /_\  \   |   ___/  
                          |  |  |  |  /  _____  \  |  |      
                          |__|  |__| /__/     \__\ | _|      
                                                                                      **/

/**
 * Defines the `map` struct. */
struct map {
  u64   length;
  u64   capacity;
  size  key_size;
  size  value_size;
  u64   (*hash)(void*, size);
  bool  (*compare)(void*, void*, size);
  struct map_entry** buckets;
};

struct map_entry {
  void* key;
  void* value;
  u64   hash;
  struct map_entry* next;
};

#define map(key_type, value_type) \
  map_new(sizeof(key_type), sizeof(value_type), 8)

/**
 * All map functions. */

function(map_add_entry,           void         )(struct map*, void*, void*, struct map_entry**);
function(map_free,                void         )(struct map*);
function(map_free_bucket,         void         )(struct map_entry*);
function(map_generic_compare,     bool         )(void*, void*, size);
function(map_generic_hash,        u64          )(void*, size);
function(map_get,                 void*        )(struct map*, void*);
function(map_new,                 struct map*  )(size, size, size);
function(map_pretty_print,        void         )(struct map*);
function(map_pretty_print_bucket, void         )(size, size, u64, struct map_entry*);
function(map_pretty_print_entry,  void         )(size, size, u64, struct map_entry*);
function(map_rehash,              void         )(struct map*);
function(map_set,                 void*        )(struct map*, void*, void*);
function(map_set_on_buckets,      void*        )(struct map*, void*, void*, u64, struct map_entry**);
