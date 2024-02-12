#define ANSI_COLOR_RED    "\x1b[31m"
#define ANSI_COLOR_GREEN  "\x1b[32m"
#define ANSI_COLOR_NONE   "\x1b[0m"

#define test(test_function_name)                                                        \
  void test_function_name(void)

#define test_function(test_function_name)                                               \
  void test_function_name(void);

#define success()                                                                       \
  fprintf(stderr, "\r");                                                                \
  fprintf(stderr, ANSI_COLOR_GREEN);                                                    \
  fprintf(stderr, "█ ");                                                                \
  fprintf(stderr, ANSI_COLOR_NONE);                                                     \
  fprintf(stderr, "\n");                                                                \
end_test:

#define given(description)                                                              \
  fprintf(stderr, "  given " description);

#define when(description)                                                               \
  fprintf(stderr, ", when " description);

#define calling(description)                                                            \
  fprintf(stderr, " => calling " description);

#define must(description)                                                               \
  fprintf(stderr, " must " description);

#define describe(description)                                                           \
  fprintf(stderr, "\n[%s]\n", description)

#define verify(condition)                                                               \
  if (!(condition)) { fail(__FILE__, __LINE__, #condition ); }

#define fail(location_name, line_num, message)                                          \
  fprintf(stderr, " : ");                                                               \
  fprintf(stderr, ANSI_COLOR_RED);                                                      \
  fprintf(stderr, "%s (%s:%i)\n", message, location_name, line_num);                    \
  fprintf(stderr, ANSI_COLOR_NONE);                                                     \
  fprintf(stderr, "\r");                                                                \
  fprintf(stderr, ANSI_COLOR_RED);                                                      \
  fprintf(stderr, "█ ");                                                                \
  fprintf(stderr, ANSI_COLOR_NONE);                                                     \
  fprintf(stderr, "\n");                                                                \
  goto end_test;

test_function( map_alloc_default_capacity );
