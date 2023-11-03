#include <assert.h>

struct user {
  uint32 id;
  uint32 age;
  char name[32];
};


void user_print (struct user user);
uint32 user_hash (void* user);
bool user_compare (void* u1, void* u2);
bool user_ptr_compare (void* u1, void* u2);
uint32 user_ptr_hash (void* user);
void user_ptr_print (struct user* user);

void test_char_pointer(void);
void test_pointer_struct (void);
void test_scalar_int(void);
void test_scalar_struct(void);
void test_vector(void);
