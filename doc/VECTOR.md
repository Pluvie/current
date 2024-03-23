# Vector

A vector is a collection of dynamically allocated elements of the same type.
It will grow automatically to fit the memory occupied by all the elements.

Usage example:

```c
Vector vector = vector_init(int);
vector_flag_enable(VECTOR_FLAG__COPY_ELEMENTS);
vector_create(&vector);

for (int i = 0; i < 3; i++)
  vector_push(&vector, &i);

vector_get(&vector, 0)  // Holds a pointer to 0.
vector_get(&vector, 1)  // Holds a pointer to 1.

vector_each(&vector, element)
  printf("> %i", *element); // Will print 0 and 1.

vector_destroy(&vector);
```
