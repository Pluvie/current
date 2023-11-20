#include <assert.h>
#include <threads.h>

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
