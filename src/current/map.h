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
  u64   (*hash)(void*);
  bool  (*compare)(void*, void*);
  struct map_entry** buckets;
};

struct map_entry {
  void* key;
  void* value;
  struct map_entry* next;
};

#define map(key_type, value_type) \
  map_new(sizeof(key_type), sizeof(value_type), 8)

u64 map_generic_hash (
    void* key
)
{
  return (u64) key / 2;
}

bool map_generic_compare (
    void* key_1,
    void* key_2
)
{
  return key_1 == key_2;
}

struct map* map_new (
    size key_size,
    size value_size,
    size initial_capacity
)
{
  struct map* map_ptr = calloc(1, sizeof(struct map));
  map_ptr->key_size = key_size;
  map_ptr->value_size = value_size;
  map_ptr->capacity = initial_capacity;
  map_ptr->buckets = calloc(initial_capacity, sizeof(struct map_entry*));
  map_ptr->hash = map_generic_hash;
  map_ptr->compare = map_generic_compare;

  return map_ptr;
}

void map_free_bucket (
    struct map_entry* entry
)
{
  if (entry == NULL) return;
  map_free_bucket(entry->next);
  free(entry);
}

void map_free (
    struct map* map_ptr
)
{
  for (i64 i = 0; i < map_ptr->capacity; i++)
    map_free_bucket(map_ptr->buckets[i]);
  free(map_ptr->buckets);
  free(map_ptr);
}

struct map_entry* map_add_entry (
    struct map* map_ptr,
    void* key,
    void* value
)
{
  struct map_entry* entry = calloc(1, sizeof(struct map_entry));
  entry->key = key;
  entry->value = value;
  map_ptr->length++;
  return entry;
}

bool map_set (
    struct map* map_ptr,
    void* key,
    void* value
)
{
  u64 hash = map_ptr->hash(key) % map_ptr->capacity;
  struct map_entry* entry = map_ptr->buckets[hash];
  if (entry != NULL)
    goto search_entry;

  map_ptr->buckets[hash] = map_add_entry(map_ptr, key, value);
  return true;

search_entry:
  bool (*compare)(void*, void*) = map_ptr->compare;

compare_key:
  if (compare(entry->key, key)) {
    entry->value = value;
    return false;
  }

  if (entry->next == NULL)
    goto append_entry;

  entry = entry->next;
  goto compare_key;

append_entry:
  entry->next = map_add_entry(map_ptr, key, value);
  return true;
}

void* map_get (
    struct map* map_ptr,
    void* key
)
{
  u64 hash = map_ptr->hash(key) % map_ptr->capacity;
  bool (*compare)(void*, void*) = map_ptr->compare;
  struct map_entry* entry = map_ptr->buckets[hash];

compare_key:
  if (entry == NULL)
    return NULL;
  if (compare(entry->key, key))
    return entry->value;

  entry = entry->next;
  goto compare_key;
}

void map_pretty_print_bucket (
    size key_size,
    size value_size,
    i64 bucket_index,
    struct map_entry* entry
)
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

  if (entry->next != NULL)
    map_pretty_print_bucket(key_size, value_size, bucket_index, entry->next);

  return;

print_empty_entry:
  for (size i = 0; i < key_size; i++)
    fprintf(stderr, "-- ");
  fprintf(stderr, "] [ ");

  for (size i = 0; i < value_size; i++)
    fprintf(stderr, "-- ");
  fprintf(stderr, "]\n");
}

void map_pretty_print (
    struct map* map_ptr
)
{
  for (i64 i = 0; i < map_ptr->capacity; i++)
    map_pretty_print_bucket(
      map_ptr->key_size, map_ptr->value_size, i, map_ptr->buckets[i]);
}
