/**
        ____    ____  _______   ______ .___________.  ______   .______      
        \   \  /   / |   ____| /      ||           | /  __  \  |   _  \     
         \   \/   /  |  |__   |  ,----'`---|  |----`|  |  |  | |  |_)  |    
          \      /   |   __|  |  |         |  |     |  |  |  | |      /     
           \    /    |  |____ |  `----.    |  |     |  `--'  | |  |\  \----.
            \__/     |_______| \______|    |__|      \______/  | _| `._____|
        
                                                                                      **/
/**
 * Defines the `vector_init` macro to initialize new vector with the given
 * *element_type*. */
#define vector_init(element_type)  \
  { .element_size = sizeof(element_type) }

/**
 * Defines the defaul initial capacity of a vector, if not specified by the
 * programmer. */
#define VECTOR_DEFAULT_CAPACITY 8

struct vector {
  u64   capacity;
  u64   length;
  u32   flags;
  size  element_size;
  void* elements;
  struct arena* arena;
};

/**
 * Defines all the flags used to tweak and configure the vector behaviour. */
enum vector_flags {
  Vector_Flag__None           = 0,
  Vector_Flag__Copy_Elements  = 1 << 1,
};

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
function( vector_create,          void    )(  struct vector*                );
function( vector_destroy,         void    )(  struct vector*                );
function( vector_get,             void*   )(  struct vector*, u64           );
function( vector_pop,             void*   )(  struct vector*                );
function( vector_pretty_print,    void    )(  struct vector*                );
function( vector_push,            void    )(  struct vector*, void*         );
function( vector_resize,          void    )(  struct vector*                );
function( vector_set,             bool    )(  struct vector*, u64, void*    );
