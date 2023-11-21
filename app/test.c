struct arena* arena = NULL;

int main (
    int argc,
    char** argv
)
{

  //test_map_scalar_int();
  //test_map_scalar_struct();
  //test_map_pointer_struct();
  //test_map_pointer_char();
  test_map_pointer_char_key_copy();
  //test_map_vector();

  arena = arena_init(0);
  //test_arena();
  //test_map_scalar_int_arena(arena);
  //test_map_scalar_struct_arena(arena);
  //test_map_pointer_struct_arena(arena);
  //test_map_pointer_struct_copy();
  //test_map_char_pointer_arena(arena);
  //test_vector_arena(arena);
  arena_destroy(arena);

  char abc[5] = { 'a', 'b', 'c' };
  fprintf(stderr, "%p\n", abc);
  fprintf(stderr, "%p\n", &abc);
  fprintf(stderr, "%p\n", (void*) &abc);
  void* v = abc;
  fprintf(stderr, "%p\n", v);
  fprintf(stderr, "%p\n", &v);
  fprintf(stderr, "%p\n", "abc");
  fprintf(stderr, "%p\n", &"abc");
  void* w = "abc";
  fprintf(stderr, "%p\n", w);
  fprintf(stderr, "%p\n", &w);

  return 0;
}
