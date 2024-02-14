void* arena_realloc (
    struct arena* arena,
    void* memory,
    u64 amount
)
/**
 * Reallocates the *memory* in the arena to a new *amount*. */
{
  if (arena == NULL)
    return realloc(memory, amount);

  struct region* memory_region = arena_region_search(arena, memory);
  if (memory_region == NULL)
    return NULL;

  u64 amount_to_copy = 0;
  u64 previous_position = memory_region->position;
  void* new_memory = arena_malloc(arena, amount);
  bool is_new_memory_in_same_region =
    (byte*) new_memory >= memory_region->data &&
    (byte*) new_memory < (memory_region->data + memory_region->capacity);

  /* If, after allocating the new memory in the arena, the new memory is still in the
   * same region of the original memory -- this basically happens when the last region
   * has enough space for the new memory *amount* -- then the amount to copy shall be
   * equal to the space between the original *memory* and the previous position of the
   * region, but no greater than the region remaining space, to prevent overflow.
   *
   *             REGION
   *              ┌──┐
   *              │  │
   *              │  │
   *           ┌  ├──┤ <─ *memory* to realloc
   *           │  │▒▒│
   *   amount  │  ├──┤
   *   to copy │  │  │
   *           │  │  │   ┌─ region position before realloc, which, in
   *           └┌ ├--┤ <─┘   ┐     this case, is also equal to *new_memory*
   * there is   │ │▒▒│       │
   * enough     │ │▒▒│       ├─ *amount* to realloc
   * space in   │ │▒▒│       │
   * the region │ ├--┤ <─┐   ┘
   * for the    │ │  │   └─ region position after realloc
   * *amount*   │ │  │
   * to realloc │ │  │
   *            └ └──┘ <─ region capacity
   * */
  if (is_new_memory_in_same_region) {
    amount_to_copy = (memory_region->data + previous_position) - (byte*) memory;
    u64 region_remaining_space = memory_region->capacity - previous_position;
    if (amount_to_copy > region_remaining_space)
      amount_to_copy = region_remaining_space;
    goto exec_copy;
  }

  /* Otherwise, the amount to copy shall be equal to the space between the original
   * memory and the end of the region, but no greater than the region capacity, to
   * prevent overflow.
   *
   *             REGION
   *              ┌──┐
   *              │  │
   *              │  │
   *              │  │
   *              │  │
   *              │  │
   *              │  │
   *              │  │
   *           ┌  ├──┤ <─ *memory* to realloc
   *           │  │▒▒│
   *           │  ├──┤
   *   amount  │  │  │   ┌─ region position before realloc
   *   to copy │  ├--┤ <─┘   ┐
   *           │  │  │       │ there is not enough space in the
   *           │  │  │       │ region for the *amount* to realloc
   *           └  └──┘ <─┐   ┘
   *                     └─ region capacity
   *
   *            NEW REGION
   *
   *                     ┌─ *new_memory*
   *              ┌──┐ <─┘   ┐
   *              │▒▒│       │
   *              │▒▒│       │ *amount* to realloc
   *              │▒▒│       │
   *              ├--┤ <─┐   ┘
   *              │  │   └─ new region position after realloc
   *              │  │
   *              │  │
   *              └──┘ <─ new region capacity
   * */
  else {
    amount_to_copy = (memory_region->data + memory_region->capacity) - (byte*) memory;
    struct region* end_region = arena->end;
    if (amount_to_copy > end_region->capacity)
      amount_to_copy = end_region->capacity;
    goto exec_copy;
  }

exec_copy:
  memcpy(new_memory, memory, amount_to_copy);
  return new_memory;
}
