package main

import (
  "fmt"
)

func main() {
  insert();
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
