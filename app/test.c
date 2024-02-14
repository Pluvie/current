int main (
    int argc,
    char** argv
)
{
  test_run( arena_init_on_stack );
  test_run( arena_alloc_allocate_begin_region );
  test_run( arena_alloc_provided_capacity );
  test_run( arena_malloc_allocate_by_advancing_position );
  test_run( arena_malloc_allocate_in_next_region );
  test_run( arena_calloc_allocate_at_zero );
  test_run( arena_realloc_copy_reallocated_memory );
  test_run( arena_realloc_reallocate_same_region );
  test_run( arena_realloc_no_copy_overlap_same_region );
  test_run( arena_realloc_reallocate_end_region );
  test_run( arena_realloc_no_copy_overlap_old_region );

  test_run( map_correct_key_size );
  test_run( map_correct_value_size );
  test_run( map_default_flags );
  test_run( map_provided_flags );
  test_run( map_alloc_default_capacity );
  test_run( map_alloc_provided_capacity );
  test_run( map_alloc_provided_capacity_no_pow_2 );
  test_run( map_alloc_provided_capacity_inferior_to_minimum );
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
