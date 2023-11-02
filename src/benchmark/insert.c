#define cacca(str) str

void benchmark_insert (
    void
)
{
  fprintf(stderr, "Insert\n");

  map(char*, int) benchmark = map_new(char*, int);
  int string_length = 0;
  char character = ASCII_CHAR_BEGIN;
  char* key_forge = calloc(MAX_KEY_LENGTH + 1, sizeof(char));

  for (int round = 0; round < BENCHMARK_ROUNDS; round++) {
    memset(key_forge, '\0', MAX_KEY_LENGTH + 1);

    string_length = (round % MAX_KEY_LENGTH) + 1;
    for (int pos = 0; pos < string_length; pos++) {
      key_forge[pos] = character;
      character++;
      if (character > ASCII_CHAR_END)
        character = ASCII_CHAR_BEGIN;
    }

    //fprintf(stderr, ">> [%i] %s\n", round, key);
    map_set(benchmark, key_forge, round);
    //map_print(benchmark, char*, int, "%s", "%i");
  }

  map_print(benchmark, char*, int, "%s", "%i");
  char* key_to_check = "a";
  int value_to_check = 16777072;
  fprintf(stderr, "CHECK: %i\n", map_get(benchmark, key_to_check) == value_to_check);
  //fprintf(stderr, "CHECK: %i\n", benchmark[6] == value_to_check);

  map_free(benchmark);
  free(key_forge);
}
