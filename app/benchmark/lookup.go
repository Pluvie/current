package main

import (
  "fmt"
)

func main() {
  m := make(map[int]int)
  result := 0

  for a := 0; a < 10; a++ {
    for i := 0; i < 100000; i++ {
      for j := 0; j < 100; j++ {
        m[j] = i;
        result = m[j];
      }
    }
  }

  fmt.Println("done: ", result)
}
