<div align="center">
  <h1>☄️ CURRENT ☄️</h1>
  <h3>an arena optimized map-set-vector C library</h3>
</div>

## Introduction

__Current__ is a C library that provides a convenient implementation of generic `map`,
`set` and `vector` data structures.

__Current__'s endeavor is to streamline and make as joyful as possible your work with
those data structures in C. This of course does not come without limits, however
our hope is that you'll find it as useful and enjoyable as we do.

## Installation

To install __Current__, use the provided Linux Bash script `bin/install`. It will
compile the library and output the shared object `libcurrent.so` in the `lib` directory
of the current path. The library has no dependencies, so it can be directly copied into
your `/usr/lib` directory and linked using `gcc ... -lcurrent`.

## Features

__Current__ will make possible to create maps, sets and vectors of generic types, and
operate with these data structures as you are probably used from higher level languages.

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

## Test

Use the provided Linux Bash script `bin/test`. You must have Valgrind installed to run
the test. Everything should run without memory leaks and without assert failures.

## Benchmarks

TODO

```shell
\time -v exe/benchmark insert
```

## Contributing

Any contribution is very welcome. Please open an issue or a pull request and we will
happily review it.
