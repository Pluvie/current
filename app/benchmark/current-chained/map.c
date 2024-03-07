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
 * result in the same hash, they will be stored in the same index of the pairs array
 * using a linked list: this is why the pairs array is called "buckets". */
struct map {
  u64   length;
  u64   capacity;
  size  key_size;
  size  value_size;
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
  Map_Flag__Rehashing   = 1 << 0,
  Map_Flag__Copy_Keys   = 1 << 1,
  Map_Flag__Copy_Values = 1 << 2,
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
function( map_create,               void              )(  struct map*                                           );
function( map_capped_hash,          u64               )(  i64, u64                                              );
function( map_compare,              bool              )(  void*, void*, size                                    );
function( map_del,                  void*             )(  struct map*, void*                                    );
function( map_entry_add,            void              )(  struct map*, void*, void*, u64, struct map_entry**    );
function( map_entry_key_set,        void              )(  struct map*, struct map_entry*, void*                 );
function( map_entry_value_set,      void              )(  struct map*, struct map_entry*, void*                 );
function( map_destroy,              void              )(  struct map*                                           );
function( map_destroy_bucket,       void              )(  struct map*, struct map_entry*                        );
function( map_destroy_entry,        void              )(  struct map*, struct map_entry*                        );
function( map_get,                  void*             )(  struct map*, void*                                    );
function( map_get_entry,            struct map_entry* )(  struct map*, void*                                    );
function( map_has,                  bool              )(  struct map*, void*                                    );
function( map_hash,                 u64               )(  void*, size                                           );
function( map_pretty_print,         void              )(  struct map*                                           );
function( map_pretty_print_bucket,  void              )(  size, size, u64, struct map_entry*                    );
function( map_pretty_print_entry,   void              )(  size, size, u64, struct map_entry*                    );
function( map_rehash,               void              )(  struct map*                                           );
function( map_set,                  void*             )(  struct map*, void*, void*                             );
function( map_set_with_buckets,     void*             )(  struct map*, void*, void*, u64, struct map_entry**    );

void map_create (
    struct map* map
)
/**
 * This function shall allocate the provided map. */
{
  size initial_capacity = next_pow2(map->capacity);
  if (initial_capacity < MAP_DEFAULT_CAPACITY)
    initial_capacity = MAP_DEFAULT_CAPACITY;

  struct arena* arena = map->arena;

  if ((initial_capacity > map->capacity) &&
      ((d64) map->capacity / (d64) initial_capacity >= MAP_MAXIMUM_LOAD_FACTOR))
    initial_capacity *= 2;

  map->capacity = initial_capacity;

  if (arena == NULL)
    goto alloc_buckets_only;

  size footprint =
    (initial_capacity * sizeof(struct map_entry*)) +
    (initial_capacity * sizeof(struct map_entry));

  if (map->flags & Map_Flag__Copy_Keys)
    footprint += (initial_capacity * map->key_size);
  if (map->flags & Map_Flag__Copy_Values)
    footprint += (initial_capacity * map->value_size);

  arena_prealloc(arena, footprint);

alloc_buckets_only:
  map->buckets = arena_calloc(arena, initial_capacity, sizeof(struct map_entry*));
}
void* map_del (
    struct map* map,
    void* key
)
/**
 * This function shall delete the *provided* key in the map.
 *
 * If the key is found, its value shall be returned.
 * If not, `NULL` shall be returned. */
{
  if (key == NULL)
    return NULL;

  size key_size = map->key_size;
  u64 hash = map_hash(key, key_size);
  u64 capped_hash = map_capped_hash(hash, map->capacity);
  struct map_entry* entry = map->buckets[capped_hash];
  struct map_entry* previous_entry = NULL;
  void* deleted_value = NULL;

compare_key:
  if (entry == NULL)
    return NULL;
  if (map_compare(entry->key, key, key_size)) {
    deleted_value = entry->value;
    goto delete_entry;
  }

  previous_entry = entry;
  entry = entry->next;
  goto compare_key;

delete_entry:
  if (previous_entry == NULL)
    map->buckets[capped_hash] = entry->next;
  else
    previous_entry->next = entry->next;

  map_destroy_entry(map, entry);
  return deleted_value;
}
void map_destroy (
    struct map* map
)
/**
 * This function shall free the memory used by the map and all its buckets. */
{
  if (map->arena != NULL)
    return;

  for (i64 i = 0; i < map->capacity; i++)
    map_destroy_bucket(map, map->buckets[i]);
  free(map->buckets);
}
void* map_get (
    struct map* map,
    void* key
)
/**
 * This function shall retrieve the value of the provided *key* in the map.
 *
 * If the key is not present in the map, `NULL` shall be returned. */
{
  struct map_entry* entry = map_get_entry(map, key);

  if (entry == NULL)
    return NULL;
  else
    return entry->value;
}
bool map_has (
    struct map* map,
    void* key
)
/**
 * This function shall determine if the provided *key* is present in the map.
 *
 * If the key is present in the map, `true` shall be returned.
 * If the key is not present in the map, `false` shall be returned. */
{
  if (key == NULL)
    return NULL;

  size key_size = map->key_size;
  u64 hash = map_hash(key, key_size);
  u64 capped_hash = map_capped_hash(hash, map->capacity);
  struct map_entry* entry = map->buckets[capped_hash];

compare_key:
  if (entry == NULL)
    return false;
  if (map_compare(entry->key, key, key_size))
    return true;

  entry = entry->next;
  goto compare_key;
}
void map_pretty_print (
    struct map* map
)
/**
 * This function shall pretty print the map, showing all entries in the map grouped
 * in buckets.
 *
 * For each entry, this function shall print the bytes of its key and value. */
{
  for (u64 i = 0; i < map->capacity; i++)
    map_pretty_print_bucket(
      map->key_size, map->value_size, i, map->buckets[i]);
}
void map_rehash (
    struct map* map
)
/**
 * This function shall double the map capacity and shall reposition all entries in their
 * new hashed location in the buckets.
 *
 * This operation is necessary in order to avoid overcrowding of the map: when this
 * happens, the map performances start to degrade, because the buckets will hold more
 * and more entries in the linked lists, requiring linear search in order to find
 * the entries.
 *
 * Increasing the capacity and redistributing the entries across ampler buckets shall
 * avoid the overcrowdinge of linked lists, which will allow more direct hash access. */
{
  u64 old_capacity = map->capacity;
  u64 new_capacity = old_capacity * 2;

  map->length = 0;
  map->capacity = new_capacity;
  struct map_entry* old_entry = NULL;
  struct map_entry** new_buckets = calloc(new_capacity, sizeof(struct map_entry*));

  /* Temporarily enables the `Map_Flag__Rehashing` which prevents copying the keys
   * and values during the rehash, to avoid double copies. */
  map_flag_enable(map, Map_Flag__Rehashing);

  u64 index = 0;
  old_entry = map->buckets[index];
  /* Starting from the first entry of the first bucket, the following cycle will pass
   * over every entry in the map, and will set its corresponding key and value in the
   * new buckets, thus effectively redistributing the load. */

next_entry:
  if (old_entry == NULL)
    goto next_bucket;

  map_set_with_buckets(
    map, old_entry->key, old_entry->value, old_entry->hash, new_buckets);

  if (old_entry->next == NULL)
    goto next_bucket;

  old_entry = old_entry->next;
  goto next_entry;

next_bucket:
  map_destroy_bucket(map, map->buckets[index]);
  index++;
  if (index >= old_capacity)
    goto assign_new_buckets;

  old_entry = map->buckets[index];
  goto next_entry;

assign_new_buckets:
  free(map->buckets);
  map->buckets = new_buckets;
  map_flag_disable(map, Map_Flag__Rehashing);
}
void* map_set (
    struct map* map,
    void* key,
    void* value
)
/**
 * This function shall set corresponding *key* with the provided *value* in the map.
 *
 * If the *key* is already present in the map, its value shall be replaced, otherwise
 * a new entry shall be added.
 *
 * The function will return the provided *value*. */
{
  if (key == NULL)
    return NULL;

  u64 hash = map_hash(key, map->key_size);
  return map_set_with_buckets(map, key, value, hash, map->buckets);
}
void map_destroy_bucket (
    struct map* map,
    struct map_entry* entry
)
/**
 * This function shall recursively free all entries in a bucket. */
{
  if (entry == NULL)
    return;

  map_destroy_bucket(map, entry->next);
  map_destroy_entry(map, entry);
}
void map_destroy_entry (
    struct map* map,
    struct map_entry* entry
)
/**
 * This function shall recursively free all entries in a bucket. */
{
  if (entry == NULL)
    return;

  /* If rehashing, do not ever free the entry key and value, even if the copy flags are
   * enabled. They will be reused. */
  if (map->flags & Map_Flag__Rehashing)
    goto free_entry;

  if (map->flags & Map_Flag__Copy_Keys)
    free(entry->key);
  if (map->flags & Map_Flag__Copy_Values)
    free(entry->value);

free_entry:
  free(entry);
}
void map_entry_add (
    struct map* map,
    void* key,
    void* value,
    u64 hash,
    struct map_entry** add_location
)
/**
 * This function shall add a new entry in the map, with the provided *key*, *value* and
 * *hash*.
 *
 * The entry will be stored at the provided *add_location*, which must be an entry
 * pointer address. In other words, the caller of this function must know in advance
 * where the new entry must be added: this function will not do any reasoning in this
 * matter.
 *
 * If, after adding the new entry, the map load reaches or surpasses the
 * `MAP_MAXIMUM_LOAD_FACTOR` threshold, then this function shall trigger a rehash,
 * invoking the #map_rehash function. */
{
  struct arena* arena = map->arena;
  struct map_entry* entry = arena_calloc(arena, 1, sizeof(struct map_entry));

  map_entry_key_set(map, entry, key);
  map_entry_value_set(map, entry, value);
  entry->hash = hash;
  *add_location = entry;

  map->length++;

  /* Skips load check if already rehashing. */
  if (map->flags & Map_Flag__Rehashing)
    return;

  d64 map_load = (d64) map->length / (d64) map->capacity;
  if (map_load >= MAP_MAXIMUM_LOAD_FACTOR)
    map_rehash(map);
}
void map_entry_key_set (
    struct map* map,
    struct map_entry* entry,
    void* key
)
/**
 * This function shall set the provided *key* in the provided *entry*.
 *
 * If the map has the copy key flag enabled, then this function shall make a copy of the
 * provided *key* and store that copy in the provided *entry*. */
{
  if (map->flags & Map_Flag__Rehashing)
    goto do_not_copy;

  if (map->flags & Map_Flag__Copy_Keys)
    goto do_copy;

do_not_copy:
  entry->key = key;
  return;

do_copy:
  size key_size = map->key_size;
  void* key_copy = arena_calloc(map->arena, 1, key_size);
  memcpy(key_copy, key, key_size);
  entry->key = key_copy;
  return;
}
void map_entry_value_set (
    struct map* map,
    struct map_entry* entry,
    void* value
)
/**
 * This function shall set the provided *value* in the provided *entry*.
 *
 * If the map has the copy value flag enabled, then this function shall make a copy of
 * the provided *value* and store that copy in the provided *entry*. */
{
  if (map->flags & Map_Flag__Rehashing)
    goto do_not_copy;

  if (map->flags & Map_Flag__Copy_Values)
    goto do_copy;

do_not_copy:
  entry->value = value;
  return;

do_copy:
  size value_size = map->value_size;

  /* The entry *value* is not `NULL`, therefore it was already copied in a previous
   * call of #map_entry_value_set. Even if the `Map_Flag__Copy_Values` is enabled, we
   * avoid doing another copy -- which is redundant -- and instead reuse the already
   * allocated memory, overwriting it with the new value. */
  if (entry->value != NULL)
    goto reuse_memory;

  void* value_copy = arena_calloc(map->arena, 1, value_size);
  memcpy(value_copy, value, value_size);
  entry->value = value_copy;
  return;

reuse_memory:
  memcpy(entry->value, value, value_size);
  return;
}
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
inline bool map_compare (
    void* key_1,
    void* key_2,
    size key_size
)
/**
 * This function is a generic byte comparison between two keys. */
{
  for (size i = 0; i < key_size; i++)
    if (((byte*) key_1)[i] != ((byte*) key_2)[i])
      return false;

  return true;
}
inline u64 map_hash (
    void* key,
    size key_size
)
/**
 * This function returns a generic hash value based on [djb2 algorithm]
 * (http://www.cse.yorku.ca/~oz/hash.html). */
{
  u64 hash = 5381;
  byte key_byte = 0;
  byte* key_bytes = (byte*) key;

  for (size i = 0; i < key_size; i++) {
    key_byte = key_bytes[i];
    hash = ((hash << 5) + hash) + key_byte; /* hash * 33 + character */
  }

  return hash;
}
struct map_entry* map_get_entry (
    struct map* map,
    void* key
)
/**
 * This function shall retrieve the entry of the provided *key* in the map.
 *
 * If the key is not present in the map, `NULL` shall be returned. */
{
  if (key == NULL)
    return NULL;

  size key_size = map->key_size;
  u64 hash = map_hash(key, key_size);
  u64 capped_hash = map_capped_hash(hash, map->capacity);
  struct map_entry* entry = map->buckets[capped_hash];

compare_key:
  if (entry == NULL)
    return NULL;
  if (map_compare(entry->key, key, key_size))
    return entry;

  entry = entry->next;
  goto compare_key;
}
void map_pretty_print_bucket (
    size key_size,
    size value_size,
    u64 bucket_index,
    struct map_entry* bucket
)
/**
 * Pretty prints a bucket of the map. */
{
  map_pretty_print_entry(key_size, value_size, bucket_index, bucket);
  if (bucket != NULL && bucket->next != NULL)
    map_pretty_print_bucket(key_size, value_size, bucket_index, bucket->next);
}
void map_pretty_print_entry (
    size key_size,
    size value_size,
    u64 bucket_index,
    struct map_entry* entry
)
/**
 * Pretty prints an entry of the map. */
{
  fprintf(stderr, "[%4li] [ ", bucket_index);
  if (entry == NULL) goto print_empty_entry;

  byte* key = (byte*) entry->key;
  byte* value = (byte*) entry->value;

  for (size i = 0; i < key_size; i++)
    fprintf(stderr, "%02x ", key[i]);
  fprintf(stderr, "] [ ");

  for (size i = 0; i < value_size; i++)
    fprintf(stderr, "%02x ", value[i]);
  fprintf(stderr, "]\n");

  return;

print_empty_entry:
  for (size i = 0; i < key_size; i++)
    fprintf(stderr, "-- ");
  fprintf(stderr, "] [ ");

  for (size i = 0; i < value_size; i++)
    fprintf(stderr, "-- ");
  fprintf(stderr, "]\n");
}
inline void* map_set_with_buckets (
    struct map* map,
    void* key,
    void* value,
    u64 hash,
    struct map_entry** buckets
)
/**
 * This function shall set corresponding *key* with the provided *value* in the
 * provided *buckets*, using the precalculated *hash*.
 *
 * If the *key* is already present in the buckets, its value shall be replaced,
 * otherwise a new entry shall be added.
 *
 * The function will return the provided *value*. */
{
  if (key == NULL)
    return NULL;

  u64 capped_hash = map_capped_hash(hash, map->capacity);
  size key_size = map->key_size;
  struct map_entry* entry = buckets[capped_hash];
  if (entry != NULL)
    goto search_entry;

  map_entry_add(map, key, value, hash, buckets + capped_hash);
  return value;

search_entry:

compare_key:
  if (map_compare(entry->key, key, key_size)) {
    map_entry_value_set(map, entry, value);
    return value;
  }

  if (entry->next == NULL)
    goto append_entry;

  entry = entry->next;
  goto compare_key;

append_entry:
  map_entry_add(map, key, value, hash, &(entry->next));
  return value;
}
