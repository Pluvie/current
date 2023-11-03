void benchmark_delete (
    void
)
{
  fprintf(stderr, "Delete\n");

  map(char*, char*) benchmark = map_new(char*, char*);
  int string_length = 0;
  char character = ASCII_CHAR_BEGIN;
  char* key_forge = calloc(MAX_KEY_LENGTH + 1, sizeof(char));
  char* value_forge = NULL;

  for (int round = 0; round < BENCHMARK_ROUNDS; round++) {
    memset(key_forge, '\0', MAX_KEY_LENGTH + 1);

    string_length = (round % MAX_KEY_LENGTH) + 1;
    for (int pos = 0; pos < string_length; pos++) {
      key_forge[pos] = character;
      character++;
      if (character > ASCII_CHAR_END)
        character = ASCII_CHAR_BEGIN;
    }

    fprintf(stderr, "\n\n>> [%i] %s\n", round, key_forge);
    value_forge = strdup(key_forge);
    map_set(benchmark, key_forge, value_forge);
    map_print(benchmark, char*, char*, "%s", "%s");
  }

  map_print(benchmark, char*, char*, "%s", "%s");
  char* key_to_check = "ghij";
  fprintf(stderr, "CHECK: %s\n", map_get(benchmark, "ghij"));
  fprintf(stderr, "CHECK: %s\n", map_get(benchmark, key_to_check));
  fprintf(stderr, "CHECK: %s\n", benchmark[8]);
  //fprintf(stderr, "CHECK: %i\n", benchmark[6] == value_to_check);

  for (int i = 0; i < map_capacity(benchmark); i++)
    free(benchmark[i]);
  map_free(benchmark);
  free(key_forge);
}
