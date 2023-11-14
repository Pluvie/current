int main (
    int argc,
    char** argv
)
{
  fprintf(stderr, "scratching\n");
  test_scalar_int();
  test_scalar_int_arena();
  //test_scalar_struct();
  //test_pointer_struct();
  //test_char_pointer();
  //test_vector();
  return 0;
}
