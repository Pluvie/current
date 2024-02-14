int main (
    int argc,
    char** argv
)
{
  int result = 0;

  for (int a = 0; a < 1000; a++) {
    for (int i = 0; i < 100000; i++) {
      for (int j = 0; j < 100; j++) {
        result = i;
      }
    }
  }

  fprintf(stderr, "done: %i\n", result);

  return 0;
}
