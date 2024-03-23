/**
                             _______. _______ .___________.
                            /       ||   ____||           |
                           |   (----`|  |__   `---|  |----`
                            \   \    |   __|      |  |     
                        .----)   |   |  |____     |  |     
                        |_______/    |_______|    |__|     
                                                                                      **/


/**
 * # Set
 *
 * A set is an unordered array *elements* that can be retrieved in constant time. */


enum set_flags;
typedef enum set_flags {
  SET_FLAG__NONE          = 0,
  SET_FLAG__FIXED_LOOKUP  = 1 << 0,
  SET_FLAG__COPY_ELEMENTS = 1 << 1,
} SetFlags;


struct set;
typedef struct set {
  u64 capacity;
  u64 length;
  Map elements;
} Set;


/**
 * Defines the `set_init` macro to initialize a new set with the given *element_type*. */
#define set_init(element_type) \
  { .elements = map_init(element_type, element_type) }

/**
 * Defines a macro to enable the provided flag in the set. */
#define set_flag_enable(set, flag)                                \
  if (flag == SET_FLAG__COPY_ELEMENTS) {                          \
    map_flag_enable(&((set)->elements), MAP_FLAG__COPY_KEYS);     \
    map_flag_enable(&((set)->elements), MAP_FLAG__COPY_VALUES);   \
  } else {                                                        \
    map_flag_enable(&((set)->elements), flag);                    \
  }

/**
 * Defines a macro to disable the provided flag in the set. */
#define set_flag_disable(set, flag)                               \
  if (flag == SET_FLAG__COPY_ELEMENTS) {                          \
    map_flag_disable(&((set)->elements), MAP_FLAG__COPY_KEYS);    \
    map_flag_disable(&((set)->elements), MAP_FLAG__COPY_VALUES);  \
  } else {                                                        \
    map_flag_disable(&((set)->elements), flag);                   \
  }


/**
 * All set function definitions. */

void*   set_add                   ( Set*, void* );
void    set_create                ( Set* );
void*   set_del                   ( Set*, void* );
void    set_destroy               ( Set* );
bool    set_has                   ( Set*, void* );
void    set_pretty_print          ( Set* );
void    set_pretty_print_entry    ( size, u64, MapEntry* );
