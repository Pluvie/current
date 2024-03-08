package main

import (
  "fmt"
  "os"
)

func pseudorand(n int) int {
  return 18000 * (n & 65535) + (n >> 16);
}

func main() {
  args := os.Args[1:]

  if (args[0] == "insert") {
    insert()
  } else if (args[0] == "capacity") {
    capacity()
  } else if (args[0] == "lookup") {
    lookup()
  } else if (args[0] == "insert_rand") {
    insert_rand()
  } else {
    fmt.Println("no benchmark")
  }
}

func insert() {
  m := make(map[int]int)
  result := 0

  for i := 0; i < 300000; i++ {
    for j := 0; j < 1000; j++ {
      m[j] = i;
    }
  }

  result = m[999];
  fmt.Println("done: ", result)
}

func capacity() {
  m := make(map[int]int)
  result := 0

  for i := 0; i < 3000000; i++ {
    for j := 0; j < 100; j++ {
      m[i] = j;
    }
  }

  result = m[0];
  fmt.Println("done: ", result)
}

func lookup() {
  m := make(map[int]int)
  result := 0

  for i := 0; i < 100; i++ {
    m[i] = i;
  }

  v := 0
  for i := 0; i < 3000000; i++ {
    for j := 0; j < 100; j++ {
      v = m[j];
    }
  }

  result = v;
  fmt.Println("done: ", result)
}

func insert_rand() {
  m := make(map[int]int)
  result := 0

  var k int
  var v int
  for i := 0; i < 300000; i++ {
    for j := 0; j < 1000; j++ {
      k = pseudorand(i)
      v = pseudorand(j)
      m[k] = v
    }
  }

  result = m[126000]; // value should be: 17982000
  fmt.Println("done: ", result)
}
