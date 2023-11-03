#include <assert.h>

struct user {
  uint32 id;
  uint32 age;
  char name[32];
};


void user_print (struct user user);
uint32 user_hash (void* user);
bool user_compare (void* u1, void* u2);

void test_scalar_int(void);
void test_scalar_struct(void);
