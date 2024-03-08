/**
 * From: [https://probablydance.com/2017/02/26/i-wrote-the-fastest-hashtable/]
 * Code available here: [https://github.com/skarupke/flat_hash_map] */

#include <iostream>
#include <string.h>
#include "./flat_hash_map/flat_hash_map.hpp"

void insert(void);
void capacity(void);
void lookup(void);
void insert_rand(void);

static inline int pseudorand (
    int n
)
{
  return 18000 * (n & 65535) + (n >> 16);
}

int main(
    int argc,
    char* argv[]
) {
  if (argc < 2) {
    std::cout << "no benchmark" << std::endl;
    return 0;
  }

  if (strcmp(argv[1], "insert") == 0)
    insert();
  else if (strcmp(argv[1], "capacity") == 0)
    capacity();
  else if (strcmp(argv[1], "lookup") == 0)
    lookup();
  else if (strcmp(argv[1], "insert_rand") == 0)
    insert_rand();
  else
    std::cout << "invalid benchmark" << std::endl;

  return 0;
}

void insert (
    void
)
{
  int result = 0;
  ska::flat_hash_map<int, int> map;

  for (int i = 0; i < 300000; i++) {
    for (int j = 0; j < 1000; j++) {
      map.emplace(j, i);
    }
  }

  int key = 999;
  result = map[key];
  std::cout << "done: " << result << std::endl;
}

void capacity (
    void
)
{
}

void lookup (
    void
)
{
}

void insert_rand (
    void
)
{
  int result = 0;
  ska::flat_hash_map<int, int> map;

  int k, v;
  for (int i = 0; i < 300000; i++) {
    for (int j = 0; j < 1000; j++) {
      k = pseudorand(i);
      v = pseudorand(j);
      map.emplace(k, v);
    }
  }

  int key = 126000; // value should be: 17982000
  result = map[key];
  std::cout << "done: " << result << std::endl;
}
