#include <assert.h>
#include <threads.h>

struct user {
  uint32 id;
  uint32 age;
  char name[32];
};

uint64 user_hash (void*);
bool user_compare (void*, void*);
void user_print (struct user);

struct user user_generator(int);
struct user* user_generator_ptr(int);
struct user* user_generator_ptr_arena(struct arena*, int);

void test_arena(void);
void test_map_char_pointer(void);
void test_map_char_pointer_arena(struct arena*);
void test_map_pointer_struct (void);
void test_map_pointer_struct_arena (struct arena*);
void test_map_pointer_struct_copy (void);
void test_map_scalar_int(void);
void test_map_scalar_int_arena(struct arena*);
void test_map_scalar_struct(void);
void test_map_scalar_struct_arena(struct arena*);
void test_vector(void);
void test_vector_arena(struct arena*);
