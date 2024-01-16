#define ANSI_COLOR_RED    "\x1b[31m"
#define ANSI_COLOR_GREEN  "\x1b[32m"
#define ANSI_COLOR_NONE   "\x1b[0m"

#define describe(name) \
  fprintf(stderr, "%-48s", name)

#define test(condition) \
  if (!(condition)) { fail(__func__, __LINE__, #condition ); }

#define success() \
  fprintf(stderr, ANSI_COLOR_GREEN); \
  fprintf(stderr, "█\n"); \
  fprintf(stderr, ANSI_COLOR_NONE)

#define fail(func_name, line_num, message) \
  fprintf(stderr, ANSI_COLOR_RED); \
  fprintf(stderr, "█ %s -> %s:%i\n", message, func_name, line_num); \
  fprintf(stderr, ANSI_COLOR_NONE); \
  return

struct user {
  uint32 id;
  uint32 age;
  char name[32];
};

uint64 user_hash (void*);
uint64 user_hash_ptr (void*);
bool user_compare (void*, void*);
bool user_compare_ptr (void*, void*);
void user_print (struct user);
void user_print_ptr (struct user*);

struct user user_generator(int);
struct user* user_generator_ptr(int);
struct user* user_generator_ptr_arena(int, struct arena*);

uint32 string_generator(char*, uint32);

void test_arena_memory(void);

void test_map__char_ptr__char_ptr(void);
void test_map__int32__int32(void);
void test_map__int64__int64(void);
void test_map__struct_user__int32(void);
void test_map__struct_user_ptr__int32(void);
void test_map__key_copy__int32__int32(void);
void test_map__key_copy__char_ptr__int32(void);
void test_map__key_copy__char_ptr__char_ptr(void);

void test_vector(void);
void test_vector_arena(struct arena*);
