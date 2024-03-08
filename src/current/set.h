/**
                             _______. _______ .___________.
                            /       ||   ____||           |
                           |   (----`|  |__   `---|  |----`
                            \   \    |   __|      |  |     
                        .----)   |   |  |____     |  |     
                        |_______/    |_______|    |__|     
                                                                                      **/

/**
 * Defines the `set_init` macro to initialize a new set with the given *element_type*. */
#define set_init(element_type) \
  { .elements = map_init(element_type, element_type) }

/**
 * Defines the `set` struct.
 * A set is an unordered array *elements* that can be retrieved in constant time. */
struct set {
  u64 capacity;
  u64 length;
  struct map elements;
};

/**
 * Defines all the flags used to tweak and configure the set behaviour. */
enum set_flags {
  Set_Flag__None          = 0,
  Set_Flag__Fixed_Lookup  = 1 << 0,
  Set_Flag__Copy_Elements = 1 << 1,
};

/**
 * Defines a macro to enable the provided flag in the set. */
#define set_flag_enable(set, flag)                                \
  if (flag == Set_Flag__Copy_Elements) {                          \
    map_flag_enable(&((set)->elements), Map_Flag__Copy_Keys);     \
    map_flag_enable(&((set)->elements), Map_Flag__Copy_Values);   \
  } else {                                                        \
    map_flag_enable(&((set)->elements), flag);                    \
  }

/**
 * Defines a macro to disable the provided flag in the set. */
#define set_flag_disable(set, flag)                               \
  if (flag == Set_Flag__Copy_Elements) {                          \
    map_flag_disable(&((set)->elements), Map_Flag__Copy_Keys);    \
    map_flag_disable(&((set)->elements), Map_Flag__Copy_Values);  \
  } else {                                                        \
    map_flag_disable(&((set)->elements), flag);                   \
  }

/**
 * All set function definitions. */
function( set_add,                  void*   )(  struct set*, void*            );
function( set_create,               void    )(  struct set*                   );
function( set_del,                  void*   )(  struct set*, void*            );
function( set_destroy,              void    )(  struct set*                   );
function( set_has,                  bool    )(  struct set*, void*            );
function( set_pretty_print,         void    )(  struct set*                   );
function( set_pretty_print_entry,   void    )(  size, u64, struct map_entry*  );
