void benchmark_generic (
    void
)
{
  fprintf(stderr, "Generic\n");

  map(int, int) benchmark = map_new(int, int);
  int round_capped = 0;
  for (int round = 0; round < BENCHMARK_ROUNDS; round++) {
    round_capped = (round % MAX_KEY_LENGTH) + 1;
    //fprintf(stderr, ">> [%i] %i\n", round, round_capped);
    map_set(benchmark, round_capped, round);
  }

  map_print(benchmark, int, int, "%i", "%i");
  int test = 4;
  fprintf(stderr, "TESTTT >>> %i: %i\n", test, map_get(benchmark, test));
  fprintf(stderr, "TESTTT >>> %i: %i\n", test, benchmark[4]);
  map_free(benchmark);
}
