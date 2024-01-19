struct arena* arena = NULL;

int main (
    int argc,
    char** argv
)
{
  arena = arena_init(0);
  test_arena_memory();

  test_map__int32__int32();
  //test_map__int64__int64();
  //test_map__struct_user__int32();
  //test_map__struct_user_ptr__int32();
  //test_map__char_ptr__char_ptr();

  test_map__key_copy__int32__int32();
  //test_map__key_copy__char_ptr__int32();
  //test_map__key_copy__char_ptr__char_ptr();
  ///test_map_pointer_struct_key_copy();
  ///test_map_pointer_char();
  ///test_map_pointer_char_key_copy();
  //test_map_vector();

  ///test_map_scalar_int_arena(arena);
  ///test_map_scalar_struct_arena(arena);
  ///test_map_pointer_struct_arena(arena);
  //test_map_char_pointer_arena(arena);
  //test_vector_arena(arena);
  arena_destroy(arena);

  return 0;
}
