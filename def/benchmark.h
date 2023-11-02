//#define BENCHMARK_ROUNDS  1 << 18
#define BENCHMARK_ROUNDS  (1 << 8)
#define MAX_KEY_LENGTH    (1 << 4)
#define ASCII_CHAR_BEGIN  97
#define ASCII_CHAR_END    122

void benchmark_insert(void);
void benchmark_lookup(void);
void benchmark_delete(void);
void benchmark_generic(void);
