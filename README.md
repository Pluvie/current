<div align="center">
  <h1>☄️ CURRENT ☄️</h1>
  <h3>a map-vector C library</h3>
</div>

## Introduction

__Current__ is a C library that provides a convenient implementation of generic `map`
and `vector` data structures.

__Current__'s endeavor is to streamline and make as joyful as possible working with
those modern data structures in C. This of course does not come without limits, however
our hope is that you find it as useful and enjoyable as we do.

## Vector

This is easy. TODO.

## Map

Map is a lot more complicated than `vector`. Just like it, it can be declared as follows:

```c
map(char*, int) my_map;
```

In order to initialize you must use the `map_new` macro, or the `map_new_cap` macro if
you have a rough idea of how much data the map will require (beware of load factor, see
later).

```c
/* Default capacity, which is 8. */
map(char*, int) my_map = map_new(char*, int);

/* Custom capacity, in this case set at 32. */
map(char*, int) my_map = map_new_cap(char*, int, 32);
```

And of course, at the end, don't forget to free the map!

```c
map_free(my_map);
```

### Hash and compare functions

TODO, explain hash and compare functions.

### Operations

Common operation in maps are:

```c
/* Setting the value for a given key. */
map_set(my_map, "abc", 11);

/* Getting the value for a given key. */
map_get(my_map, "abc");

/* Deleting the value for a given key. */
map_delete(my_map, "abc");

/* Determining if the map has a given key. */
map_has(my_map, "def");
```

The types of the value that you provide to the `map_set` macro is checked at compile
time, so you are safe on that regard.

The key, however, is another (sad) story. Since the implementation, to be easy and as
generic as possible, uses a `void*` to store the keys, you won't have compile time
checks on the key type.

Moreover, there are certain caveats that we will explore now.

### Keys

#### String (aka `char*`) key type

If the key type of the map is `char*`, then you are mostly safe as optimizations have
been made in order to work better with this type.

First, each key is copied, and stored in the map. This will allow you to end the
lifetime of a string without breaking the map keys. Example:

```c
map(char*, int) example = map_new(char*, int);

char* my_string = calloc(8, sizeof(char));
my_string[0] = 'a';
my_string[1] = 'b';
my_string[2] = 'c';

map_set(example, my_string, 7);
map_get(example, my_string);      // Will return 7.

free(my_string);
/* Now, of course you cannot do `map_get(example, my_string)` anymore, since `my_string`
 * has been freed, but you can still do: */
map_get(example, "abc");        // Will still work and return 7.

/* Also, when freeing the map, all copies of the string keys will also be automatically
 * freed. */
map_free(example);
```

This behaviour is not valid for other pointer key types. Let's say for example that
you have your `struct user` type. If you use the `struct user*` pointer type as map
key type, **remember that the map will copy only the pointer** for each key, and thus
the pointed key object **must** remain valid for all the lifetime of the map.

Scalar key types, instead, are perfectly fine. They will be copied by value, will not
use any heap space, and will remain valid for all the lifetime of the map. Remember
that, when doing map operation with a scalar key type, you **must** give a pointer
for the key, which will be used internally by the map to `memcpy` the key content:

```c
struct user {
  uint32 id;
  uint32 age;
  char name[32];
};

uint32 user_hash (
    void* user
)
{
  return ((struct user*) user)->id;
}

bool user_compare (
    void* u1,
    void* u2
)
{
  if (u1 == NULL || u2 == NULL) return false;
  return ((struct user*) u1)->id == ((struct user*) u2)->id;
}

map(struct user, int) user_ages = map_new(struct user, int);
map_config(user_ages, user_hash, user_compare);

struct user toni = { .id = 11, .age = 33, .name = "Toni" };
map_set(user_ages, &toni, toni.age);    // Remember the `&` when using scalar key types.
map_get(user_ages, &toni);              // Will return 33.

map_free(user_ages);
```

### Zero value

What happens when a `map_get` operation will not find the given key in the map? How
will the returned result be handled? Well, hopefully there's good news here.

The __Current__ map implementation, during initialization, will reserve a **zero-value**
memory region of the same type of the map value. This is basically a memory block of the
same length of the value type, filled with zero's. It is stored right before the map
value pointer, so, when the map find will return `-1` (key not found) a simple pointer
arithmetic will return the zero value of the map value type.

For pointer key types, the zero-value will be equal to the `NULL` macro, so you can use
its logic. For scalar key types, you can just do a `== 0` comparison, even for `struct`
types.

## Benchmarks

TODO

```shell
\time -v exe/benchmark insert
```
