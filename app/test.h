/**
 * Various constants and helpers to print on the console. */

#define ASCII_ESC                 27
#define ANSI_COLOR_RED            "\x1b[31m"
#define ANSI_COLOR_GREEN          "\x1b[32m"
#define ANSI_COLOR_NONE           "\x1b[0m"

//#define USE_VT100
#ifdef  USE_VT100
  #define VT100_SAVE_CURSOR_POS     fprintf(stderr, "%c7", ASCII_ESC)
  #define VT100_RESTORE_CURSOR_POS  fprintf(stderr, "%c8", ASCII_ESC)
#else
  #define VT100_SAVE_CURSOR_POS
  #define VT100_RESTORE_CURSOR_POS  fprintf(stderr, "\r")
#endif

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

#define test_run(test_function_name)                                                    \
  VT100_SAVE_CURSOR_POS;                                                                \
  fprintf(stderr, "  " #test_function_name);                                            \
  test_function_name()

#define given(description)    ;
#define when(description)     ;
#define calling(description)  ;
#define must(description)     ;

#define verify(condition)                                                               \
  if (!(condition)) { fail(__FILE__, __LINE__, #condition ); }

#define success()                                                                       \
  VT100_RESTORE_CURSOR_POS;                                                             \
  fprintf(stderr, ANSI_COLOR_GREEN);                                                    \
  fprintf(stderr, "█ ");                                                                \
  fprintf(stderr, ANSI_COLOR_NONE);                                                     \
  fprintf(stderr, "\n");                                                                \
end_test:

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
