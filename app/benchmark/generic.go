package main

import (
  "fmt"
)

func main() {
  result := 0

  for a := 0; a < 1000; a++ {
    for i := 0; i < 100000; i++ {
      for j := 0; j < 100; j++ {
        result = i;
      }
    }
  }

  fmt.Println("done: ", result)
}
