# Map

A `map` is an unordered collection of pairs { *key*, *value* }.
For each given *key*, there can be only one value: in other words, a map cannot hold two
pairs with the same *key*.

The map can get, set, or delete a { *key*, *value* } pair. All these operations are done
in constant time. This is achieved with the use of a hash function -- this is why this
data structure is often referred as "hashmap". To know more on how a map works,
[refer to this article](https://benhoyt.com/writings/hash-table-in-c/).

In __Current__, a map can be declared like this:

```c
struct map* my_map = map(char*, int);
```

The key type is `char*`, and the value type is `int`.

## Initialization

As you probably have guessed, the map initialization is done by a macro which accepts
variadic args as configuration parameters. These parameters are fields of the
`configuration` struct that will be given to the map during initialization.

We have already seen the `hash` and `compare` parameters, [below](#configuration) you
can find a list of the other ones available.

The map object created by the `map_init` or `map_new` macros is just a pointer, so you
can safely pass it around.

## Usage

Using the

```c
map(char*, int) my_map
```

defined above, you can:

### Set

Set an association between a *key* and a *value* (in this case a `char*` and an
`int`), by doing:

```c
char* key = "abc";
map_set(my_map, &key, 10);
```

__IMPORTANT__: the key argument passed to `map_set` must be an address of a local
variable of the exact same type of the map key. You cannot use a constant, a literal and
neither an array:

```c
#define KEY "abc"
map_set(my_map, &KEY, 10);    /* Will not work! */

char key[4] = "abc";
map_set(my_map, &key, 10);    /* Will not work! */

map_set(my_map, &"abc", 10);  /* Will not work! */
```

All of the above examples will not work. The reason is because the map implementation
demands a pointer to the key object (as `void*`) and the address of operator (`&`) will
not give the correct address when used on a constant, an array or a literal.

### Get

You can get a value with:

```c
char* key = "abc";
map_get(my_map, &key);
```

As said in the set operation, the key must be a pointer to a local variable.

If the key is not present in the map, then the *zero value* of the same type of the
map *value* type shall be returned. The *zero value* is just a fixed sequence of bytes,
all at value 0, with the same length of the size of the map *value* type.

### Delete

You can delete a value with:

```c
char* key = "abc";
map_del(my_map, &key);
```

As said in the set and get operation, the key must be a pointer to a local variable.

### Has

You can check if the map has a given key with:

```c
char* key = "abc";
map_has(my_map, &key);
```

This function shall return `true` if the map has the key, `false` otherwise.

## Configuration

All map configuration parameters are:

  - `initial_capacity` (`uint64`), if you have an idea of how many *keys* the map will
    hold, in order to optimize memory allocations.
  - `copy_keys` (`bool`), if you want the map to do a copy of each *key*, more info
    [here](#copy-keys).
  - `key_copy_size` (`unit64`), an optional length in bytes of the key copy: if not
    given, it will be the same length of the key.
  - `key_copy_func` (`(void)(void*, void*, unit64)`), an optional function that shall
    handle the copy of the key.
  - `key_copy_size_func` (`(uint64)(void*)`), an optional function that shall return the
    length of the key copy.
  - `copy_values` (`bool`), if you want the map to do a copy of each *value*, more info
    [here](#copy-values).
  - `value_copy_size` (`unit64`), an optional length in bytes of the value copy: if not
    given, it will be the same length of the value.
  - `value_copy_func` (`(void)(void*, void*, unit64)`), an optional function that shall
    handle the copy of the value.
  - `value_copy_size_func` (`(uint64)(void*)`), an optional function that shall return
    the length of the value copy.
  - `arena` (`struct arena*`), an optional arena pointer to use for memory allocations.

## Hash and compare functions

The hash and compare function for some base types are already provided by __Current__.
These are the prebuilt functions that you can use as hash or compare:

  - `__map_prebuilt_int32_hash`
  - `__map_prebuilt_int32_compare`
  - `__map_prebuilt_int64_hash`
  - `__map_prebuilt_int64_compare`
  - `__map_prebuilt_string_hash`
  - `__map_prebuilt_string_compare`

So, if you want to use the prebuilt functions the example above becomes:

```c
map_new(my_map, char*, int,
  .hash = __map_prebuilt_string_hash,
  .compare = __map_prebuilt_string_compare);
```

But you are of course free to use the functions that you like.
