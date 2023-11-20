thread_local struct arena* arena;

int main (
    int argc,
    char** argv
)
{
  arena = arena_init(0);

  //test_arena();
  //test_scalar_int();
  test_scalar_int_arena(arena);
  //test_scalar_struct();
  //test_scalar_struct_arena(arena);
  //test_pointer_struct();
  //test_pointer_struct_arena(arena);
  //test_pointer_struct_copy();
  //test_char_pointer();
  //test_char_pointer_arena(arena);
  //test_vector();
  //test_vector_arena(arena);

  arena_destroy(arena);

  return 0;
}
