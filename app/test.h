#define ASCII_ESC         27
#define ANSI_COLOR_RED    "\x1b[31m"
#define ANSI_COLOR_GREEN  "\x1b[32m"
#define ANSI_COLOR_NONE   "\x1b[0m"

#define test(test_function_name)                                                        \
  void test_function_name(void)

#define test_function(test_function_name)                                               \
  void test_function_name(void);

#define success()                                                                       \
  fprintf(stderr, "%c8", ASCII_ESC);                                                    \
  fprintf(stderr, ANSI_COLOR_GREEN);                                                    \
  fprintf(stderr, "█ ");                                                                \
  fprintf(stderr, ANSI_COLOR_NONE);                                                     \
  fprintf(stderr, "\n");                                                                \
end_test:

#define given(description)                                                              \
  fprintf(stderr, "%c7  given " description, ASCII_ESC);

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
  fprintf(stderr, "%c8", ASCII_ESC);                                                    \
  fprintf(stderr, ANSI_COLOR_RED);                                                      \
  fprintf(stderr, "█ ");                                                                \
  fprintf(stderr, ANSI_COLOR_NONE);                                                     \
  fprintf(stderr, "\n");                                                                \
  fprintf(stderr, ANSI_COLOR_RED);                                                      \
  fprintf(stderr, "  %s (%s:%i)", message, location_name, line_num);                    \
  fprintf(stderr, ANSI_COLOR_NONE);                                                     \
  fprintf(stderr, "\n");                                                                \
  goto end_test;

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
