# Map

A `map` is an unordered collection of pairs { *key*, *value* }. These pairs are called
*entries*.

The most important map property is that for each given *key*, there can be only one
value: in other words, a map cannot hold two entries with the same *key*.

The map can get, set, or delete an *entry*. All these operations are done in constant
time. This is achieved with the use of a hash function -- this is why this data
structure is often referred as "hashmap". To know more on how a map works,
[refer to this article](https://benhoyt.com/writings/hash-table-in-c/).

In __Current__, a map can be declared like this:

```c
struct map map = map_init(int, char*);
```

The key type is `int`, and the value type is `char*`.

## Initialization

The map is designed to be used on the stack. You can freely pass its address around to
other functions as there are no internal pointers.

When initialized with `map_init`, the map will not do any allocation. In order to start
using it, you must call `map_create`:

```c
struct map map = map_init(int, char*);
map_create(&map);
```

## Usage

You can do these operations on the map:

  - `set` to put a { *key*, *value* } entry in the map: this operation will add a new
    entry if the *key* is not present in the map, otherwise it will substitute the
    *value* of the already existing entry with the same *key*.
  - `del` to remove a { *key*, *value* } entry.
  - `get` to retrieve the *value* for a *key*: if there are no entries with that *key*,
    `NULL` will be returned.
  - `has` to know if the map has an entry with a provided *key*.

Examples:

```c
struct map map = map_init(int, int);
map_create(&map);

int key = 3;
int value = 7;

map_set(&map, &key, &value);          // Will create the new entry { 3, 7 }.

int other_value = 9;
map_set(&map, &key, &other_value);    // Will replace the previous entry with { 3, 9 }.

int* value_pointer;
value_pointer = map_get(&map, &key);  // Will retrieve the value 9.

map_has(&map, &key);                  // Will return `true`.
map_del(&map, &key);                  // Will remove the entry { 3, 9 }.
```

As you can see, the map works exclusively with pointers. You will not be able to pass
direct keys or values to __Current__ map, e.g. you cannot do `map_get(&map, 3)`.

This is because the map will just hold pointers to its real keys and values. With this
usage, **it is mandatory that the objects holding the keys and values will continue to
remain valid and unchanged throughout all the map lifetime**.

Of course, this cannot always happen in a real world scenario. To help dealing with
this, __Current__ map has two flags: `Map_Flag__Copy_Keys` and `Map_Flag__Copy_Values`.
You can activate them, before creating the map, using:

```c
map_flag_enable(&map, Map_Flag__Copy_Keys);
map_flag_enable(&map, Map_Flag__Copy_Values);
```

With these flags active, the map will copy all keys and values, and you can scratch
whatever was holding them after being given to the map. These flags can be active
individually, should you need to just copy the keys, or the values.

This will use more memory, of course, and also slow performances a bit, since we have to
pay for the cost of the copy. But in some situations, this is the only solution.
Nevertheless, one of the benefits of working with the C language is that you have
**complete** control over the memory: if you don't need to copy the keys or the values,
and can instead reference them via pointers, you **can** do it. This, if used wisely,
can held in so much better performance and memory savings compared to other garbage
collected languages like Go or Java, and again in so much less programmer headaches
and compiler-wars compared to languages like Rust.

Once done with the map, you must release its memory with:

```c
map_destroy(&map);
```

This will just release the memory occupied by the map entries, and all potential key or
value copies. Since the map struct is on the stack, it will be cleared upon function
return.

## Fixed Lookup

__Current__ map provides the `Map_Flag__Fixed_Lookup` for maps where you can guarantee
that every call to `map_set` is unique, i.e. a given *key* will be inserted at most
once.

This is particularly beneficial in heavy insertion scenarios, as the set function will
directly look for empty *entries*, completely skipping the *key* comparison when dealing
with a collision.

This technique is used internally in the `map_rehash` function, where the map has to
be resized to a doubled capacity: in this case, we can safely use the fixed lookup flag,
as we know that keys are unique by definition.

## Thread Safety

__Current__ map is thread safe only for the `get` and `has` operations, whereas the
`set` and `del` operations must be externally synchronized via a mutex.
