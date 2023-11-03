<div align="center">
  <h1>☄️ CURRENT ☄️</h1>
  <h3>a map-vector C library</h3>
</div>

## Introduction

__Current__ is a C library that provides a convenient implementation of generic `map`
and `vector` data structures.

__Current__'s endeavor is to streamline and make as joyful as possible your work with
those modern data structures in C. This of course does not come without limits, however
our hope is that you'll find it as useful and enjoyable as we do.

## Installation

To install __Current__, use the provided Linux Bash script `bin/compile`. It will
compile the library and output the shared object `libcurrent.so` in the `lib` directory
of the current path. The library has no dependencies, so it can be directly copied into
your `/usr/lib` directory and linked using `gcc ... -lcurrent`.

## Vector

A `vector` is a collection of dynamically allocated elements of the same type.
It will grow automatically to fit the memory occupied by all the elements.

Usage example:

```c
vector(int) my_vector = vector_new(int);

vector_push(my_vector, 1);
vector_push(my_vector, 2);
vector_push(my_vector, 3);

my_vector[0];   // Holds 1.
my_vector[1];   // Holds 2.

vector_each(my_vector, int, iter)
  my_vector[iter.index] == iter.element  // You can access them both ways.

vector_free(my_vector);
```

## Map

Map is a lot more complicated than `vector`. Nonetheless, just like `vector` it can be
declared as follows:

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

A map makes sense only if it's tied to a `hash` and a `compare` function. If you use
`char*` as key type, the hash and compare function are provided automatically by the
__Current__ library, no need to specify them (of course, you can still override them).
The same is true if you use an `int`-like scalar type.

For all other types, either scalar or pointer, you **must** provide your own hash and
compare function. They can be then linked to the map using the `map_config` macro. There
will be examples below.

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

The type of the value that you provide to the `map_set` macro is checked at compile
time, so you are safe on that regard.

The key, however, is another (sad) story. Since the implementation, in order to be easy
and as generic as possible, uses a `void*` to store the keys, you won't have compile time
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

#### Other key types

This behaviour is not valid for other pointer key types. Let's say for example that
you have your `struct user` type. If you use the `struct user*` pointer type as map
key type, **remember that the map will copy only the pointer** for each key, and thus
the pointed key object **must** remain valid for all the lifetime of the map. Scalar
key types, instead, are perfectly fine. They will be copied by value, will not
use any heap space, and will remain valid for all the lifetime of the map.

Remember that, when doing map operation with a key type that is not `char*`, you
**must** give a pointer for the key, which will be used internally by the map to
`memcpy` the key content.

Using this struct,

```c
struct user {
  uint32 id;
  uint32 age;
  char name[32];
};
```

Let's look at an example with pointer types:

```c
uint32 user_pointer_hash (
    void* user
/**
 * On pointer types, when this function is called, it will be given a pointer to a
 * `struct user*` pointer. This is because in the map keys it is stored the address
 * of the `struct user*` key, and not directly its content.
 *
 * Thus, all pointer type keys will have always a size of 8 byte (`sizeof(void*)`). */
)
{
  return (*(struct user**) user)->id;
}

bool user_pointer_compare (
    void* u1,
    void* u2
/**
 * Just like we said before, here the comparison between keys is done again with
 * pointers to a `struct user*` pointer. */
)
{
  if (u1 == NULL || u2 == NULL) return false;
  return (*(struct user**) u1)->id == (*(struct user**) u2)->id;
}

map(struct user*, int) user_ages = map_new(struct user*, int);
map_config(user_ages, user_pointer_hash, user_pointer_compare);

struct user* toni = calloc(1, sizeof(struct user));
toni->id = 11; toni->age = 33; toni->name = "Toni";
map_set(user_ages, &toni, toni->age);   // Remember the `&` with non `char*` key types.
map_get(user_ages, &toni);              // Will return 33.

/**
 * IMPORTANT: the `toni` struct must remain valid for all the lifetime of the map!
 * Otherwise, its keys will be broken. */
free(toni);
map_free(user_ages);
```

And another for scalar types:

```c
uint32 user_scalar_hash (
    void* user
)
{
  return ((struct user*) user)->id;
}

bool user_scalar_compare (
    void* u1,
    void* u2
)
{
  if (u1 == NULL || u2 == NULL) return false;
  return ((struct user*) u1)->id == ((struct user*) u2)->id;
}

map(struct user, int) user_ages = map_new(struct user, int);
map_config(user_ages, user_scalar_hash, user_scalar_compare);

struct user toni = { .id = 11, .age = 33, .name = "Toni" };
map_set(user_ages, &toni, toni.age);    // Remember the `&` with non `char*` key types.
map_get(user_ages, &toni);              // Will return 33.

map_free(user_ages);
```

This brings us to the main limitation of __Current__ map: you cannot use scalar literals
in map operations. The reason is that, in C, a scalar literal cannot be the target of
the "address of" (`&`) operator. You must save the literal value on a variable first,
and the use that variable as key. Example:

```c
map(int, int) example = map_new(int, int);

map_set(example, &7, 11);   // You cannot do this (it's not even valid C).
int key = 7;
map_set(example, &key, 11); // You must do this.

map_free(example);
```

This is because in our choice of implementation, we required that all keys have to be
passed by reference (pointer). There are other implementations that lets you pass
a key by value, but they bring other complications on the table. In the end, we believe
this implementation is the best tradeoff between simplicity of use and power of
expression.

### Looping

Looping a map is almost like a vector:

```c
map(char*, int) my_map = map_new(char*, int);

map_each(my_map, char*, int, iter) {
  iter.key;   // Will hold the map key.
  iter.value; // Will hold the map value.
  iter.index; // Will hold the current iterating index starting from 0.
}

map_free(my_map);
```

### Zero value

What happens when a `map_get` operation will not find the given key in the map? How
will the returned result be handled? Well, hopefully there's good news here.

The __Current__ map implementation, during initialization, will reserve a **zero-value**
memory region of the same type of the map value. This is basically a memory block of the
same length of the value type, filled with zero's. It is stored right before the map
value pointer, so, when the map find will return `-1` (key not found) a simple pointer
arithmetic will return the zero value of the map value type.

For pointer value types, the zero-value will be equal to the `NULL` macro, so you can use
its logic. For scalar value types, you can just do a `== 0` comparison, even for `struct`
types.

## Benchmarks

TODO

```shell
\time -v exe/benchmark insert
```

## Contributing

Any contribution is very welcome. Please open an issue or a pull request and we will
happily review it.
