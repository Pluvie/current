#include <assert.h>
#include <threads.h>

struct user {
  uint32 id;
  uint32 age;
  char name[32];
};

struct user* pointer_user_generator(int);
struct user* pointer_user_generator_arena(int, struct arena*);
struct user scalar_user_generator(int);
struct user user_generator(int);
void user_print (struct user);
uint64 user_hash (void*);
bool user_compare (void*, void*);
bool user_ptr_compare (void*, void*);
uint64 user_ptr_hash (void*);
void user_ptr_print (struct user*);

void test_arena(void);
void test_char_pointer(void);
void test_char_pointer_arena(struct arena*);
void test_pointer_struct (void);
void test_pointer_struct_arena (struct arena*);
void test_pointer_struct_copy (void);
void test_scalar_int(void);
void test_scalar_int_arena(struct arena*);
void test_scalar_struct(void);
void test_scalar_struct_arena(struct arena*);
void test_vector(void);
void test_vector_arena(struct arena*);
