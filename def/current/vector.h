/**
 * Main vector data, held just before the vector pointer.
 * It contains all the metadata needed for the vector to operate.
 *
 * This will be referenced by the macro #vector_data, which will move the vector pointer
 * behind by `sizeof(struct __vector_data)` bytes.
 *
 * This technique is called "Fat Pointer", [see more here](
 * https://libcello.org/learn/a-fat-pointer-library). */
struct __vector_data {
  uint32  length;
  uint32  capacity;
  uint32  block;
};

/**
 * Minimum vector capacity. */
#define VECTOR_MIN_CAPACITY 4

/**
 * Macro to refer vector data types. */
#define vector(type)                                                                    \
  type*

/**
 * Returns the size of the vector metadata struct. */
#define vector_datasize                                                                 \
  sizeof(struct __vector_data)

/**
 * Returns the vector metadata struct pointer from a vector pointer. */
#define vector_data(vec)                                                                \
  ((struct __vector_data*) vec - 1)

/**
 * Returns the vector capacity. */
#define vector_capacity(vec)                                                            \
  (vector_data(vec)->capacity)

/**
 * Returns the vector length. */
#define vector_length(vec)                                                              \
  (vec == NULL ? 0 : vector_data(vec)->length)

/**
 * Calculates the vector minimum capacity value given a capacity number. */
#define vector_min_cap(capacity)                                                        \
  (capacity < VECTOR_MIN_CAPACITY ? VECTOR_MIN_CAPACITY : next_pow2(capacity))

/**
 * Allocates a new vector using the `type` and `initial_capacity` provided. */
#define vector_new_cap(type, initial_capacity) (                                        \
  __vector_new(vector_min_cap(initial_capacity), sizeof(type)))

/**
 * Allocates a new vector of the provided `type`. The initial capacity shall be equal
 * to #VECTOR_MIN_CAPACITY. */
#define vector_new(type)                                                                \
  vector_new_cap(type, VECTOR_MIN_CAPACITY)

/**
 * Resizes a vector, in order to be able to hold more elements. */
#define vector_resize(vec)                                                              \
  (vec = __vector_resize(vector_data(vec)), 1)

/**
 * Check if the vector is at full capacity. If so, it shall be resized. */
#define vector_check_resize(vec, amount) (                                              \
  vector_length(vec) + amount >= vector_capacity(vec) ?                                 \
  vector_resize(vec) : 1)

/**
 * Pushes a new element at the end of the vector. */
#define vector_push(vec, value)                                                         \
  (vector_check_resize(vec, 1) ? ((vec)[vector_data(vec)->length++] = (value), 1) : 0)

/**
 * Loops through all the elements of the vector, using the provided `iter_name`. */
#define vector_each(vec, element_type, iter_name)                                       \
  for (struct { element_type element; uint32 index; } iter_name =                       \
      { .index = 0 }; iter_name.index < vector_length(vec); iter_name.index++)          \
    if (iter_name.element = vec[iter_name.index], 1)

/**
 * Frees all memory used by the vector and its metadata. */
#define vector_free(vec)                                                                \
  (vec == NULL ? 0 : free(vector_data(vec)))

/**
 * Vector functions. */
function(__vector_new, void*) (uint32 initial_capacity, uint32 element_size);
function(__vector_resize, void*) (struct __vector_data* vector_data);
