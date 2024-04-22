/**
        ____    ____  _______   ______ .___________.  ______   .______      
        \   \  /   / |   ____| /      ||           | /  __  \  |   _  \     
         \   \/   /  |  |__   |  ,----'`---|  |----`|  |  |  | |  |_)  |    
          \      /   |   __|  |  |         |  |     |  |  |  | |      /     
           \    /    |  |____ |  `----.    |  |     |  `--'  | |  |\  \----.
            \__/     |_______| \______|    |__|      \______/  | _| `._____|
        
                                                                                      **/


/**
 * # Vector
 *
 * A vector is a collection of dynamically allocated elements of the same type.
 * It will grow automatically to fit the memory occupied by all the elements. */


enum vector_flags;
typedef enum vector_flags {
  VECTOR_FLAG__NONE           = 0,
  VECTOR_FLAG__COPY_ELEMENTS  = 1 << 1,
  VECTOR_FLAG__READ_ONLY      = 1 << 2,
} VectorFlags;


struct vector;
typedef struct vector {
  u64 capacity;
  u64 length;
  size element_size;
  void* elements;
  VectorFlags flags;
  Arena* arena;
} Vector;


/**
 * Defines the defaul initial capacity of a vector, if not specified by the
 * programmer. */
#define VECTOR_DEFAULT_CAPACITY 8

/**
 * Defines the `vector_init` macro to initialize new vector with the given
 * *element_type*. */
#define vector_init(element_type)  \
  { .element_size = sizeof(element_type) }

/**
 * Defines a macro to enable the provided flag in the vector. */
#define vector_flag_enable(vector, flag) \
  (vector)->flags |= (flag)

/**
 * Defines a macro to disable the provided flag in the vector. */
#define vector_flag_disable(vector, flag) \
  (vector)->flags &= ~(flag)

/**
 * Defines a macro to iterate all the elements in the vector. */
#define vector_each(vector, element) \
  (u64 i = 0; i < (vector)->capacity; i++) \
    if ((element = vector_get(vector, i)) != NULL)

/**
 * Defines a macro to iterate all the elements in the vector, with a specified index. */
#define vector_each_with_index(vector, element, index) \
  (u64 index = 0; index < (vector)->capacity; index++) \
    if ((element = vector_get(vector, index)) != NULL)


/**
 * All vector function definitions. */

void    vector_create         ( Vector* );
void    vector_destroy        ( Vector* );
bool    vector_from_data      ( Vector*, void*, u64 );
void*   vector_get            ( Vector*, u64 );
void*   vector_pop            ( Vector* );
void    vector_pretty_print   ( Vector* );
void    vector_push           ( Vector*, void* );
void    vector_resize         ( Vector* );
bool    vector_set            ( Vector*, u64, void* );
