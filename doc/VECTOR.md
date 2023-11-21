# Vector

A `vector` is a collection of dynamically allocated elements of the same type.
It will grow automatically to fit the memory occupied by all the elements.

Usage example:

```c
vector(int) my_vector = vector_new(int);

vector_push(my_vector, 1);
vector_push(my_vector, 2);
vector_push(my_vector, 3);

my_vector[0];   // Holds 1.
my_vector[1];   // Holds 2.

vector_each(my_vector, int, iter)
  my_vector[iter.index] == iter.element  // You can access them both ways.

vector_free(my_vector);
```
