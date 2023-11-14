void* arena_calloc (
    arena* current,
    int64 num,
    int64 size
)
{
  void* memory = arena_malloc(current, num * size);
  memset(memory, '\0', num * size);
  return memory;
}
