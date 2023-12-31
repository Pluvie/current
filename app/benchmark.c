int main (
    int argc,
    char** argv
)
{
  if (argc != 2) {
    fprintf(stderr,
      "Usage: current-benchmark [case]"           "\n"
      "  Cases:"                                  "\n"
      "  - insert   : insert focused benchmarks"  "\n"
      "  - lookup   : lookup focused benchmarks"  "\n"
      "  - delete   : delete focused benchmarks"  "\n"
      "  - generic  : generic usage benchmark"    "\n");
    return 1;
  }

       if (strcmp(argv[1], "insert") == 0)
    benchmark_insert();
  else if (strcmp(argv[1], "lookup") == 0)
    benchmark_lookup();
  else if (strcmp(argv[1], "delete") == 0)
    benchmark_delete();
  else if (strcmp(argv[1], "generic") == 0)
    benchmark_generic();

  return 0;
}
