package main

import (
  "fmt"
)

func main() {
  //insert();
  capacity();
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
