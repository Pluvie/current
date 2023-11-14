/**
       ____    ____  _______   ______ .___________.  ______   .______      
       \   \  /   / |   ____| /      ||           | /  __  \  |   _  \     
        \   \/   /  |  |__   |  ,----'`---|  |----`|  |  |  | |  |_)  |    
         \      /   |   __|  |  |         |  |     |  |  |  | |      /     
          \    /    |  |____ |  `----.    |  |     |  `--'  | |  |\  \----.
           \__/     |_______| \______|    |__|      \______/  | _| `._____|
                                                                    
                                                                                      **/

/**
 * Main vector data, held just before the vector pointer.
 * It contains all the metadata needed for the vector to operate.
 *
 * This will be referenced by the macro #vector_fp, which will move the vector pointer
 * behind by `sizeof(struct __vector_fp)` bytes.
 *
 * This technique is called "Fat Pointer", [see more here](
 * https://libcello.org/learn/a-fat-pointer-library). */
struct __vector_fp {
  arena*  allocator;
  uint64  length;
  uint64  capacity;
  uint64  block;
};

function(__vector_free, void) (struct __vector_fp*);
function(__vector_new, void*) (uint64, uint64, arena*);
function(__vector_resize, void*) (struct __vector_fp*);

/**
 * Minimum vector capacity. */
#define VECTOR_MIN_CAPACITY 4

/**
 * Macro to refer vector data types. */
#define vector(type)                                                                    \
  type*

/**
 * Returns the size of the vector metadata struct. */
#define vector_fp_size                                                                  \
  sizeof(struct __vector_fp)

/**
 * Returns the vector metadata struct pointer from a vector pointer. */
#define vector_fp(vec)                                                                  \
  ((struct __vector_fp*) vec - 1)

/**
 * Returns the vector capacity. */
#define vector_capacity(vec)                                                            \
  (vector_fp(vec)->capacity)

/**
 * Returns the vector length. */
#define vector_length(vec)                                                              \
  (vec == NULL ? 0 : vector_fp(vec)->length)

/**
 * Calculates the vector minimum capacity value given a capacity number. */
#define vector_min_cap(capacity)                                                        \
  (capacity < VECTOR_MIN_CAPACITY ? VECTOR_MIN_CAPACITY : next_pow2(capacity))

/**
 * Allocates a new vector using the `type` and `initial_capacity` provided. */
#define vector_new_cap(type, initial_capacity) (                                        \
  __vector_new(vector_min_cap(initial_capacity), sizeof(type), NULL))

/**
 * Same as #vector_new_cap, but using the specified allocator. */
#define vector_new_cap_arena(type, initial_capacity, allocator) (                       \
  __vector_new(vector_min_cap(initial_capacity), sizeof(type), allocator))

/**
 * Allocates a new vector of the provided `type`. The initial capacity shall be equal
 * to #VECTOR_MIN_CAPACITY. */
#define vector_new(type)                                                                \
  vector_new_cap(type, VECTOR_MIN_CAPACITY)

/**
 * Same as #vector_new, but using the specified allocator. */
#define vector_new_arena(type, allocator)                                               \
  vector_new_cap_arena(type, VECTOR_MIN_CAPACITY, allocator)

/**
 * Resizes a vector, in order to be able to hold more elements. */
#define vector_resize(vec)                                                              \
  (vec = __vector_resize(vector_fp(vec)), 1)

/**
 * Check if the vector is at full capacity. If so, it shall be resized. */
#define vector_check_resize(vec, amount) (                                              \
  vector_length(vec) + amount >= vector_capacity(vec)                                   \
  ? vector_resize(vec)                                                                  \
  : 1)

/**
 * Pushes a new element at the end of the vector. */
#define vector_push(vec, value) (                                                       \
  vector_check_resize(vec, 1)                                                           \
  ? ((vec)[ vector_fp(vec)->length++ ] = (value), 1)                                    \
  : 0)

/**
 * Loops through all the elements of the vector, using the provided `iter_name`. */
#define vector_each(vec, element_type, iter_name)                                       \
  for (struct { element_type element; uint64 index; } iter_name =                       \
      { .index = 0 }; iter_name.index < vector_length(vec); iter_name.index++)          \
    if (iter_name.element = vec[iter_name.index], 1)

/**
 * Frees all memory used by the vector and its metadata. */
#define vector_free(vec)                                                                \
  ((vec) == NULL ? free(NULL) : __vector_free(vector_fp(vec)))
