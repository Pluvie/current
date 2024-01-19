/**
 * Initializes an already declared map, with the given *name*, *key_type* and
 * *value_type*. Extra configuration options may be passed using the macro variadic
 * args. */
#define map_init(name, key_type, value_type, ...)                                       \
  {                                                                                     \
    struct __map_config config = {                                                      \
      .key_size = (uint16) sizeof(key_type),                                            \
      .value_size = (uint16) sizeof(value_type),                                        \
      ##__VA_ARGS__ };                                                                  \
    if (config.key_copy_size == 0)                                                      \
      config.key_copy_size = config.key_size;                                           \
    name = __map_new(config);                                                           \
  }

/**
 * Creates a new map, with the given *name*, *key_type* and *value_type*.
 * Extra configuration options may be passed using the macro variadic args. */
#define map_new(name, key_type, value_type, ...)                                        \
  map(key_type, value_type) name;                                                       \
  map_init(name, key_type, value_type, ##__VA_ARGS__ )

/**
 * Returns `true` if the map has the given key, `false` otherwise. */
#define map_has(map_ptr, key)                                                           \
  (map_find(map_ptr, key, __Map_Find_Default) >= 0)

/**
 * Returns the map value associated to the given key. If the key is not present,
 * then the __zero value__ of the map value type is returned. */
#define map_get(map_ptr, key)                                                           \
  (map_ptr[map_find(map_ptr, key, __Map_Find_Default)])

/**
 * Sets the value for the given key in the map. If the key is already present,
 * the value will be overwritten. */
#define map_set(map_ptr, key, value) (                                                  \
  map_load(map_ptr, 1) >= 0.7                                                           \
    ? (                                                                                 \
      map_ptr = __map_rehash(map_ptr, map_fat_ptr(map_ptr)),                            \
      map_ptr[map_use(map_ptr, key, __Map_Use_Default)] = value,                        \
      value                                                                             \
    )                                                                                   \
    : (                                                                                 \
      map_ptr[map_use(map_ptr, key, __Map_Use_Default)] = value,                        \
      value                                                                             \
    )                                                                                   \
  )

/**
 * Deletes the value for the given key in the map. */
#define map_del(map_ptr, key)                                                           \
  __map_delete(&(key), map_hash(map_ptr, key), map_fat_ptr(map_ptr))

/**
 * Releases all memory regions used by the map. */
#define map_free(map_ptr)                                                               \
  (__map_free(map_fat_ptr(map_ptr)))

/**
 * Loops through all the used indexes of the map. */
#define map_each(map_ptr, key_type, value_type, iter_name)                              \
  (struct { key_type key; value_type value; int64 counter; int64 index; }               \
      iter_name = { .counter = 0, .index = -1 };                                        \
      iter_name.counter < map_capacity(map_ptr); iter_name.counter++)                   \
    if (iter_name.index++,                                                              \
        iter_name.key = map_key(map_ptr, key_type, iter_name.counter),                  \
        iter_name.value = map_ptr[iter_name.counter],                                   \
        !(map_used(map_ptr, iter_name.counter))) { iter_name.index--; continue; } else

/**
 * Loops through all the indexes of the map, both used and not used. */
#define map_all(map_ptr, key_type, value_type, iter_name) (                             \
    struct {                                                                            \
      key_type key; value_type value; bool used; uint64 hash; uint64 index;             \
    } iter_name = { 0 };                                                                \
    iter_name.index < map_capacity(map_ptr);                                            \
    iter_name.index++                                                                   \
  )                                                                                     \
    if (iter_name.key = map_key(map_ptr, key_type, iter_name.index),                    \
        iter_name.value = map_ptr[iter_name.index],                                     \
        iter_name.hash = map_hash_stored(map_ptr, iter_name.index),                     \
        iter_name.used = map_used(map_ptr, iter_name.index), true)
