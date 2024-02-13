/**
 * Various constants and helpers to print on the console. */

#define ASCII_ESC                 27
#define ANSI_COLOR_RED            "\x1b[31m"
#define ANSI_COLOR_GREEN          "\x1b[32m"
#define ANSI_COLOR_NONE           "\x1b[0m"
#define VT100_SAVE_CURSOR_POS     fprintf(stderr, "%c7", ASCII_ESC)
#define VT100_RESTORE_CURSOR_POS  fprintf(stderr, "%c8", ASCII_ESC)

/**
 * Test framework macros.
 *
 * Example:
 * ```c
 * test(map_alloc_provided_capacity) {                    // wrap the test with `test()`
 *                                                        //
 *   given("a map")                                       // set the subject with
 *     struct map map = map_init(i32, i32);               // `given()`
 *                                                        //
 *   when("the provided capacity is a power of 2")        // conditions can be expressed
 *     map.capacity = 1 << 4;                             // with `when()`
 *                                                        //
 *   calling("map_alloc()")                               // the function to be tested
 *     map_alloc(&map);                                   // is defined with `calling()`
 *                                                        //
 *   must("allocate the map with the provided capacity")  // the end result can be
 *     verify(map.capacity == 16);                        // enforced with `must()`
 *                                                        //
 *   success()                                            // closing operations can be
 *     map_free(&map);                                    // done after `success()`
 * }                                                      //
 * ```
 *
 * This (very) simple framework should give you the basic tools to write test functions
 * in a natural and readable way. */

#define test(test_function_name)                                                        \
  void test_function_name(void)

#define test_function(test_function_name)                                               \
  void test_function_name(void);

#define success()                                                                       \
  VT100_RESTORE_CURSOR_POS;                                                             \
  fprintf(stderr, ANSI_COLOR_GREEN);                                                    \
  fprintf(stderr, "█ ");                                                                \
  fprintf(stderr, ANSI_COLOR_NONE);                                                     \
  fprintf(stderr, "\n");                                                                \
end_test:

#define given(description)                                                              \
  VT100_SAVE_CURSOR_POS;                                                                \
  fprintf(stderr, "  given " description);

#define when(description)                                                               \
  fprintf(stderr, ", when " description);

#define calling(description)                                                            \
  fprintf(stderr, ", calling " description);

#define must(description)                                                               \
  fprintf(stderr, " must " description);

#define describe(description)                                                           \
  fprintf(stderr, "\n[%s]\n", description)

#define verify(condition)                                                               \
  if (!(condition)) { fail(__FILE__, __LINE__, #condition ); }

#define fail(location_name, line_num, message)                                          \
  VT100_RESTORE_CURSOR_POS;                                                             \
  fprintf(stderr, ANSI_COLOR_RED);                                                      \
  fprintf(stderr, "█ ");                                                                \
  fprintf(stderr, ANSI_COLOR_NONE);                                                     \
  fprintf(stderr, "\n");                                                                \
  fprintf(stderr, ANSI_COLOR_RED);                                                      \
  fprintf(stderr, "  %s (%s:%i)", message, location_name, line_num);                    \
  fprintf(stderr, ANSI_COLOR_NONE);                                                     \
  fprintf(stderr, "\n");                                                                \
  goto end_test;

/**
 * Test functions (cases). */

test_function( map_correct_key_size );
test_function( map_correct_value_size );
test_function( map_default_flags );
test_function( map_provided_flags );
test_function( map_alloc_default_capacity );
test_function( map_alloc_provided_capacity );
test_function( map_alloc_provided_capacity_no_pow_2 );
test_function( map_alloc_provided_capacity_inferior_to_minimum );
test_function( map_set_correct_key_value );
test_function( map_set_overwrite_value );
test_function( map_set_copy_key );
test_function( map_set_avoid_copying_key_if_present );
test_function( map_set_copy_value );
test_function( map_set_reuse_value_copy_if_key_present );
test_function( map_set_rehash_trigger );
test_function( map_set_rehash_avoid_double_copy );
test_function( map_get_retrieve_value );
test_function( map_get_return_null );
test_function( map_del_remove_entry );
test_function( map_del_do_nothing );
test_function( map_has_true_if_key_present );
test_function( map_has_false_if_key_not_present );
