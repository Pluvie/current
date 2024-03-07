#include "test.h"
#include "./test/arena/init/on_stack.c"
#include "./test/arena/create/allocate_begin_region.c"
#include "./test/arena/create/provided_capacity.c"
#include "./test/arena/malloc/allocate_by_advancing_position.c"
#include "./test/arena/malloc/allocate_in_next_region.c"
#include "./test/arena/calloc/allocate_at_zero.c"
#include "./test/arena/realloc/copy_reallocated_memory.c"
#include "./test/arena/realloc/reallocate_same_region.c"
#include "./test/arena/realloc/no_copy_overlap_same_region.c"
#include "./test/arena/realloc/reallocate_end_region.c"
#include "./test/arena/realloc/no_copy_overlap_old_region.c"
#include "./test/vector/init/correct_element_size.c"
#include "./test/vector/init/default_flags.c"
#include "./test/vector/init/provided_flags.c"
#include "./test/vector/create/default_capacity.c"
#include "./test/vector/create/provided_capacity.c"
#include "./test/vector/create/provided_capacity_inferior_to_minimum.c"
#include "./test/vector/push/element_at_length.c"
#include "./test/vector/push/resize_if_capacity_reached.c"
#include "./test/vector/pop/reduce_length.c"
#include "./test/vector/get/value_at_position.c"
#include "./test/vector/get/null_if_over_length.c"
#include "./test/vector/set/value_at_position.c"
#include "./test/vector/set/false_if_over_length.c"
#include "./test/map/init/correct_key_size.c"
#include "./test/map/init/correct_value_size.c"
#include "./test/map/init/default_flags.c"
#include "./test/map/init/provided_flags.c"
#include "./test/map/create/default_capacity.c"
#include "./test/map/create/provided_capacity.c"
#include "./test/map/create/provided_capacity_no_pow_2.c"
#include "./test/map/create/provided_capacity_no_pow_2_high_load.c"
#include "./test/map/create/provided_capacity_inferior_to_minimum.c"
#include "./test/map/set/correct_key_value.c"
#include "./test/map/set/overwrite_value.c"
#include "./test/map/set/copy_key.c"
#include "./test/map/set/avoid_copying_key_if_present.c"
#include "./test/map/set/copy_value.c"
#include "./test/map/set/reuse_value_copy_if_key_present.c"
#include "./test/map/set/rehash_trigger.c"
#include "./test/map/set/rehash_avoid_double_copy.c"
#include "./test/map/get/retrieve_value.c"
#include "./test/map/get/return_null.c"
#include "./test/map/del/remove_entry.c"
#include "./test/map/del/do_nothing.c"
#include "./test/map/has/true_if_key_present.c"
#include "./test/map/has/false_if_key_not_present.c"

int main (
    int argc,
    char** argv
)
{
  test_run( arena_init_on_stack );
  test_run( arena_create_allocate_begin_region );
  test_run( arena_create_provided_capacity );
  test_run( arena_malloc_allocate_by_advancing_position );
  test_run( arena_malloc_allocate_in_next_region );
  test_run( arena_calloc_allocate_at_zero );
  test_run( arena_realloc_copy_reallocated_memory );
  test_run( arena_realloc_reallocate_same_region );
  test_run( arena_realloc_no_copy_overlap_same_region );
  test_run( arena_realloc_reallocate_end_region );
  test_run( arena_realloc_no_copy_overlap_old_region );

  test_run( vector_init_correct_element_size );
  test_run( vector_init_default_flags );
  test_run( vector_init_provided_flags );
  test_run( vector_create_default_capacity );
  test_run( vector_create_provided_capacity );
  test_run( vector_create_provided_capacity_inferior_to_minimum );
  test_run( vector_push_element_at_length );
  test_run( vector_push_resize_if_capacity_reached );
  test_run( vector_pop_reduce_length );
  test_run( vector_get_value_at_position );
  test_run( vector_get_null_if_over_length );
  test_run( vector_set_value_at_position );
  test_run( vector_set_false_if_over_length );

  test_run( map_init_correct_key_size );
  test_run( map_init_correct_value_size );
  test_run( map_init_default_flags );
  test_run( map_init_provided_flags );
  test_run( map_create_default_capacity );
  test_run( map_create_provided_capacity );
  test_run( map_create_provided_capacity_no_pow_2 );
  test_run( map_create_provided_capacity_no_pow_2_high_load );
  test_run( map_create_provided_capacity_inferior_to_minimum );
  test_run( map_set_correct_key_value );
  test_run( map_set_overwrite_value );
  test_run( map_set_copy_key );
  test_run( map_set_avoid_copying_key_if_present );
  test_run( map_set_reuse_value_copy_if_key_present );
  test_run( map_set_copy_value );
  test_run( map_set_rehash_trigger );
  test_run( map_set_rehash_avoid_double_copy );
  test_run( map_get_retrieve_value );
  test_run( map_get_return_null );
  test_run( map_del_remove_entry );
  test_run( map_del_do_nothing );
  test_run( map_has_true_if_key_present );
  test_run( map_has_false_if_key_not_present );

  return 0;
}
