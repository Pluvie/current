#define ANSI_COLOR_RED    "\x1b[31m"
#define ANSI_COLOR_GREEN  "\x1b[32m"
#define ANSI_COLOR_NONE   "\x1b[0m"

#define describe(description)                                                           \
  fprintf(stderr, "\n[%s]\n", description)

#define test(test_case)                                                                 \
  for (struct { const char* m; i8 i; } t = { .m = test_case, .i = 0 }; t.i < 1; t.i++)

#define assert(condition)                                                               \
  if (!(condition)) { fail(__FILE__, __LINE__, #condition ); }

#define success()                                                                       \
  fprintf(stderr, ANSI_COLOR_GREEN);                                                    \
  fprintf(stderr, "█ ");                                                                \
  fprintf(stderr, ANSI_COLOR_NONE);                                                     \
  fprintf(stderr, "%s\n", t.m);

#define fail(location_name, line_num, message)                                          \
  fprintf(stderr, ANSI_COLOR_RED);                                                      \
  fprintf(stderr, "█ ");                                                                \
  fprintf(stderr, ANSI_COLOR_NONE);                                                     \
  fprintf(stderr, "%s :", t.m);                                                         \
  fprintf(stderr, ANSI_COLOR_RED);                                                      \
  fprintf(stderr, "%s (%s:%i)\n", message, location_name, line_num);                    \
  fprintf(stderr, ANSI_COLOR_NONE);                                                     \
  break

function( test_arena,     void  )(  void  );
function( test_map,       void  )(  void  );
