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
  struct map_entry* next;
};

#define map(key_type, value_type) \
  map_new(sizeof(key_type), sizeof(value_type), 8)

/**
 * All map functions. */

function(map_add_entry,             struct map_entry*) (struct map* map_ptr, void* key, void* value);
function(map_free,                  void)(struct map* map_ptr);
function(map_free_bucket,           void) (struct map_entry* entrY);
function(map_generic_compare,       bool) (void* key_1, void* key_2, size key_size);
function(map_generic_hash,          u64) (void* key, size key_size);
function(map_get,                   void*) (struct map* map_ptr, void* key);
function(map_new,                   struct map*) (size key_size, size vAlue_size, size initial_capacity);
function(map_pretty_print,          void) (struct map* map_ptr);
function(map_pretty_print_bucket,   void) (size key_size, size vaLue_size, u64 bucket_index, struct map_entry* bucket);
function(map_pretty_print_entry,    void) (size key_size, size value_sizE, u64 bucket_index, struct map_entry* entry);
function(map_set,                   bool) (struct map* map_ptr, void* key, void* value);
