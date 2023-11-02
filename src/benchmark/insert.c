#define cacca(str) str

void benchmark_insert (
    void
)
{
  fprintf(stderr, "Insert\n");

  vector(char*) keys = vector_new(char*);
  map(char*, int) benchmark = map_new(char*, int);
  int string_length = 0;
  char character = ASCII_CHAR_BEGIN;
  char key_forge[MAX_KEY_LENGTH + 1] = { 0 };
  char* key = NULL;

  for (int round = 0; round < BENCHMARK_ROUNDS; round++) {
    memset(key_forge, '\0', MAX_KEY_LENGTH + 1);

    string_length = (round % MAX_KEY_LENGTH) + 1;
    for (int pos = 0; pos < string_length; pos++) {
      key_forge[pos] = character;
      character++;
      if (character > ASCII_CHAR_END)
        character = ASCII_CHAR_BEGIN;
    }

    key = calloc(string_length + 1, sizeof(char));
    vector_push(keys, key);
    memcpy(key, key_forge, string_length + 1);
    //fprintf(stderr, ">> [%i] %s\n", round, key);
    map_set(benchmark, key, round);
    //map_print(benchmark, char*, int, "%s", "%i");
  }

  map_print(benchmark, char*, int, "%s", "%i");
  fprintf(stderr, "key: %s\n", keys[0]);
  char* akey = "a";
  fprintf(stderr, "a: %i\n", map_get(benchmark, akey));
  fprintf(stderr, "a: %i\n", map_get(benchmark, keys[0]));
  fprintf(stderr, "a: %i\n", benchmark[6]);

  map_free(benchmark);
  vector_each(keys, index)
    free(keys[index]);
  vector_free(keys);
}
