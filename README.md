<div align="center">
  <h1>☄️ CURRENT ☄️</h1>
  <h3>an arena optimized map-set-vector C library</h3>
</div>

## Introduction

__Current__ is a C library that provides a convenient implementation of generic `map`,
`set` and `vector` data structures.

__Current__'s endeavor is to streamline and make as joyful as possible your work with
those data structures in C. This, of course, does not come without limits, however
our hope is that you'll find it as useful and enjoyable as we do.

## Features

__Current__ will make possible to create maps, sets and vectors of generic types, and
operate with these data structures in a way that will resemble what you are probably
used from higher level languages.

To be true to the C way, memory management of these objects is *manual*. However, they
also come with an arena implementation, which will significantly help in managing the
memory. If you are used to the classic `malloc`/`free` pairing, writing object
constructors and destructors, we strongly suggest that you give a try to the arena
approach with __Current__ because we feel that it can be of significant help to the
programmer. If not, the arena is completely optional.

To read more on __Current__ map, set and vector usage, refer to each single section:

  - [Map](doc/MAP.md)
  - [Set](doc/SET.md)
  - [Vector](doc/VECTOR.md)

To read more on the arena allocator, refer to [this excellent article](
https://www.rfleury.com/p/untangling-lifetimes-the-arena-allocator).


## Installation

To install __Current__, clone the git repository at the version you want, and then link
the `src` directory in your project, at the path you prefer. Then, include
`current.h` in your sources, and compile them alongside `current.c`, as a
separate translation unit. Example:

Suppose your project folder is `my_project` with a `src/main.c` file. Suppose you
link __Current__ in your project `lib` directory. Your tree will look like:

```
  my_project/
  │
  ├─ lib/
  │  └─ current/
  │
  └─ src/
     └─ main.c
```

You can then add to your `main.c` file:

```c
#include "../lib/current/current.h"
```

And compile the whole project with:

```bash
gcc src/main.c lib/current/current.c -o my_project_executable
```

At the moment, __Current__ did not put any effort in being portable. We are very much
open to contributions on this note. __Current__ is guaranteed to work with `gcc 11.4.0`
on `x86_64` architecture.

## Test

To run tests, install `valgrind` before. Then run the Linux Bash script:

```bash
bin/valgrind test
```

Everything should run without memory leaks and without verification failures.

## Benchmarks

There is a benchmarking tool available that can be run using:

```bash
bin/benchmark [case]
```

Benchmark cases are: `insert`, `capacity`, `lookup` and `insert_rand`. They will
benchmark __Current__'s performances against other C/C++ hashmaps implementations, and
against Golang `map`.

## Contributing

Any contribution is very welcome. Please open an issue or a pull request and we will
happily review it.
