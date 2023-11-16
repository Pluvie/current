int main (
    int argc,
    char** argv
)
{
  test_arena();
  test_scalar_int();
  test_scalar_int_arena();
  test_scalar_struct();
  test_scalar_struct_arena();
  test_pointer_struct();
  test_pointer_struct_arena();
  test_pointer_struct_copy();
  test_char_pointer();
  test_char_pointer_arena();
  test_vector();
  test_vector_arena();
  return 0;
}
