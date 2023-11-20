thread_local struct arena* arena;

int main (
    int argc,
    char** argv
)
{

  test_map_scalar_int();
  test_map_scalar_struct();
  test_map_pointer_struct();
  //test_map_char_pointer();
  //test_map_vector();

  arena = arena_init(0);
  //test_arena();
  test_map_scalar_int_arena(arena);
  test_map_scalar_struct_arena(arena);
  test_map_pointer_struct_arena(arena);
  //test_map_pointer_struct_copy();
  //test_map_char_pointer_arena(arena);
  //test_vector_arena(arena);
  arena_destroy(arena);

  return 0;
}
