package main

import (
  "fmt"
)

func pseudorand(a int) int {
  a = (a ^ 61) ^ (a >> 16)
  a = a + (a << 3)
  a = a ^ (a >> 4)
  a = a * 0x27d4eb2d
  a = a ^ (a >> 15)
  return a;
}

func main() {
  //insert();
  //capacity();
  //lookup();
  insert_rand();
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

  for i := 0; i < 300000; i++ {
    for j := 0; j < 1000; j++ {
      m[pseudorand(j)] = pseudorand(i);
    }
  }

  result = m[999];
  fmt.Println("done: ", result)
}
