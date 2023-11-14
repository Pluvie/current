void* __vector_new (
    uint64 initial_capacity,
    uint64 element_size,
    arena* allocator
)
/**
 * This function shall create a new vector using the provided arguments:
 *
 *  - *initial_capacity*: the initial capacity of the vector; this is useful to
 *    reduce expensive reallocations if the amount of data the vector must hold is
 *    known, even rougly, beforehand.
 *  - *element_size*: the amount of bytes occupied by a vector element.
 *
 * All these arguments are usually automatically calculated by the macro #vector_new
 * or #vector_new_cap. */
{
  void* vec = (allocator == NULL)
    ? calloc(1, vector_fp_size + (initial_capacity * element_size))
    : arena_calloc(allocator, 1, vector_fp_size + (initial_capacity * element_size));

  struct __vector_fp* vector_fp = vec;
  vector_fp->allocator = allocator;
  vector_fp->block = element_size;
  vector_fp->capacity = initial_capacity;

  /* Fat pointer technique. The returned pointer is offsetted by a precise amount,
   * in order to store the vector data.
   *
   * When allocating all the memory used by the vector, it is firstly allocated an
   * amount of needed for the vector data -- equal to `sizeof(struct __vector_fp)`,
   * and then an amount needed to hold the actual vector elements -- equal to
   * `element_size * initial_capacity`.
   *
   * ```
   * ┌───────────────────┐
   * │                   │ <---- the allocation starts here
   * │    VECTOR DATA    │
   * │                   │
   * ├───────────────────┤
   * │     element 0     │ <---- the returned pointer is here
   * │ ───────────────── │
   * │     element 1     │
   * │ ───────────────── │
   * │     element 2     │
   * │ ───────────────── │
   * │        .          │
   * │        .          │
   * │        .          │
   * │        v          │
   * │                   │
   * └───────────────────┘
   * ```
   *
   * The returned pointer starts in this last memory region. When it is passed around
   * in all the vector operations and functions, it is always possible to retrieve the
   * pointer to the vector data by going back to the known amount of bytes. */
  return ((byte*) vec + vector_fp_size);
}
